#include "dialogupgrade.h"
#include "ui_dialogupgrade.h"

DialogUpgrade::DialogUpgrade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpgrade)
{
    ui->setupUi(this);
}

DialogUpgrade::~DialogUpgrade()
{
    delete ui;
}
