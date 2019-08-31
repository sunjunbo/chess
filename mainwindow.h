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
    QIcon icons[2][7];
    int board[9][9];
    void setBoard();
    int* reverseBoard();
    bool canmove();
    int gettype(int x,int y);
    bool ismychess(int x,int y);
    void sethighlight(int x,int y);
private slots:
    void on_action_2_triggered();
    void on_action_3_triggered();
    void onButtonClicked(QPushButton b);
    void set_host();
    void set_client();
    void on_action_triggered();
    void rev_host();
    void rev_client();
private:
    bool click_from;
    int fromx;
    int fromy;
    Ui::MainWindow *ui;
    QPushButton * ButtonMap[9][9];
    bool is_host;//true 为主机，false 为客户端
    bool is_walking;//是否轮到自己走子
    void decode_board(QTextStream& in);
    void send_board();
    void send_walk();
    int string_to_cat(QString s);
    QPoint string_to_po(QString s);
};
extern MainWindow* mainwindow;
#endif // MAINWINDOW_H
