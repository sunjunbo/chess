#include "dialogupgrade.h"
#include "ui_dialogupgrade.h"
#include"mainwindow.h"
DialogUpgrade::DialogUpgrade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpgrade)
{
    ui->setupUi(this);
    ui->pushButton->setIcon(mainwindow->icons[1][1]);
    ui->pushButton_2->setIcon(mainwindow->icons[1][2]);
    ui->pushButton_3->setIcon(mainwindow->icons[1][3]);
    ui->pushButton_4->setIcon(mainwindow->icons[1][5]);
}

DialogUpgrade::~DialogUpgrade()
{
    delete ui;
}

void DialogUpgrade::on_pushButton_clicked()
{
    done(1);
}

void DialogUpgrade::on_pushButton_3_clicked()
{
    done(3);
}

void DialogUpgrade::on_pushButton_2_clicked()
{
    done(2);
}

void DialogUpgrade::on_pushButton_4_clicked()
{
    done(5);
}
