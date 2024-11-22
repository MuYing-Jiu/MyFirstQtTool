#include "ser.h"
#include "ui_ser.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QSerialPort>
#include <QMessageBox>
#include <cstring>
#include <menu.h>
#include "picture.h"

long int SendCnt = 0, ReciCnt = 0;

ser::ser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ser)
{
    ui->setupUi(this);

    setWindowTitle("--串口助手-- 制作：Shadow");

    /**声明一个串口变量**/
    serialport = new QSerialPort(this);


    /***查找串口：设置串口下拉框自动读取的串口***/
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())	{
        QStringList Portname;//portname：最终显示在串口下拉框的内容，例如COM1
        Portname<<info.portName();
        ui->Number_port->addItems(Portname);//下拉框显示能够用的串口端口
    }//获取过程

    /**手动关联接收信号和在窗口显示的槽函数**/
    connect(serialport,SIGNAL(readyRead()),this,SLOT(serial_read_show()));

    ui->SendText->setText("Send:0");
    ui->ReciveText->setText("Recieve:0");

}

ser::~ser()
{
    delete ui;
}

void ser::on_OpenButton_clicked()
{
    /***定义变量****/
    QSerialPort::BaudRate   Baudrate;
    QSerialPort::DataBits   Databits;
    QSerialPort::StopBits   Stopbits;
    QSerialPort::Parity     Checkbit;

    //波特率
    if(ui->BitRate->currentText()=="9600"){
        Baudrate = QSerialPort::Baud9600;
    }
    else if (ui->BitRate->currentText()=="115200") {
        Baudrate = QSerialPort::Baud115200;
    }

    //数据位
    if(ui->DataBit->currentText()=="5"){
        Databits=QSerialPort::Data5;
    }else if (ui->DataBit->currentText()=="6") {
        Databits=QSerialPort::Data6;
    }else if (ui->DataBit->currentText()=="7") {
        Databits=QSerialPort::Data7;
    }else if (ui->DataBit->currentText()=="8") {
        Databits=QSerialPort::Data8;
    }

    //停止位Q
    if(ui->StopBit->currentText()=="1"){
        Stopbits=QSerialPort::OneStop;
    }else if (ui->StopBit->currentText()=="1.5") {
        Stopbits=QSerialPort::OneAndHalfStop;
    }else if (ui->StopBit->currentText()=="2") {
        Stopbits=QSerialPort::TwoStop;
    }
    //校验位
    if(ui->CheckBit->currentText()=="None"){
        Checkbit=QSerialPort::NoParity;
    }

    serialport->setPortName(ui->Number_port->currentText());
    serialport->setBaudRate(Baudrate);
    serialport->setDataBits(Databits);
    serialport->setStopBits(Stopbits);
    serialport->setParity(Checkbit);

    if(serialport->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this,"串口打开情况","成功");
        ui->label_led->setStyleSheet("border-image: url(:/image/green.svg)");
    }
    else
    {
        QMessageBox::information(this,"串口打开情况","失败");
    }


}

void ser::on_CloseButton_clicked()
{
    serialport->close();
    QMessageBox::information(this,"串口关闭情况","成功");
    ui->label_led->setStyleSheet("border-image: url(:/image/red.svg)");
}


void ser::on_SendButton_clicked()
{
    SendCnt++;
    serialport->write(ui->InputEdit->toPlainText().toLocal8Bit().data());

    QString in,out;
    in = ui->InputEdit->toPlainText();
    out = ui->OutputEdit->toPlainText();
    if(in.isEmpty() && out.toStdString()=="NO.1")
    {
        this->close();
        Picture*p = new Picture;
        p->show();

    }
    ui->SendText->clear();
    ui->SendText->setText("Send:"+QString::number(SendCnt));
}

void ser::serial_read_show()
{
    ReciCnt++;
    QString buf;
    buf = QString(serialport->readAll());
    ui->OutputEdit->appendPlainText(buf);

    ui->ReciveText->clear();
    ui->ReciveText->setText("Recieve:"+QString::number(ReciCnt));
}


void ser::on_ClearButton_clicked()
{
    ui->InputEdit->clear();
    ui->OutputEdit->clear();
    ui->SendText->clear();
    ui->ReciveText->clear();
    ui->SendText->setText("Send:0");
    ui->ReciveText->setText("Recieve:0");
    SendCnt = 0;
    ReciCnt = 0;
}

void ser::on_BackButton_clicked()
{
    this->close();
    menu*m = new menu;
    m->show();
}

