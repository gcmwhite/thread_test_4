#include "timework.h"
#include <QDebug>
#include <QMutexLocker>

TimeWork::TimeWork(QObject *parent)
    :QObject(parent)
{
    QMutexLocker lock(&mutex2);
    isPause = false;
    isStop = true;
}

void TimeWork::start()
{
    qDebug() << "子线程启动：" << QThread::currentThread();
    int count = 0;
    mutex2.lock();
    isStop = false;
    mutex2.unlock();
    while (!isStop) {
        emit countSignal(count++);
        QThread::msleep(200);
        mutex.lock();
        mutex.unlock();
    }
    qDebug() << "子线程退出：" << QThread::currentThread();
}

void TimeWork::pause()
{
    if (isStop)
    {
        qDebug() << "线程未启动！";
        return ;
    }
    QMutexLocker lock(&mutex2);
    isPause = !isPause;
    if (isPause)
    {
        mutex.lock();
    } else {
        mutex.unlock();
    }
}

void TimeWork::close()
{

    if (isStop)
    {
        qDebug() << "线程未启动！";
        return ;
    }
    if (isPause)
    {
        mutex.unlock();
        isPause = false;
    }
    QMutexLocker lock(&mutex2);
    isStop = true;
}
