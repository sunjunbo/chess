#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialogsethost.h"
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
    ButtonMap[1][1]->setIcon(QIcon(":/c/pic/black_bishop.png"));
}


void MainWindow::on_action_2_triggered()
{
    DialogSetHost* dialog = new DialogSetHost();
    dialog->exec();
}

void MainWindow::set_host()
{

}

void MainWindow::set_client()
{

}

void MainWindow::on_action_triggered()
{

}
