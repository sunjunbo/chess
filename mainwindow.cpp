#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialogsethost.h"
MainWindow* mainwindow;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listenSocket = nullptr;
    readWriteSocket = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
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
