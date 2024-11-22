#include "signin.h"
#include "ui_signin.h"

signin::signin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::signin)
{
    ui->setupUi(this);
}

signin::~signin()
{
    delete ui;
}

void signin::on_Sign_clicked()
{
    this->close();
    w = new Widget;
    w -> show();
}

