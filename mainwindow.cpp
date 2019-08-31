﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialogsethost.h"
#include "dialogsetclient.h"
#include <QFileDialog>
#include<QGridLayout>
#include<QTcpSocket>
MainWindow* mainwindow;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listenSocket = nullptr;
    readWriteSocket = nullptr;
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    int width = 60;
    int x=50;
    int y=50;

    icons[1][1]=QIcon(":/c/pic/black_rook.png");// 车
    icons[1][2]=QIcon(":/c/pic/black_knight.png");// 马
    icons[1][3]=QIcon(":/c/pic/black_bishop.png");// 象
    icons[1][4]=QIcon(":/c/pic/black_king.png");// 王
    icons[1][5]=QIcon(":/c/pic/black_queen.png");// 后
    icons[1][6]=QIcon(":/c/pic/black_pawn.png");// 兵

    icons[2][1]=QIcon(":/c/pic/white_rook.png");
    icons[2][2]=QIcon(":/c/pic/white_knight.png");
    icons[2][3]=QIcon(":/c/pic/white_bishop.png");
    icons[2][4]=QIcon(":/c/pic/white_king.png");
    icons[2][5]=QIcon(":/c/pic/white_queen.png");
    icons[2][6]=QIcon(":/c/pic/white_pawn.png");
    QGridLayout *layout = ui->gridLayout;
    layout->setSpacing(0);
    for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        {
            ButtonMap[i][j]=new QPushButton(this);
            ButtonMap[i][j]->setFixedSize(60,60);
            ButtonMap[i][j]->setIconSize(QSize(60,60));
            if((i+j)%2==1)
                ButtonMap[i][j]->setStyleSheet("background-color: rgb(235, 207, 167)");
            else
                ButtonMap[i][j]->setStyleSheet("background-color: rgb(109, 114, 63)");
            layout->addWidget(ButtonMap[i][j],i,j);
        }
}

void MainWindow::on_action_2_triggered()
{
    DialogSetHost* dialog = new DialogSetHost();
    if(dialog->exec() == QDialog::Accepted){
        set_host();
        connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(rev_host()));
    }
}
void MainWindow::setBoard()
{
    int s;
    if(is_host) s=1;
    else s=0;
    for(int i=1;i<=2;i++)
        for(int j=1;j<=8;j++)
            ButtonMap[i][j]->setIcon(icons[s][(2*s-1)*board[i][j]]);
    for(int i=8;i<=7;i--)
        for(int j=1;j<=8;j++)
            ButtonMap[i][j]->setIcon(icons[s][(2*s-1)*board[i][j]]);
}
void MainWindow::set_host()
{   
    //作为服务器初始化，小红帽写
    //此时双方链接已经建立
    int myboard[9][9] = {
        0,0,0,0,0,0,0,0,0,
        0,1,2,3,4,5,3,2,1,
        0,6,6,6,6,6,6,6,6,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,-6,-6,-6,-6,-6,-6,-6,-6,
        0,-1,-2,-3,-4,-5,-3,-2,-1
    };
    memcpy(board,myboard,sizeof(myboard));
    setBoard();
}

void MainWindow::set_client()
{
    //作为客户端初始化，小红帽写
    //此时双方链接已经建立
    int myboard[9][9] = {
        0,0,0,0,0,0,0,0,0,
        0,1,2,3,4,5,3,2,1,
        0,6,6,6,6,6,6,6,6,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,-6,-6,-6,-6,-6,-6,-6,-6,
        0,-1,-2,-3,-4,-5,-3,-2,-1
    };
    memcpy(board,myboard,sizeof(myboard));
    setBoard();
}

void MainWindow::on_action_triggered()
{
    //载入文件
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("载入存档"), "", tr("存档(*.txt)"));
}

void MainWindow::on_action_3_triggered()
{
    DialogSetClient* dialog = new DialogSetClient();
    if(dialog->exec() == QDialog::Accepted){
        set_client();
        connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(rev_client()));
    }
}

void MainWindow::rev_host()
{
    QByteArray buf = this->readWriteSocket->readAll();
}

void MainWindow::rev_client()
{
    QByteArray buf = this->readWriteSocket->readAll();
}
