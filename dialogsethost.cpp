#include "dialogsethost.h"
#include "ui_dialogsethost.h"
#include<QPushButton>
#include <QTcpSocket>
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

void DialogSetHost::on_buttonBox_accepted()
{
    delete mainwindow->listenSocket;
    delete mainwindow->readWriteSocket;
    mainwindow->listenSocket = nullptr;
    mainwindow->readWriteSocket = nullptr;
    mainwindow->listenSocket = new QTcpServer();
    mainwindow->listenSocket->listen(QHostAddress(ui->lineEdit->text()), 2333);
    connect(mainwindow->listenSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    ui->buttonBox->button(ui->buttonBox->Ok)->setEnabled(false);
    mainwindow->readWriteSocket = new QTcpSocket();
}

void DialogSetHost::acceptConnection()
{
    mainwindow->readWriteSocket = mainwindow->listenSocket->nextPendingConnection();
    this->accept();
}

void DialogSetHost::on_buttonBox_rejected()
{
    mainwindow->listenSocket->close();
    this->reject();
}
