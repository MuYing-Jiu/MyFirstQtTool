#ifndef TT_H
#define TT_H

#include <QSqlDatabase>
#include <QSqlQuery> //可以用来真正访问操作数据库
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //oop*o;
    int *TryTimes;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
private slots:
    void on_openBt_clicked();
    void on_sendBt_clicked();

    void newConnection_Slot();
    void connected_Slot();
    void readyRead_Slot();
    void disconnected_Slot();


    void on_clearBt_clicked();

    void on_sendBt_pressed();

    void on_sendBt_released();

    void on_clearBt_pressed();

    void on_clearBt_released();

    void on_clearS_pressed();

    void on_clearS_released();

    void on_ms_clicked();



    void on_Send1Button_clicked();

    void on_back_clicked();

private:
    Ui::Widget *ui;



};

#endif // TT_H
