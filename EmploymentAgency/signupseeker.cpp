#include "signupseeker.h"
#include "ui_signupseeker.h"
#include "signup.h"

signUpSeeker::signUpSeeker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUpSeeker)
{
    ui->setupUi(this);
}

signUpSeeker::~signUpSeeker()
{
    delete ui;
}

void signUpSeeker::on_pushButton_finish_clicked()
{
    // getting the data
    QString name = ui->lineEdit_name->text();
    QString details = ui->textEdit_description->toPlainText();

    // setting up INSERT query
    QSqlQuery query;
    query.prepare(QString("INSERT INTO seeker(seeker_id, name, CV, other_details)")
                          + QString("VALUES(:seeker_id, :name, :CV, :other_details)"));

    query.bindValue(":seeker_id", ((signUp*) parentWidget())->getCount());
    query.bindValue(":name", name);
    query.bindValue(":CV", NULL);
    query.bindValue(":other_details", details);

    if (query.exec()) {
        // successfull query will insert the new entry

        hide();
        parentWidget()->parentWidget()->show();
    } else
        qDebug() << "signup_apply.cpp query unsuccessful";

}
