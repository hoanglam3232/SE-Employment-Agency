#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    connectDatabase();
}

Login::~Login()
{
    delete ui;
}

void Login::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("Employment_Agency");

    if (db.open()) {}
    else {
        QMessageBox::information(this, "Login call", "Database failed");
    }
}

void Login::on_forgetPassButton_clicked()
{

}

void Login::on_helpButton_clicked()
{

}

void Login::on_loginButton_clicked()
{

}

void Login::on_signupButton_clicked()
{

}
