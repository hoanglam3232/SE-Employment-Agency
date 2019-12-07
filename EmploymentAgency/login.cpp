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
    // Show forget password screen
}

void Login::on_helpButton_clicked()
{
    // Show help screen
}

void Login::on_loginButton_clicked()
{
    // Check login info

    // If correct, show the user's profile
    // Else, MessBox -> "Unsuccessful login"
}

void Login::on_signupButton_clicked()
{
    hide();

    signUp *signUp = new class signUp(this);
    signUp->setModal(true);
    signUp->exec();
}
