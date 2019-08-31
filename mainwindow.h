#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtNetwork/QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void init();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer  *listenSocket;
    QTcpSocket *readWriteSocket;
private slots:
    void on_action_2_triggered();
    void set_host();
    void set_client();
private:
    Ui::MainWindow *ui;
    QPushButton * ButtonMap[9][9];
    bool is_host;//true 为主机，false 为客户端
};
extern MainWindow* mainwindow;
#endif // MAINWINDOW_H
