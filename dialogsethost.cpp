#include "dialogsethost.h"
#include "ui_dialogsethost.h"
#include<QPushButton>
#include <QTcpSocket>
extern MainWindow* mainwindow;
DialogSetHost::DialogSetHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetHost)
{
    ui->setupUi(this);
}

void DialogSetHost::listening_thread()
{

}

DialogSetHost::~DialogSetHost()
{
    delete ui;
}


void DialogSetHost::acceptConnection()
{
    mainwindow->readWriteSocket = mainwindow->listenSocket->nextPendingConnection();
    qDebug() << "hehe";
    this->accept();
}



void DialogSetHost::on_pushButton_clicked()
{
    qDebug() << &mainwindow;
    qDebug() << mainwindow->listenSocket;
    delete mainwindow->listenSocket;
    delete mainwindow->readWriteSocket;
    mainwindow->listenSocket = nullptr;
    mainwindow->readWriteSocket = nullptr;
     qDebug() << "haha";
    mainwindow->listenSocket = new QTcpServer();
    mainwindow->listenSocket->listen(QHostAddress(ui->lineEdit->text()), 2345);
     qDebug() << "haha";
    connect(mainwindow->listenSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    ui->buttonBox->button(ui->buttonBox->Ok)->setEnabled(false);
     qDebug() << "haha";
    qDebug() << "haha";
}

void DialogSetHost::on_pushButton_2_clicked()
{
    mainwindow->listenSocket->close();
    this->reject();
}
