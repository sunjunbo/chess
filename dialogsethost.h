#ifndef DIALOGSETHOST_H
#define DIALOGSETHOST_H

#include <QDialog>
#include<QtGui>
namespace Ui {
class DialogSetHost;
}

class DialogSetHost : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetHost(QWidget *parent = nullptr);
    ~DialogSetHost();
signals:
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogSetHost *ui;
};

#endif // DIALOGSETHOST_H
