#include "widget.h"
#include "ui_widget.h"
#include "timework.h"
#include <QDebug>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "主线程启动：" << QThread::currentThread();

    TimeWork *t1 = new TimeWork;
    TimeWork *t2 = new TimeWork;

    QThread *th1 = new QThread;
    QThread *th2 = new QThread;

    t1->moveToThread(th1);
    t2->moveToThread(th2);

    connect(th1,&QThread::started,t1,&TimeWork::start);
    connect(th2,&QThread::started,t2,&TimeWork::start);

    connect(t1,&TimeWork::countSignal,this,[=](int count){
        ui->lcdNumber_1->display(count);
    });

    connect(t2,&TimeWork::countSignal,this,[=](int count){
        ui->lcdNumber_2->display(count);
    });

    connect(ui->startBtn_1,&QPushButton::clicked,this,[=](){
        th1->start();
    });

    connect(ui->startBtn_2,&QPushButton::clicked,this,[=](){
        th2->start();
    });

    connect(ui->pauseBtn_1,&QPushButton::clicked,this,[=](){
        t1->pause();
    });

    connect(ui->pauseBtn_2,&QPushButton::clicked,this,[=](){
        t2->pause();
    });

    connect(ui->stopBtn_1,&QPushButton::clicked,this,[=](){
        t1->close();
        th1->quit();
        th1->wait();
        ui->lcdNumber_1->display(0);
    });

    connect(ui->stopBtn_2,&QPushButton::clicked,this,[=](){
        t2->close();
        th2->quit();
        th2->wait();
        ui->lcdNumber_2->display(0);
    });

    connect(this,&Widget::destroyed,this,[=](){
        t1->close();
        th1->quit();
        th1->wait();
        t1->deleteLater();
        th2->deleteLater();

        t2->close();
        th2->quit();
        th2->wait();
        t2->deleteLater();
        th2->deleteLater();

        qDebug() << "程序完全退出！";
    });


}

Widget::~Widget()
{
    delete ui;
}
