#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    //QSqlDatabase db;
    Login(QWidget *parent = nullptr);
    ~Login();
    void setName(QString);
    QString getName();

private:
    Ui::Login *ui;

};
#endif // LOGIN_H
