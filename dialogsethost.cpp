#include "dialogsethost.h"
#include "ui_dialogsethost.h"

DialogSetHost::DialogSetHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetHost)
{
    ui->setupUi(this);
}

DialogSetHost::~DialogSetHost()
{
    delete ui;
}

void DialogSetHost::on_buttonBox_accepted()
{

}
