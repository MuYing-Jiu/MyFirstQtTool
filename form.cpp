#include "form.h"
#include "ui_form.h"
#include <QSqlError>
#include <QSqlDatabase>

extern QSqlDatabase db;

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
}

void Form::setStaffInfo(int id, QString name, QString key, bool isvip, bool isadmin)
{
    ui->label_id->setText(QString::number(id));
    ui->label_uid->setText(name);
    ui->label_key->setText(key);
    ui->label_isvip->setText(QString::number(isvip));
    ui->label_isadmin->setText(QString::number(isadmin));
}

Form::~Form()
{
    delete ui;
}
