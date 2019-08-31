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
    icons[0][1]=QIcon(":/c/pic/black_rook.png");// 车
    icons[0][2]=QIcon(":/c/pic/black_knight.png");// 马
    icons[0][3]=QIcon(":/c/pic/black_bishop.png");// 象
    icons[0][4]=QIcon(":/c/pic/black_king.png");// 王
    icons[0][5]=QIcon(":/c/pic/black_queen.png");// 后
    icons[0][6]=QIcon(":/c/pic/black_pawn.png");// 兵

    icons[1][1]=QIcon(":/c/pic/white_rook.png");
    icons[1][2]=QIcon(":/c/pic/white_knight.png");
    icons[1][3]=QIcon(":/c/pic/white_bishop.png");
    icons[1][4]=QIcon(":/c/pic/white_king.png");
    icons[1][5]=QIcon(":/c/pic/white_queen.png");
    icons[1][6]=QIcon(":/c/pic/white_pawn.png");
    QGridLayout *layout = ui->gridLayout;
    layout->setSpacing(0);
    for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        {
            ButtonMap[i][j]=new QPushButton(this);
            ButtonMap[i][j]->setFixedSize(60,60);
            ButtonMap[i][j]->setIconSize(QSize(60,60));
            connect( ButtonMap[i][j],SIGNAL(clicked(bool)),this,SLOT(onButtonClicked(i,j)));
            if((i+j)%2==1)
                ButtonMap[i][j]->setStyleSheet("background-color: rgb(235, 207, 167)");
            else
                ButtonMap[i][j]->setStyleSheet("background-color: rgb(109, 114, 63)");
            layout->addWidget(ButtonMap[i][j],i,j);
        }
}
void MainWindow::onButtonClicked(int x,int y){
    if(!click_from)
    {
        if(gettype(x,y)!=0&&ismychess(x,y)){
            fromx=x;fromy=y;
            sethighlight(x,y);
            click_from=1;
        }
    }
    else{
        // 更换走子
        if(gettype(x,y)!=0&&ismychess(x,y)){
            origincolor(fromx,fromy);
            sethighlight(x,y);
            fromx=x;fromy=y;
            return;
        }
        // 走过去
        if(canmove(x,y)){
            move(x,y);
            click_from=0;
            origincolor(fromx,fromy);
        }
    }
}
void MainWindow::sethighlight(int x,int y)
{
    ButtonMap[x][y]->setStyleSheet("background-color: rgb(76, 84, 43)");
}
void MainWindow::origincolor(int i,int j){
    if((i+j)%2==1)
        ButtonMap[i][j]->setStyleSheet("background-color: rgb(235, 207, 167)");
    else
        ButtonMap[i][j]->setStyleSheet("background-color: rgb(109, 114, 63)");
}
// 根据棋子种类判断是否可移动
bool MainWindow::canmove(int x,int y){

}
int MainWindow::gettype(int x,int y){
    int type;
    if(is_host)
        type = abs(board[x][y]);
    else
        type = abs(board[9-x][y]);
    return type;
}
bool MainWindow::ismychess(int i,int j){
    if(is_host)
    {
        if(board[i][j]<0)return true;
        else return false;
    }
    else{
        if(board[9-i][j]>0)return true;
        else return false;
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
    if(is_host)
    {
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++){
                if(board[i][j]>0)
                    ButtonMap[i][j]->setIcon(icons[0][board[i][j]]);
                else
                    ButtonMap[i][j]->setIcon(icons[1][-board[i][j]]);
            }
    }
    else{
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++){
                if(board[9-i][j]>0)
                    ButtonMap[i][j]->setIcon(icons[0][board[9-i][j]]);

                else
                    ButtonMap[i][j]->setIcon(icons[1][-board[9-i][j]]);
            }
    }
}

void MainWindow::set_host()
{   
    //作为服务器初始化，小红帽写
    //此时双方链接已经建立
    is_host=1;
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
    send_board();
}

void MainWindow::set_client()
{
    //作为客户端初始化，小红帽写
    //此时双方链接已经建立
    setBoard();
}
//服务器载入存档
void MainWindow::on_action_triggered()
{
    if(!is_host)
        return;
    //载入文件
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("载入存档"), "", tr("存档(*.txt)"));
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString t;
        in >> t;
        if(t == "white"){
            is_walking = true;
        }else{
            is_walking = false;
            send_walk();
        }
        memset(board, 0, sizeof(board));
        int color = is_walking;
        while(!in.atEnd()){
            in >> t;
            if(t == "white" || t == "black"){
                color ^= 1;
                continue;
            }
            int type = string_to_cat(t);
            int n;
            in >> n;
            for(int i = 1; i <= n; ++i){
                QString pos;
                in >> pos;
                QPoint p = string_to_po(pos);
                if(color == 1){
                    board[p.x()][p.y()] = type;
                }else{
                    board[p.x()][p.y()] = -type;
                }
            }
        }
    }
    setBoard();
    send_board();
}

void MainWindow::on_action_3_triggered()
{
    DialogSetClient* dialog = new DialogSetClient();
    if(dialog->exec() == QDialog::Accepted){
        set_client();
        connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(rev_client()));
    }
}
//双方通信
//mode:1.send_board
//2.for you to walk
void MainWindow::rev_host()
{
    QByteArray buf = this->readWriteSocket->readAll();
    QString* s = new QString(buf);
    QTextStream stream(s,  QIODevice::ReadOnly);
    int mode;
    stream >> mode;
    if(mode == 1){
        decode_board(stream);
        setBoard();
    }
    if(mode == 2){
        is_walking  = true;
    }
}

void MainWindow::rev_client()
{
    QByteArray buf = this->readWriteSocket->readAll();
    QString* s = new QString(buf);
    QTextStream stream(s,  QIODevice::ReadOnly);
    int mode;
    stream >> mode;
    if(mode == 1){
        decode_board(stream);
        setBoard();
    }
    if(mode == 2){
        is_walking  = true;
    }
}

void MainWindow::decode_board(QTextStream &in)
{
    for(int i = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
            in >> board[i][j];
}
//向对方发送棋局
void MainWindow::send_board()
{
    QString s;
    QTextStream out(&s);
    out << 1 << ' ';
    for(int i = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
            out << board[i][j] << ' ';
    readWriteSocket->write(s.toStdString().c_str());
}
//要求对方走子
void MainWindow::send_walk()
{
    QString s;
    QTextStream out(&s);
    out << 2 << ' ';
    readWriteSocket->write(s.toStdString().c_str());
}

int MainWindow::string_to_cat(QString s)
{
    if(s == "rook")
        return 1;
    if(s == "knight")
        return 2;
    if(s == "bishop")
        return 3;
    if(s == "king")
        return 4;
    if(s == "queen")
        return 5;
    if(s == "pawn")
        return 6;
}

QPoint MainWindow::string_to_po(QString s)
{

    return QPoint(s.toStdString()[1] - '0' + 1, s.toStdString()[0] - 'a' + 1);
}


