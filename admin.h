#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_quit_clicked();

    void on_Net_clicked();

    void on_TryTimes_valueChanged(int arg1);

    void on_InsertButton_clicked();

    void on_DeleteButton_clicked();

    void on_UpdataButton_clicked();

    void on_SerchButton_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
