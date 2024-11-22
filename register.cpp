#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "oop.h"


extern QSqlDatabase db;

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    setWindowTitle("--注册-- 制作：Shadow");
}

Register::~Register()
{
    delete ui;
}

static QString username, password, confirmPassword,vipkey;
//std::string u, p, cp, v;


void SqlInsert(Ui::Register *ui,bool isvip, bool isadmin)//插入操作
{

    username = ui->usernameEdit->text();
    password = ui->passwordEdit->text();

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

}

bool isexist(QString str)
{
    QSqlQuery query;
    QString sqlCheck = QString("SELECT 1 FROM staff WHERE username='%1' LIMIT 1;").arg(str);

    if(query.exec(sqlCheck))
    {
        if(query.next())
        {
            return true;
        }
    }
    else
    {
        qDebug() << "Error checking username existence: " << query.lastError();
    }

    return false;  // 如果没有找到记录，返回 false
}

bool isvipkey(QString str)
{
    QSqlQuery query;
    QString sqlCheck = QString("SELECT 1 FROM vipkey WHERE keyword='%1' LIMIT 1;").arg(str);

    if(query.exec(sqlCheck))
    {
        if(query.next())
        {
            //修改
            return true;
        }
    }
    else
    {
        qDebug() << "Error checking username existence: " << query.lastError();
    }

    return false;  // 如果没有找到记录，返回 false
}

bool isused(QString str)
{
    QSqlQuery query;
    QString sqlCheck = QString("SELECT isused FROM vipkey WHERE keyword='%1' LIMIT 1;").arg(str);

    if(query.exec(sqlCheck))
    {
        if(query.next())
        {
            // 记录存在，获取当前的 isused 值
            bool currentIsUsed = query.value("isused").toBool();

            // 假设你需要修改数据库中的 isused 值
            // 比如，将 isused 字段的值更新为当前值的反转（只做演示）
            if(currentIsUsed == 0)
            {
                bool newIsUsedValue = !currentIsUsed;

                // 更新数据库
                QString sqlUpdate = QString("UPDATE vipkey SET isused=%1 WHERE keyword='%2';")
                                        .arg(newIsUsedValue)
                                        .arg(str);
                if (query.exec(sqlUpdate))
                {
                    qDebug() << "Database updated successfully!";
                }
                else
                {
                    qDebug() << "Error updating database: " << query.lastError();
                }
            }
            // 返回当前的 isused 状态
            return currentIsUsed;
        }
        else
        {
            qDebug() << "No record found for keyword: " << str;
        }
    }
    else
    {
        qDebug() << "Error checking keyword existence: " << query.lastError();
    }

    return false;  // 如果没有找到记录或更新失败，返回 false
}

void Register::on_pushButton_clicked()
{
    username = ui->usernameEdit->text();
    password = ui->passwordEdit->text();
    confirmPassword = ui->confirm_passwordEdit->text();
    vipkey = ui->vipkeyeEdit->text();

    if(!username.isEmpty() && !password.isEmpty())
    {
        if(!confirmPassword.isEmpty())
        {
            if(password == confirmPassword)
            {
                if( !isexist(username) )
                {
                    if(!vipkey.isEmpty())
                    {
                        if( isvipkey(vipkey) )
                        {
                            if(!isused(vipkey))
                            {
                                SqlInsert(ui,1,0);  //insert vip
                                QMessageBox::information(this,"提示","尊敬的VIP用户您好！\n您已成功注册！\n请牢记你的账号密码，返回登陆界面重新登陆");
                            }
                            else
                            {
                                QMessageBox::information(this,"提示","这是正确的VIP激活码，但它已失效！");
                                ui->vipkeyeEdit->clear();
                            }
                        }
                        else
                        {
                            QMessageBox::information(this,"提示","VIP激活码不正确！");
                            ui->vipkeyeEdit->clear();
                        }
                    }
                    else
                    {
                        SqlInsert(ui,0,0);  //insert notvip
                        QMessageBox::information(this,"提示","注册成功！\n请牢记你的账号密码，返回登陆界面重新登陆");
                    }
                }
                else    //数据库是否已经有此账号
                {
                    QMessageBox::information(this,"提示","用户已存在！");
                    ui->usernameEdit->clear();
                }
            }
            else
            {
                QMessageBox::information(this,"提示","两次输入的密码不一致！");
                ui->passwordEdit->clear();
                ui->confirm_passwordEdit->clear();
            }
        }
        else
        {
            QMessageBox::information(this,"提示","“确认密码”栏不得为空，请重复输入密码！");
        }
    }
    else
    {
        QMessageBox::information(this,"提示","账号或密码不得为空！");
    }
}

void Register::on_backButton_clicked()
{
    this->close();
    oop* m =new oop;
    m ->show();
}

