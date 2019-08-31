#ifndef DIALOGSETCLIENT_H
#define DIALOGSETCLIENT_H

#include <QDialog>

namespace Ui {
class DialogSetClient;
}

class DialogSetClient : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetClient(QWidget *parent = nullptr);
    ~DialogSetClient();

private slots:
    void on_buttonBox_accepted();
    void button_pressed(QString text);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_buttonBox_rejected();

private:
    Ui::DialogSetClient *ui;
};

#endif // DIALOGSETCLIENT_H
