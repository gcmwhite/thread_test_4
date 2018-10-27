#include "timework.h"
#include <QDebug>

TimeWork::TimeWork(QObject *parent)
    :QObject(parent)
{
    isPause = false;
    isStop = true;
}

void TimeWork::start()
{
    qDebug() << "子线程启动：" << QThread::currentThread();
    int count = 0;
    isStop = false;
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
    isStop = true;
}
