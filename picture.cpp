#include "picture.h"
#include "ui_picture.h"
#include "ser.h"

Picture::Picture(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Picture)
{
    ui->setupUi(this);
    setWindowTitle("--合照彩蛋--");
}

Picture::~Picture()
{
    delete ui;
}

void Picture::on_pushButton_clicked()
{
    this->close();
    ser*s = new ser;
    s->show();
}

