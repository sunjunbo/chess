#ifndef DIALOGUPGRADE_H
#define DIALOGUPGRADE_H

#include <QDialog>

namespace Ui {
class DialogUpgrade;
}

class DialogUpgrade : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUpgrade(QWidget *parent = nullptr);
    ~DialogUpgrade();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DialogUpgrade *ui;
};

#endif // DIALOGUPGRADE_H
