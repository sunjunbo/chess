#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT




public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void set_host(QString host);//设置此为服务器，并设置服务器监听IP，端口号为2333
private:
    Ui::MainWindow *ui;
    bool is_host;//true 为主机，false 为客户端
};
static MainWindow* mainwindow;
#endif // MAINWINDOW_H
