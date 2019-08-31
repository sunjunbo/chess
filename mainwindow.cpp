#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialogsethost.h"
#include "dialogsetclient.h"
#include <QFileDialog>
#include<QGridLayout>
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
    int myside = 1;//or 8
}

void MainWindow::on_action_2_triggered()
{
    DialogSetHost* dialog = new DialogSetHost();
    if(dialog->exec() == QDialog::Accepted){
        set_host();
    }
}

void MainWindow::set_host()
{   
    //作为服务器初始化，小红帽写
    //此时双方链接已经建立
    for(int i=1;i<=4;i++)
    {
        ButtonMap[1][i]->setIcon(icons[1][i]);
        ButtonMap[1][8-i]->setIcon(icons[1][i]);
    }
    ButtonMap[1][5]->setIcon(icons[1][5]);
    for(int i=1;i<=8;i++)
    {
        ButtonMap[2][i]->setIcon(icons[1][6]);
    }
    for(int i=1;i<=4;i++)
    {
        ButtonMap[8][i]->setIcon(icons[2][i]);
        ButtonMap[8][8-i]->setIcon(icons[2][i]);
    }
    ButtonMap[8][5]->setIcon(icons[2][5]);
    for(int i=1;i<=8;i++)
    {
        ButtonMap[7][i]->setIcon(icons[2][6]);
    }
}

void MainWindow::set_client()
{
    //作为客户端初始化，小红帽写
    //此时双方链接已经建立
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
    }
}
