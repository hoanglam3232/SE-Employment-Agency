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
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Nati-onBear/Desktop/employment(2).db");

    if (db.open()) {}
    else {
        QMessageBox::information(this, "Login call", "Database failed");
    }
}

void Login::getSeekerProfile(int db_id)
{
    seekerProfile *seekprof = new seekerProfile(this, db_id);
    seekprof->setSession(db_id, 1); // a seeker has session type 1
    seekprof->setModal(true);
    seekprof->exec();
}

void Login::getRecruiterProfile(int db_id)
{
    recruiterProfile *recruitprof = new recruiterProfile(this, db_id);
    recruitprof->setSession(db_id, 0); // a recruiter has session type 0
    recruitprof->setModal(true);
    recruitprof->exec();
}

void Login::getStaffProfile(int db_id)
{
    Staff *staffprof = new Staff(this, db_id);
    staffprof->setModal(true);
    staffprof->exec();
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
    // Retrieve textual data
    QString email = ui->edit_email->text();
    QString password = ui->edit_pass->text();

    // Query for entered user from the database
    QSqlQuery query;
    query.prepare("SELECT A.id, A.email, A.password, A.user_type FROM login_account A WHERE A.email = :email");
    query.bindValue(":email", email);

    if (query.exec()) {
        // There must be only ONE user of the same email
        if (query.next()) {
            int     db_id       = query.value(0).toInt();
            QString db_password = query.value(2).toString();
            QString db_user_type= query.value(3).toString();

            if (password == query.value(2).toString()) {
                // Log in successful, start checking user_type
                if (query.value(3).toString().compare("Seeker") == 0) {
                    hide();
                    getSeekerProfile(db_id);
                }
                else if (query.value(3).toString().compare("Recruiter") == 0) {
                    hide();
                    getRecruiterProfile(db_id);
                }
                else {
                    // admin
                    hide();
                    getStaffProfile(db_id);
                }

            } else {
                // Log in unsuccessful
                QMessageBox::information(this, "Login call", "Login unsuccessful");
            }
        }
        else {
            // Log in unsuccessful
            QMessageBox::information(this, "Login call", "Login unsuccessful");
        }
    }
}

void Login::on_signupButton_clicked()
{
    hide();

    signUp *signUp = new class signUp(this);
    signUp->setModal(true);
    signUp->exec();
}
