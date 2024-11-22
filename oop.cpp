#include "oop.h"
#include "ui_oop.h"
//#include "widget.h"
#include "menu.h"
#include <QMessageBox>
#include <QKeyEvent>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


int ErrorCnt, TryTimes = 5; //Trytimes可以写在管理员界面
static QString username, password;

oop::oop(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::oop)
{
    ui->setupUi(this);

    setWindowTitle("--自制小工具-- 制作：Shadow");

}

oop::~oop()
{
    delete ui;
}

void oop::keyPressEvent(QKeyEvent *event)
{
    // 检查按下的键是否是回车键
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 如果按下回车键，模拟按钮点击
        ui->pushButton->click();
    }

    // 调用基类的 keyPressEvent 以保证其他键盘事件正常处理
    QWidget::keyPressEvent(event);
}

bool isadmin(QString str)
{
    QSqlQuery query;
    QString sqlCheck = QString("SELECT isadmin FROM staff WHERE username='%1' LIMIT 1;").arg(str);

    if(query.exec(sqlCheck))
    {
        if(query.next())
        {
            bool ans = query.value("isadmin").toBool();
            if(ans == true)
            {
                return true;
            }
        }
    }
    else
    {
        qDebug() << "Error checking isadmin existence: " << query.lastError();
    }
    return false;
}

bool isvipp(QString str)
{
    QSqlQuery query;
    QString sqlCheck = QString("SELECT isvip FROM staff WHERE username='%1' LIMIT 1;").arg(str);

    if(query.exec(sqlCheck))
    {
        if(query.next())
        {
            bool ans = query.value("isvip").toBool();
            if(ans == true)
            {
                return true;
            }
        }
    }
    else
    {
        qDebug() << "Error checking isvip existence: " << query.lastError();
    }
    return false;
}


bool isexistt(QString str)
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

bool ispasswordCorrect(QString str1, QString str2)
{
    QSqlQuery query;
    QString sqlCheck = QString("SELECT password FROM staff WHERE username='%1' LIMIT 1;").arg(str1);

    if(query.exec(sqlCheck))
    {
        if(query.next())
        {
            QString ans = query.value("password").toString();
            if(str2 == ans)
            {
                return true;
            }
        }
    }
    else
    {
        qDebug() << "Error checking username existence: " << query.lastError();
    }

    return false;  // 如果没有找到记录，返回 false
}



void oop::on_pushButton_clicked()
{
    username = ui->usernameEdit->text();
    password = ui->passwordEdit->text();

    if(!username.isEmpty() && !password.isEmpty())
    {
        if(isexistt(username))
        {
            if( ispasswordCorrect(username,password) )
            {
                if(!isadmin(username))
                {
                    if( isvipp(username) )
                    {
                        QMessageBox::information(this,"提示","尊敬的VIP用户 "+username+" ，您好！");
                    }
                    ErrorCnt = 0;
                    this->close();
                    menu*m  =new menu;
                    m ->show();
                }
                else
                {
                    ErrorCnt = 0;
                    this->close();
                    w =new Admin;
                    w->show();
                }
            }
            else
            {
                ErrorCnt++;
                if(ErrorCnt == TryTimes)
                {
                    QMessageBox::information(this,"提示","用户名或密码多次错误！");
                    this->close();
                }
                else
                {
                    QMessageBox::information(this,"提示","用户名或密码错误!剩余"+QString::number(TryTimes-ErrorCnt)+"次机会");
                    ui->passwordEdit->clear();  //+++
                }
            }

        }
        else
        {
            QMessageBox::information(this,"提示","该用户不存在，请先注册！");
        }
    }
    else
    {
        QMessageBox::information(this,"提示","账号或密码不得为空！");
    }

}


void oop::on_RegisterButton_clicked()
{
    this->close();
    q =new Register;
    q->show();
}

