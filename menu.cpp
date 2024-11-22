#include "menu.h"
#include "ui_menu.h"
#include "oop.h"
#include "ser.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    setWindowTitle("--菜单-- 制作：Shadow");
}

menu::~menu()
{
    delete ui;
}

void menu::on_TcpButton_clicked()
{
    this->close();
    Widget* m =new Widget;
    m ->show();
}


void menu::on_SerialButton_clicked()
{
    this->close();
    ser* m =new ser;
    m->show();
}


void menu::on_BackButton_clicked()
{
    this->close();
    oop*m = new oop;
    m->show();
}

