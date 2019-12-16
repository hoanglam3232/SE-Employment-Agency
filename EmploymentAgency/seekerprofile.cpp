#include "seekerprofile.h"
#include "ui_seekerprofile.h"

seekerProfile::seekerProfile(QWidget *parent, int accID, int view) :
    QDialog(parent),
    ui(new Ui::seekerProfile)
{
    ui->setupUi(this);
    
    // Init
    this->id = accID;
    
    // TODO add edu & exp view models
    
    // Loading Data
    loadProf();
    loadEdu();
    loadExp();
    
    // Visitor view (no button)
    if (view == 0) {
        // Close all buttons
    }
    
    // Edit mode starts at read only
    editMode = false;
}

seekerProfile::~seekerProfile()
{
    delete ui;
}

void seekerProfile::loadProf()
{
    // Query for info and display on screen
    QSqlQuery query;

    query.prepare("SELECT L.email, L.gender, L.date_of_birth, L.phone_number, L.registration_date, "
                            "S.name, S.other_details "
                  "FROM login_account L, seeker S "
                  "WHERE L.id = S.seeker_id AND L.id = :id");
    query.bindValue(":id", this->id);

    // Retrieving info
    if (query.exec() && query.first()) {
        // Display info
        // email
        QString email = query.value(0).toString();
        ui->edit_email->setText(email);

        // gender
        QString gender = query.value(1).toString();
        ui->edit_gender->setText(gender);

        // dob
        QString dob = query.value(2).toString();
        ui->edit_dob->setText(dob);

        // phone
        QString phone = query.value(3).toString();
        ui->edit_phone->setText(phone);

        // signup date
        QString signUpDate = query.value(4).toString();
        ui->edit_regDate->setText(signUpDate);

        // seeker name
        QString name = query.value(5).toString();
        ui->edit_name->setText(name);

        // short desc
        QString desc = query.value(6).toString();
        ui->edit_desc->setPlainText(desc);
    }
    else {
        qDebug() << "seekerProf loadProf() query failed";
    }
}

void seekerProfile::loadEdu()
{
    // Query for info and display on screen via table
    QSqlQuery query;
    query.prepare("SELECT school_name, major, degree_name FROM education_info WHERE seeker_id=:id");
    query.bindValue(":id", this->id);
    query.exec();

     // Set query for edu model

}

void seekerProfile::loadExp()
{
    // Query for info and display on screen via table
    QSqlQuery query;
    query.prepare("SELECT company_name, job_title, start_date, end_date FROM experience_info WHERE seeker_id=:id");
    query.bindValue(":id", this->id);
    query.exec();

    // Set query for exp model

}

int seekerProfile::getID()
{
    return this->id;
}

void seekerProfile::setSession(int ID, int Type)
{
    this->sessionID = ID;
    this->sessionType = Type;
}


void seekerProfile::on_button_reload_clicked()
{
    loadProf();
    loadEdu();
    loadExp();
}

void seekerProfile::on_button_search_clicked()
{
    // Show search menu
}

void seekerProfile::on_button_toggleEditMode_clicked()
{
    editMode ^= 0;
    
    // set edit mode accordingly
    ui->edit_dob->setReadOnly(editMode);
    ui->edit_name->setReadOnly(editMode);
    ui->edit_phone->setReadOnly(editMode);
    ui->edit_gender->setReadOnly(editMode);
    ui->edit_desc->setReadOnly(editMode);
    if (editMode == 1) {
        QSqlQuery query;
        // query one
        query.prepare("UPDATE login_account SET gender = :gender, date_of_birth = :date_of_birth, phone_number = :phone_number WHERE id = :id");
        query.bindValue(":gender", ui->edit_gender->text());
        query.bindValue(":date_of_birth", ui->edit_dob->text());
        query.bindValue(":phone_number", ui->edit_phone->text());
        query.bindValue(":id", this->id);
        query.exec();

        // query two
        query.prepare("UPDATE seeker SET name = :name, other_details = :description WHERE seeker_id = :id");
        query.bindValue(":name", ui->edit_name->text());
        query.bindValue(":description", ui->edit_desc->toPlainText());
        query.bindValue(":id", this->id);
        query.exec();

        ui->button_toggleEditMode->setText("Read");
    } else {
        ui->button_toggleEditMode->setText("Write");
    }
}

void seekerProfile::on_button_addExp_clicked()
{
    // Display modal for adding exp
}

void seekerProfile::on_button_delExp_clicked()
{
    // Delete the selected exp
}

void seekerProfile::on_button_addEdu_clicked()
{
    // Display modal for adding edu
}

void seekerProfile::on_button_delEdu_clicked()
{
    // Delete the selected edu
}
