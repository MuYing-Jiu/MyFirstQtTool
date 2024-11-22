#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "tt.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_clicked();

    void on_backButton_clicked();


private:

    Ui::Register *ui;
    QSqlDatabase db;
};

#endif // REGISTER_H
