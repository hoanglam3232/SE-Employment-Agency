#include "seekerexperience.h"
#include "ui_seekerexperience.h"
#include "seekerprofile.h"

seekerExperience::seekerExperience(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seekerExperience)
{
    ui->setupUi(this);
}

seekerExperience::~seekerExperience()
{
    delete ui;
}

void seekerExperience::on_button_saveInfo_clicked()
{
    // Gather data
    QString company = ui->edit_company->text();
    QString job = ui->edit_pos->text();
    QString addr = ui->edit_addr->text();
    QDate start = ui->dateEdit_start->date();
    QDate end = ui->dateEdit_end->date();
    QString details = ui->textEdit_details->toPlainText();

    //setting up INSERT query
    QSqlQuery query;
    query.prepare(QString("INSERT INTO experience_info(seeker_id, company_name, job_title, work_address, start_date, end_date, other_details)")
                          + QString("VALUES(:seeker_id, :company_name, :job_title, :work_address, :start_date, :end_date, :other_details)"));
    query.bindValue(":seeker_id", id);
    query.bindValue(":company_name", company);
    query.bindValue(":job_title", job);
    query.bindValue(":work_address", addr);
    query.bindValue(":start_date", start);
    query.bindValue(":end_date", end);
    query.bindValue(":other_details", details);

    if (query.exec()) {
        // successfull query will insert the new entry
        hide();
        ((seekerProfile*) parentWidget())->loadExp();
        parentWidget()->show();

        delete ui;
    } else
        qDebug() << "seekerExp.cpp query unsuccessful";
}

void seekerExperience::setID(int id)
{
    this->id = id;
}
