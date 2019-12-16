#include "seekerprofile.h"
#include "ui_seekerprofile.h"

seekerProfile::seekerProfile(QWidget *parent, int accID, int view) :
    QDialog(parent),
    ui(new Ui::seekerProfile)
{
    ui->setupUi(this);
    
    // Init
    this->id = accID;

    // Init edu and exp
    edu_model = new QSqlQueryModel();
    ui->tableView_edu->setSelectionBehavior(QAbstractItemView::SelectRows);

    exp_model = new QSqlQueryModel();
    ui->tableView_exp->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Loading Data
    loadProf();
    loadEdu();
    loadExp();
    
    // Visitor view (no button)
    if (view == 0) {
        // Close all buttons
        ui->button_addEdu->close();
        ui->button_addExp->close();
        ui->button_delEdu->close();
        ui->button_delExp->close();
        ui->button_logOut->close();
        ui->button_reload->close();
        ui->button_search->close();
        ui->button_toggleEditMode->close();
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
    edu_model->setQuery(query);

    // Set model
    ui->tableView_edu->setModel(edu_model);
}

void seekerProfile::loadExp()
{
    // Query for info and display on screen via table
    QSqlQuery query;
    query.prepare("SELECT company_name, job_title, start_date, end_date FROM experience_info WHERE seeker_id=:id");
    query.bindValue(":id", this->id);
    query.exec();

    // Set query for exp model
    exp_model->setQuery(query);

    // Set model
    ui->tableView_exp->setModel(exp_model);
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
    seekerExperience *exp = new seekerExperience(this);
    exp->setID(id);
    exp->setModal(true);
    exp->exec();
}

void seekerProfile::on_button_delExp_clicked()
{
    // Delete the selected exp
    if (ui->tableView_exp->selectionModel()->currentIndex().isValid()) {
        int rowIndex = ui->tableView_exp->selectionModel()->currentIndex().row();

        QSqlQuery query;

        query.prepare("DELETE FROM experience_info WHERE seeker_id = :id AND company_name = :cname AND job_title = :title");
        query.bindValue(":id", this->id);
        query.bindValue(":cname", exp_model->index(rowIndex , 0).data().toString());
        query.bindValue(":title", exp_model->index(rowIndex , 1).data().toString());

        if (query.exec())
            loadExp();
    }
}

void seekerProfile::on_button_addEdu_clicked()
{
    // Display modal for adding edu
    seekerEducation *edu = new seekerEducation(this);
    edu->setID(id);
    edu->setModal(true);
    edu->exec();
}

void seekerProfile::on_button_delEdu_clicked()
{
    // Delete the selected edu
    if (ui->tableView_edu->selectionModel()->currentIndex().isValid()) {
        int rowIndex = ui->tableView_edu->selectionModel()->currentIndex().row();

        QSqlQuery query;

        query.prepare("DELETE FROM education_info WHERE seeker_id = :id AND school_name = :sname AND major = :major AND degree_name = :dname");
        query.bindValue(":id", this->id);
        query.bindValue(":sname", edu_model->index(rowIndex , 0).data().toString());
        query.bindValue(":major", edu_model->index(rowIndex , 1).data().toString());
        query.bindValue(":dname", edu_model->index(rowIndex , 2).data().toString());

        if (query.exec())
            loadEdu();
    }
}
