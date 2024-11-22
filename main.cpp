#include "tt.h"
#include <QApplication>
#include "oop.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "register.h"
//#include "ser.h"

QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("staff.db");

    //如果想要进一步操作数据库，那么，就必须要进行数据库打开操作
    if(!db.open())
    {

        qDebug() << "Error falied to open" << db.lastError();
    }else
    {
        qDebug() << "open sucess";
    }
    #if 1
    QSqlQuery query;
    //定义一条创建表的sql语句  表名：staff  表中的字段：id  name age
    QString sqlCreate1 = QString("create table staff(id integer primary key autoincrement,username varchar(32),password varchar(32),isvip bool,isadmin bool);");
    if(!query.exec(sqlCreate1))
    {
        qDebug() << "create table error" << db.lastError();
    }

    QString sqlCreate2 = QString("create table vipkey(id integer primary key autoincrement,keyword varchar(32),isused bool);");
    if(!query.exec(sqlCreate2))
    {
        qDebug() << "create table error" << db.lastError();
    }
    #endif


    //create table vipkey(id integer primary key autoincrement,keyword varchar(32),isused bool);



    oop p;
    p.show();

    QStringList drivers =  QSqlDatabase::drivers(); //获取到qt中所支持的数据库驱动类型

    foreach(QString driver,drivers)
    {
        qDebug() << driver;
    }
    
    return a.exec();
}
