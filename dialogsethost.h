#ifndef DIALOGSETHOST_H
#define DIALOGSETHOST_H

#include <QDialog>
#include<QtGui>
#include"mainwindow.h"
namespace Ui {
class DialogSetHost;
}

class DialogSetHost : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetHost(QWidget *parent = nullptr);
    void listening_thread();
    QThread* thread;
    ~DialogSetHost();
signals:
private slots:
    void acceptConnection();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DialogSetHost *ui;
};

#endif // DIALOGSETHOST_H
