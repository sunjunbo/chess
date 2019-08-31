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

private:
    Ui::DialogUpgrade *ui;
};

#endif // DIALOGUPGRADE_H
