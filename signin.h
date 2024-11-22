#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class signin;
}

class signin : public QWidget
{
    Q_OBJECT

public:
    explicit signin(QWidget *parent = nullptr);
    ~signin();
    QWidget* w;

private slots:
    void on_Sign_clicked();

private:
    Ui::signin *ui;
};

#endif // SIGNIN_H
