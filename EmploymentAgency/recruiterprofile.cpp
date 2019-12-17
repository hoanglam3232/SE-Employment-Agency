#include "recruiterprofile.h"
#include "ui_recruiterprofile.h"

#include <QMessageBox>

recruiterProfile::recruiterProfile(QWidget *parent, int id, int view) :
    QDialog(parent),
    ui(new Ui::recruiterProfile)
{
    ui->setupUi(this);
    // set the id
    this->id = id;

    // models for table views
    vacancy_model = new QSqlQueryModel();
    ui->tableView_vacancy->setSelectionBehavior(QAbstractItemView::SelectRows); // select items as rows
    applicant_model = new QSqlQueryModel();
    ui->tableView_application->setSelectionBehavior(QAbstractItemView::SelectRows);

    // loading information
    loadPro();
    loadVac();
    loadApp();

    // only the owner of the profile can click these buttons
    this->view = view;
    if (view != -1) {
        // close all buttons
        ui->button_logOut->close();
        ui->button_search->close();
        ui->button_addVac->close();
        ui->button_delVac->close();
        ui->button_toggleEditMode->close();
    }

    // set to read-only
    editMode = 1;
}

recruiterProfile::~recruiterProfile()
{
    delete ui;
}

void recruiterProfile::loadPro()
{
    QSqlQuery qry;

    qry.prepare("SELECT L.email, L.gender, L.date_of_birth, L.phone_number, L.registration_date, R.name, R.job_title, R.from_company, R.company_description, R.company_url FROM login_account L, recruiter R WHERE L.id = R.recruiter_id AND L.id = :id");
    qry.bindValue(":id", this->id);

    // retrieving info
    if(qry.exec() && qry.first()){
        // email
        QString email = qry.value(0).toString();
        ui->edit_email->setText(email);

        // gender
        QString gender = qry.value(1).toString();
        ui->edit_gender->setText(gender);

        // dob
        QString dob = qry.value(2).toString();
        ui->edit_dob->setText(dob);

        // phone number
        QString phone = qry.value(3).toString();
        ui->edit_phone->setText(phone);

        // registration date
        QString regdate = qry.value(4).toString();
        ui->edit_regDate->setText(regdate);

        // recruiter name
        QString name = qry.value(5).toString();
        ui->edit_name->setText(name);

        // job title
        QString title = qry.value(6).toString();
        ui->edit_jobTitle->setText(title);

        // company
        QString company = qry.value(7).toString();
        ui->edit_company->setText(company);

        // short description
        QString description = qry.value(8).toString();
        ui->edit_company_desc->setPlainText(description);

        // company url
        QString url = qry.value(9).toString();
        ui->edit_url->setText(url);
    } else {
        qDebug() << "recruiterprofile.cpp query failed";
    }
}

void recruiterProfile::loadVac()
{
    QSqlQuery query;
    query.prepare("SELECT vacancy_id, position, published_date, closed_date FROM vacancy WHERE recruiter_id=:id");
    query.bindValue(":id", this->id);
    query.exec();

    // set query for the model
    vacancy_model->setQuery(query);

    // finally setting the model for tableView
    ui->tableView_vacancy->setModel(vacancy_model);
}

void recruiterProfile::loadApp()
{
    QSqlQuery query;
    query.prepare("SELECT L.email, V.position FROM job_application J, login_account L, vacancy V WHERE J.seeker_id = L.id AND J.vacancy_id = V.vacancy_id AND V.recruiter_id = :rec_id");
    query.bindValue(":rec_id", this->id);
    if (!query.exec()) {
        qDebug() << "Failed to load applications";
    }

    // set query for the model
    applicant_model->setQuery(query);

    // finally setting the model for tableView
    ui->tableView_application->setModel(applicant_model);
}

void recruiterProfile::loadLocation()
{
    QSqlQuery query;
    query.prepare("SELECT street_addr, ward, district, city FROM vacancy_location WHERE vacancy_id = :vac_id");
    query.bindValue(":vac_id", this->id);
    if (!query.exec()) {
        qDebug() << "Failed to load locations";
    }

    // Set query for the model
}

void recruiterProfile::setSession(int ID, int Type)
{
    this->sessionID = ID;
    this->sessionType = Type;
}

void recruiterProfile::on_button_reload_clicked()
{
    loadPro();
    loadVac();
    loadApp();
}

void recruiterProfile::on_button_search_clicked()
{

}

void recruiterProfile::on_button_toggleEditMode_clicked()
{
    editMode ^= 1;

    // set edit mode accordingly
    ui->edit_dob->setReadOnly(editMode);
    ui->edit_url->setReadOnly(editMode);
    ui->edit_name->setReadOnly(editMode);
    ui->edit_phone->setReadOnly(editMode);
    ui->edit_gender->setReadOnly(editMode);
    ui->edit_company->setReadOnly(editMode);
    ui->edit_company_desc->setReadOnly(editMode);
    if (editMode == 1) {
        QSqlQuery query;
        // query one
        query.prepare("UPDATE login_account SET gender = :gender, date_of_birth = :date_of_birth, phone_number = :phone_number WHERE id = :id");
        query.bindValue(":gender", ui->edit_gender->text());
        query.bindValue(":date_of_birth", ui->edit_dob->text());
        query.bindValue(":phone_number", ui->edit_phone->text());
        query.bindValue(":id", this->id);
        query.exec();
        if (!query.exec()) {
            qDebug() << "query 1 not executed";
        }

        // query two
        query.prepare("UPDATE recruiter SET name = :name, job_title = :job_title, from_company = :from_company, company_description = :company_description, company_url = :url WHERE recruiter_id = :id");
        query.bindValue(":name", ui->edit_name->text());
        query.bindValue(":job_title", ui->edit_jobTitle->text());
        query.bindValue(":from_company", ui->edit_company->text());
        query.bindValue(":company_description", ui->edit_company_desc->toPlainText());
        query.bindValue(":url", ui->edit_url->text());
        query.bindValue(":id", this->id);
        if (!query.exec()) {
            qDebug() << "query 2 not executed";
        }

        ui->button_toggleEditMode->setText("Read");
    } else {
        ui->button_toggleEditMode->setText("Write");
    }
}

void recruiterProfile::on_button_logOut_clicked()
{
    this->hide();
    parentWidget()->show();
    delete ui;
}

void recruiterProfile::on_button_addVac_clicked()
{
    hide();
    vacancy = new Vacancy(this);
    vacancy->setRecruiterID(id);
    vacancy->setSession(this->sessionID, this->sessionType);
    vacancy->show();
}

void recruiterProfile::on_button_delVac_clicked()
{
    if (ui->tableView_vacancy->selectionModel()->currentIndex().isValid()) {
        int rowidx = ui->tableView_vacancy->selectionModel()->currentIndex().row();
        QMessageBox::information(this, "Call", vacancy_model->index(rowidx, 0).data().toString());
        QSqlQuery qry;

        qry.prepare("DELETE FROM vacancy WHERE vacancy_id = :id");
        qry.bindValue(":id", vacancy_model->index(rowidx , 0).data().toString());

        if (qry.exec()) {
            loadVac();
        }
    }
    else {
        QMessageBox::warning(this, tr("Error"),
                                       tr("No vacancy selected"),
                                       QMessageBox::Ok,
                                       QMessageBox::Ok);
    }
}

void recruiterProfile::on_button_delApp_clicked()
{

}

void recruiterProfile::on_tableView_vacancy_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int rowidx = ui->tableView_vacancy->selectionModel()->currentIndex().row(); // get the selected row

        int id = vacancy_model->index(rowidx , 0).data().toInt();

        // get `id` from the selected row
        Vacancy *cur = new Vacancy(this);
        cur->setSession(this->sessionID, this->sessionType);

        cur->setID(id);

        if (this->sessionType == 0) { // a recruiter is viewing
            if (this->id != this->sessionID) // this is not the owner of the profile
                cur->closeLocationButtons();
        }

        cur->setModal(true);
        cur->exec();
    }
}

void recruiterProfile::on_tableView_application_doubleClicked(const QModelIndex &index)
{

}
