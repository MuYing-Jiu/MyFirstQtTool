#include "admin.h"
#include "ui_admin.h"
#include "oop.h"
#include "tt.h"
#include "menu.h"
#include <QSqlError>
#include "form.h"

extern int TryTimes;
extern QSqlDatabase db;

Admin::Admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);

    ui->TryTimes->setMinimum(2);
    ui->TryTimes->setMaximum(10);
    ui->TryTimes->setValue(TryTimes);

    Admin::on_SerchButton_clicked();

    setWindowTitle("--管理员配置-- 制作：Shadow");

}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_quit_clicked()
{
    this->close();
    oop* m =new oop;
    m ->show();
}


void Admin::on_Net_clicked()
{
    this->close();
    menu*m  =new menu;
    m -> show();
}


void Admin::on_TryTimes_valueChanged(int arg1)
{
    TryTimes = arg1;
}


void Admin::on_InsertButton_clicked()
{
    int id = ui->IDEdit->text().toInt();
    QString username = ui->UIDEdit->text();
    QString password = ui->KeyEdit->text();
    QString Isadmin = ui->AdminBox->currentText();
    QString Isvip = ui->VIPBox->currentText();
    bool isvip, isadmin;
    isvip = Isvip == QString::fromStdString("会员");
    isadmin = Isadmin == QString::fromStdString("管理员");

    QSqlQuery query;
    QString sqlInert = QString("insert into staff(username,password,isvip,isadmin) "
                               "values('%1','%2',%3,%4);")
                           .arg(username)
                           .arg(password)
                           .arg(isvip)
                           .arg(isadmin);
    if(!query.exec(sqlInert))
    {
        qDebug() << "Error insert into data" << db.lastError();
    }
    else
    {
        qDebug() << "Insert into data Successfully";
    }
    Admin::on_SerchButton_clicked();
}


void Admin::on_DeleteButton_clicked()
{
    int id = ui->IDEdit->text().toInt();
    QString username = ui->UIDEdit->text();
    QString password = ui->KeyEdit->text();
    QString Isadmin = ui->AdminBox->currentText();
    QString Isvip = ui->VIPBox->currentText();
    bool isvip, isadmin;
    isvip = Isvip == QString::fromStdString("会员");
    isadmin = Isadmin == QString::fromStdString("管理员");

    //[1]删除数据库中的记录
    QSqlQuery query;
    QString sqlDelete = QString("delete from staff where id = %1;").arg(id);
    if(!query.exec(sqlDelete))
    {
        qDebug() << "Error delete into data" << db.lastError();
    }
    Admin::on_SerchButton_clicked();
}


void Admin::on_UpdataButton_clicked()
{
    int id = ui->IDEdit->text().toInt();
    QString username = ui->UIDEdit->text();
    QString password = ui->KeyEdit->text();
    QString Isadmin = ui->AdminBox->currentText();
    QString Isvip = ui->VIPBox->currentText();

    bool isvip = (Isvip == "会员");
    bool isadmin = (Isadmin == "管理员");

    QSqlQuery query;



    // 构建更新SQL的基础部分
    QString sqlUpdate = "UPDATE staff SET ";
    bool first = true;  // 用于判断是否是第一个要更新的字段

    // 如果用户名不为空，加入更新条件
    if (!username.isEmpty()) {
        if (!first) sqlUpdate += ", ";  // 如果不是第一个字段，添加逗号分隔符
        sqlUpdate += QString("username = '%1'").arg(username);
        first = false;
    }

    // 如果密码不为空，加入更新条件
    if (!password.isEmpty()) {
        if (!first) sqlUpdate += ", ";
        sqlUpdate += QString("password = '%1'").arg(password);
        first = false;
    }

    // VIP加入更新条件
        if (!first) sqlUpdate += ", ";
        sqlUpdate += QString("isvip = %1").arg(isvip ? "1" : "0");
        first = false;


    // 管理员加入更新条件
        if (!first) sqlUpdate += ", ";
        sqlUpdate += QString("isadmin = %1").arg(isadmin ? "1" : "0");
        first = false;


    // 最后添加WHERE条件
    sqlUpdate += QString(" WHERE id = %1").arg(id);

    // 执行SQL更新
    if (!query.exec(sqlUpdate)) {
        qDebug() << "Error updating data: " << query.lastError();
    } else {
        qDebug() << "Data updated successfully!";
    }

    Admin::on_SerchButton_clicked();
}


void Admin::on_SerchButton_clicked()
{
    ui->listWidget->clear(); //在查询数据之前，清空列表上的内容
    QSqlQuery query;

    //[1]向数据库下达查询数据的命令
    QString sqlSelect = QString("select * from staff;");    //[1]查询数据库数据
    if(!query.exec(sqlSelect))
    {
        qDebug() << "Error insert into data" << db.lastError();
    }

    //[2]遍历数据库记录
    while (query.next()) {
        int id =   query.value("id").toInt();
        QString name = query.value("username").toString();
        QString pass = query.value("password").toString();
        int isvip = query.value("isvip").toInt();
        int isadmin =  query.value("isadmin").toInt();

        //qDebug() << "id = " << id << "name = " << name << "age = " << age <<
        //    "address = " << address << "salary = " << salary;

        //[3]每遍历一条记录，就要更新到UI控件上
        //[3.1] 创建一个列表条目
        Form* staffitem = new Form;
        staffitem->setStaffInfo(id,name,pass,isvip,isadmin);
        //[3.2] 创建ListWidget条目
        QListWidgetItem* item = new QListWidgetItem;

        item->setSizeHint(QSize(600,63));

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,staffitem);
    }

}

