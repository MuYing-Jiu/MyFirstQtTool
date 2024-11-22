#ifndef SER_H
#define SER_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class ser;
}

class ser : public QWidget
{
    Q_OBJECT

public:
    explicit ser(QWidget *parent = nullptr);
    ~ser();
    QSerialPort *serialport;

private slots:

    void on_OpenButton_clicked();

    void serial_read_show();

    void on_CloseButton_clicked();

    void on_SendButton_clicked();

    void on_ClearButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::ser *ui;
};

#endif // SER_H
