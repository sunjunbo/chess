#include "dialogsetclient.h"
#include "ui_dialogsetclient.h"
#include"mainwindow.h"
#include <QRegExpValidator>
#include<QMessageBox>
#include <QTcpSocket>
DialogSetClient::DialogSetClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetClient)
{
    ui->setupUi(this);
}

DialogSetClient::~DialogSetClient()
{
    delete ui;
}

void DialogSetClient::on_buttonBox_accepted()
{
    delete mainwindow->listenSocket;
    delete mainwindow->readWriteSocket;
    mainwindow->listenSocket = nullptr;
    mainwindow->readWriteSocket = nullptr;
    QRegExp rx("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
    QValidator *validator = new QRegExpValidator(rx, this);
    QString s = ui->lineEdit->text();
    int pos = 0;
    if(!validator->validate(s, pos)){
        QMessageBox::about(this,tr("IP地址非法"),tr("IP地址非法"));
        return;
    }
    mainwindow->readWriteSocket = new QTcpSocket();
    mainwindow->readWriteSocket->connectToHost(QHostAddress(ui->lineEdit->text()),2333);
    this->accept();
}

void DialogSetClient::on_buttonBox_rejected()
{
    this->reject();
}
void DialogSetClient::button_pressed(QString text)
{
    if(text.front().isDigit() || text.front() == '.'){
        ui->lineEdit->setText(ui->lineEdit->text() + text.front());
    }
    else if (!ui->lineEdit->text().isEmpty()) {
        QString s = ui->lineEdit->text();
        s.chop(1);
        ui->lineEdit->setText(s);
    }
}

void DialogSetClient::on_pushButton_clicked()
{
    button_pressed(ui->pushButton->text());
}

void DialogSetClient::on_pushButton_2_clicked()
{
    button_pressed(ui->pushButton_2->text());
}

void DialogSetClient::on_pushButton_3_clicked()
{
    button_pressed(ui->pushButton_3->text());
}

void DialogSetClient::on_pushButton_4_clicked()
{
    button_pressed(ui->pushButton_4->text());
}

void DialogSetClient::on_pushButton_5_clicked()
{
    button_pressed(ui->pushButton_5->text());
}

void DialogSetClient::on_pushButton_11_clicked()
{
    button_pressed(ui->pushButton_11->text());
}

void DialogSetClient::on_pushButton_6_clicked()
{
    button_pressed(ui->pushButton_6->text());
}

void DialogSetClient::on_pushButton_7_clicked()
{
    button_pressed(ui->pushButton_7->text());
}

void DialogSetClient::on_pushButton_8_clicked()
{
    button_pressed(ui->pushButton_8->text());
}

void DialogSetClient::on_pushButton_9_clicked()
{
    button_pressed(ui->pushButton_9->text());
}

void DialogSetClient::on_pushButton_10_clicked()
{
    button_pressed(ui->pushButton_10->text());
}

void DialogSetClient::on_pushButton_12_clicked()
{
    button_pressed(ui->pushButton_12->text());
}


