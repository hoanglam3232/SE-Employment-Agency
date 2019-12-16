#include "seekereducation.h"
#include "ui_seekereducation.h"
#include "seekerprofile.h"

seekerEducation::seekerEducation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seekerEducation)
{
    ui->setupUi(this);
}

seekerEducation::~seekerEducation()
{
    delete ui;
}

void seekerEducation::on_button_saveInfo_clicked()
{
    // Gather data
    QString degree = ui->edit_degree->text();
    QString major = ui->edit_major->text();
    QString school = ui->edit_school->text();
    QString gpa = ui->edit_gpa->text();
    QString details = ui->edit_details->toPlainText();

    //setting up INSERT query
    QSqlQuery query;
    query.prepare(QString("INSERT INTO education_info(seeker_id, degree_name, major, school_name, gpa, other_details)")
                          + QString("VALUES(:seeker_id, :degree_name, :major, :school_name, :gpa, :other_details)"));
    query.bindValue(":seeker_id", id);
    query.bindValue(":degree_name", degree);
    query.bindValue(":major", major);
    query.bindValue(":school_name", school);
    if (gpa != "")
        query.bindValue(":gpa", gpa.toFloat());
    else
        query.bindValue(":gpa", 0.0);
    query.bindValue(":other_details", details);

    if (query.exec()) {
        // successfull query will insert the new entry
        hide();
        ((seekerProfile*) parentWidget())->loadEdu();
        parentWidget()->show();
        delete ui;
    } else
        qDebug() << "signup_apply.cpp query unsuccessful";
}

void seekerEducation::setID(int id)
{
    this->id = id;
}
