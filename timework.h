#ifndef TIMEWORK_H
#define TIMEWORK_H

#include <QObject>
#include <QMutex>
#include <QThread>

class TimeWork : public QObject
{
    Q_OBJECT
public:
    explicit TimeWork(QObject *parent = nullptr);
    void start();
    void pause();
    void close();

private:
    bool isPause;
    bool isStop;
    QMutex mutex,mutex2;
//    QThread thread;

signals:
    void countSignal(int);
};

#endif // TIMEWORK_H
