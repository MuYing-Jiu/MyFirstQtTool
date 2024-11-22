#ifndef OOP_H
#define OOP_H

#include <QWidget>
#include "tt.h"
#include "admin.h"
#include "register.h"
namespace Ui {
class oop;
}

class oop : public QWidget
{
    Q_OBJECT

public:
    explicit oop(QWidget *parent = nullptr);
    ~oop();
    Widget*ww;
    Admin*w;
    Register*q;

private slots:
    void on_pushButton_clicked();


    void on_RegisterButton_clicked();

private:
    Ui::oop *ui;
    void keyPressEvent(QKeyEvent *event);
     QSqlDatabase db;
};

#endif // OOP_H
