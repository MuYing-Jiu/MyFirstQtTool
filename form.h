#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void setStaffInfo(int id, QString name, QString key, bool isvip, bool isadmin);

private:
    Ui::Form *ui;
};

#endif // FORM_H
