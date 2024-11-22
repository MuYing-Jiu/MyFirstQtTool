#include "tt.h"
#include "ui_tt.h"
#include <QTextCodec>
#include <QMessageBox>
#include "menu.h"
#include <QSqlError>

//#include <string>

bool MS = true;//t 主机
bool flag_Sw=false;//
int swi = 0;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);




    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);

    //默认使用主机模式，等待新的连接
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection_Slot()));

    setFixedSize(480,420);
    //默认端口号 8080
    ui->portEdit->setText("8266");
    ui->ipED->setText("192.168.1.15");

    setWindowTitle("--局域网络调试器-- 制作：Shadow");



}

//检测是否有新连接进来
void Widget::newConnection_Slot(){

    tcpSocket=tcpServer->nextPendingConnection();//得到通信的套接字对象
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));

    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected_Slot()));
    // ui->label_3->setText("已连接");
    ui->label_3->setStyleSheet("border-image: url(:/new/prefix1/connect.png)");
}

//服务器或客户机连接状态
void Widget::disconnected_Slot(){

    tcpSocket->close();
    ui->label_3->setStyleSheet("border-image: url(:/new/prefix1/discon.png)");
    ui->Send1Button->setStyleSheet("border-image: url(:/new/prefix1/lightoff.jpg)");//小灯泡
}


//客户机连接
void Widget::connected_Slot(){

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));
   // ui->label_3->setText("已连接");
    ui->label_3->setStyleSheet("border-image: url(:/new/prefix1/connect.png)");

    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected_Slot()));
}

//有内容进来调用

void Widget::readyRead_Slot(){
 /*   QString buf;
    buf = tcpSocket->readAll();
    ui->RecvEdit->appendPlainText(buf);*/

    QByteArray receiveDate;
    QTextCodec *tc = QTextCodec::codecForName("GBK");  //编码转换,必须转换编码，否则乱码

    while(!tcpSocket->atEnd()){
        receiveDate = tcpSocket->readAll();
    }

    if (!receiveDate.isEmpty())
    {
        QString strBuf=tc->toUnicode(receiveDate);         //编码转换,必须转换编码，否则乱码
       // COMRXtextBrowser->append(strBuf);
        ui->RecvEdit->appendPlainText(strBuf);
        ui->LightNumber->display(strBuf);
        int value = strBuf.toInt();
        int f = 600;
        if(value > f)
        {
            ui->label_warnpicture->setStyleSheet("border-image: url(:/new/prefix1/warn1.png)");
        } else{

            ui->label_warnpicture->setStyleSheet("border-image: url(:/new/prefix1/warn.png)");
        }
    }



    receiveDate.clear();
}

Widget::~Widget()
{
    delete ui;
}
//打开网络/关闭网络
void Widget::on_openBt_clicked()
{

    flag_Sw=!flag_Sw;
    if(flag_Sw){

        //选择主机
        if(MS)
        {
            //必须去掉，否则切换为主机时候，主机不能用
            //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection_Slot()));
            tcpServer->listen(QHostAddress::Any,ui->portEdit->text().toUInt());
        }
        else//客户机
        {
            tcpSocket->connectToHost(ui->ipED->text(),ui->portEdit->text().toUInt());
            connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected_Slot()));
        }
        ui->openBt->setStyleSheet("border-image: url(:/new/prefix1/open.png)");
        ui->wifi->setStyleSheet("border-image: url(:/new/prefix1/wifi_on.png)");
    }
    else{
        tcpServer->close();
        tcpSocket->close();
        ui->openBt->setStyleSheet("border-image: url(:/new/prefix1/close.png)");
        ui->wifi->setStyleSheet("border-image: url(:/new/prefix1/wifi_off.png)");
    }
}
//发送数据
void Widget::on_sendBt_clicked()
{
    QString SendCon =  ui->sendEdit->text().toLocal8Bit().data();

    if(flag_Sw){

        if(SendCon!=""){

            //封装编码
            QByteArray receiveDate;
            QTextCodec *tc = QTextCodec::codecForName("GBK");  //编码转换,必须转换编码，否则乱码

            //对发送框编码
            receiveDate =  ui->sendEdit->text().toLocal8Bit().data();
            QString strBuf=tc->toUnicode(receiveDate);

            //整合符号 ->
            QString  str = "->";
            QString str2 = str.append(strBuf);

             //向输出框打印发送的数据
             ui->RecvEdit->appendPlainText(str2);
             tcpSocket->write(ui->sendEdit->text().toLocal8Bit().data());
        }

        else
         QMessageBox::critical(this,"警告","不能发送空白信息");
   }
    else
       QMessageBox::critical(this,"提示","发送失败，网络尚未连接");

}


//清空窗口
void Widget::on_clearBt_clicked()
{
      ui->RecvEdit->clear();
}

//按下发送
void Widget::on_sendBt_pressed()
{
    ui->sendBt->setStyleSheet("border-image: url(:/new/prefix1/send_a.png)");
}
//抬起发送
void Widget::on_sendBt_released()
{
    ui->sendBt->setStyleSheet("border-image: url(:/new/prefix1/send.png)");
}

//按下清空
void Widget::on_clearBt_pressed()
{
    ui->clearBt->setStyleSheet("border-image: url(:/new/prefix1/clear_a.png)");
}

//抬起清空
void Widget::on_clearBt_released()
{
    ui->clearBt->setStyleSheet("border-image: url(:/new/prefix1/clear_b.png)");
}

//清空输入  按下
void Widget::on_clearS_pressed()
{
    ui->sendEdit->clear();
    ui->clearS->setStyleSheet("border-image: url(:/new/prefix1/clearS_a.png)");
}

//清空输入 抬起
void Widget::on_clearS_released()
{
    ui->clearS->setStyleSheet("border-image: url(:/new/prefix1/clearS.png)");
}

//主副机切换
void Widget::on_ms_clicked()
{
 if(!flag_Sw)
 {
    //全关闭
    tcpServer->close();
    tcpSocket->close();
    //客户机
    if(MS){
        MS=false;
        ui->label->setText("客户机模式");
        ui->ms->setStyleSheet("border-image: url(:/new/prefix1/client.png);");
    }

    else//主机
    {
        MS=true;
        //必须注销，否则切换为主机时候，主机不能用
        //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection_Slot()));

        ui->label->setText("主机模式");
        ui->ms->setStyleSheet("border-image: url(:/new/prefix1/server.png);");
    }
 }
 else
    QMessageBox::critical(this,"提示","请先关闭网络，再切换模式类型");
}


void Widget::on_Send1Button_clicked()
{
    QString SendCon =  ui->sendEdit->text().toLocal8Bit().data();

    if(flag_Sw){


            QString buf;
            buf = tcpSocket->readAll();
            ui->RecvEdit->appendPlainText(buf);
            if(swi == 1)
            {
                tcpSocket->write("1");
                swi = 0;
                ui->Send1Button->setStyleSheet("border-image: url(:/new/prefix1/open.png)");
                ui->label_Send1->setStyleSheet("border-image: url(:/new/prefix1/lllon.png)");
                //ui->label_3->setStyleSheet("border-image: url(:/new/prefix1/connect.png)");
            }
            else if(swi == 0)
            {
                tcpSocket->write("0");
                swi = 1;
                ui->Send1Button->setStyleSheet("border-image: url(:/new/prefix1/close.png)");
                ui->label_Send1->setStyleSheet("border-image: url(:/new/prefix1/lll.png)");
                //ui->openBt->setStyleSheet("border-image: url(:/new/prefix1/close.png)");
            }
    }
    else
        QMessageBox::critical(this,"提示","发送失败，网络尚未连接");

}


void Widget::on_back_clicked()
{
    this->close();
    menu* m =new menu;
    m ->show();
}

