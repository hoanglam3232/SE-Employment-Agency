#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <signup.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    Login(QWidget *parent = nullptr);
    ~Login();
    void setName(QString);
    QString getName();

private slots:
    void on_forgetPassButton_clicked();

    void on_helpButton_clicked();

    void on_loginButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::Login *ui;

    void connectDatabase();

};
#endif // LOGIN_H
