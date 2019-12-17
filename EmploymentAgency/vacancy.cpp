#include "vacancy.h"
#include "ui_vacancy.h"
#include "recruiterprofile.h"
// TODO add location

Vacancy::Vacancy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vacancy)
{
    ui->setupUi(this);

    // TODO add location view model
}

Vacancy::~Vacancy()
{
    delete ui;
}

void Vacancy::setRecruiterID(int ID)
{
    this->idRecruiter = ID;
    closeLocationButtons();
}

void Vacancy::setID(int ID)
{
    ui->button_addVacancy->close();

    this->id = ID;

    // get the data from database
    QSqlQuery query;
    query.prepare("SELECT position, salary, benefits, job_description, requirements, other_details, published_date, closed_date, negotiable FROM vacancy WHERE vacancy_id = :id");
    query.bindValue(":id", ID);
    if (query.exec() && query.first()) {
        // set them up
        ui->edit_pos->setText(query.value(0).toString());
        ui->edit_salary->setText(query.value(1).toString());
        ui->textEdit_bene->setText(query.value(2).toString());
        ui->textEdit_desc->setText(query.value(3).toString());
        ui->textEdit_req->setText(query.value(4).toString());
        ui->textEdit_detail->setText(query.value(5).toString());
        ui->dateEdit_published->setDate(query.value(6).toDate());
        ui->dateEdit_closed->setDate(query.value(7).toDate());
        ui->checkBox_nego->setChecked(query.value(8).toBool());
    } else {
        qDebug() << "vacancy.cpp setID() query failed";
    }

    setReadOnly();
    loadLocation();
}

void Vacancy::setReadOnly()
{
    // Read-only mode
    ui->edit_pos->setReadOnly(true);
    ui->edit_salary->setReadOnly(true);
    ui->textEdit_bene->setReadOnly(true);
    ui->textEdit_desc->setReadOnly(true);
    ui->textEdit_req->setReadOnly(true);
    ui->textEdit_detail->setReadOnly(true);
    ui->dateEdit_published->setReadOnly(true);
    ui->dateEdit_closed->setReadOnly(true);

    // check box
    ui->checkBox_nego->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox_nego->setFocusPolicy(Qt::NoFocus);
}

void Vacancy::setSession(int ID, int Type)
{
    this->sessionID = ID;
    this->sessionType = Type;

    if (this->sessionType == 1) // the session belongs to a seeker
    {
        closeLocationButtons();
        ui->button_addVacancy->close();
    } else {
        ui->button_apply->close();
    }
}

void Vacancy::loadLocation()
{
    QSqlQuery query;
    query.prepare("SELECT street_addr, ward, district, city FROM vacancy_location WHERE vacancy_id = :vac_id");
    query.bindValue(":vac_id", this->id);
    if (!query.exec()) {
        qDebug() << "Failed to load locations";
    }

    // Set query for the model
}

void Vacancy::closeLocationButtons()
{
    ui->button_addLocation->close();
    ui->button_delLocation->close();
}

void Vacancy::on_button_reload_clicked()
{
    loadLocation();
}

void Vacancy::on_button_apply_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO job_application(seeker_id, vacancy_id) VALUES(:seeker_id, :vacancy_id)");
    query.bindValue(":seeker_id", this->sessionID);
    query.bindValue(":vacancy_id", this->id);
    if (!query.exec())
        qDebug() << "Job application failed.";
}

void Vacancy::on_button_back_clicked()
{
    hide();
    parentWidget()->show();

    delete ui;
}

void Vacancy::on_button_addVacancy_clicked()
{
    //getting the data
    QDate published = ui->dateEdit_published->date();
    QDate closed = ui->dateEdit_closed->date();
    QString position = ui->edit_pos->text();
    QString desc = ui->textEdit_desc->toPlainText();
    QString salary = ui->edit_salary->text();
    bool    nego = ui->checkBox_nego->isChecked();
    QString require = ui->textEdit_req->toPlainText();
    QString benefit = ui->textEdit_bene->toPlainText();
    QString other = ui->textEdit_detail->toPlainText();

    //setting up INSERT query
    QSqlQuery query;
    query.prepare(QString("INSERT INTO vacancy(vacancy_id, recruiter_id, published_date, closed_date, position, job_description, salary, negotiable, requirements, benefits, other_details)")
                          + QString("VALUES(:vacancy_id, :recruiter_id, :published_date, :closed_date, :position, :job_description, :salary, :negotiable, :requirements, :benefits, :other_details)"));

    query.bindValue(":recruiter_id", idRecruiter);
    query.bindValue(":published_date", published);
    query.bindValue(":closed_date", closed);
    query.bindValue(":position", position);
    query.bindValue(":job_description", desc);
    query.bindValue(":salary", salary);
    query.bindValue(":negotiable", nego);
    query.bindValue(":requirements", require);
    query.bindValue(":benefits", benefit);
    query.bindValue(":other_details", other);

    if (query.exec()) {
        // successfull query will insert the new entry
        hide();
        ((recruiterProfile*) parentWidget())->loadVac();
        parentWidget()->show();

        delete ui;
    } else
        qDebug() << "add vacancy query unsuccessful";
}

void Vacancy::on_button_addLocation_clicked()
{

}

void Vacancy::on_button_delLocation_clicked()
{

}

void Vacancy::CounterInit()
{
    QSqlQuery query;
    query.prepare("SELECT MAX(A.vacancy_id) FROM vacancy A");

    if (query.exec()) {
        if (query.next()) {
            counter = query.value(0).toInt() + 1;
            qDebug() << counter;
        }
        else {
            counter = 0;
            qDebug() << "This is %d" << counter;
        }
    } else {
        qDebug() << "Counter init failed";
    }
}
