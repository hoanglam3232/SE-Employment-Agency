#include "location.h"
#include "ui_location.h"
#include "vacancy.h"
#include "recruiterprofile.h"

Location::Location(QWidget *parent, int owner_id, bool isVacancy) :
    QDialog(parent),
    ui(new Ui::Location)
{
    ui->setupUi(this);

    oid = owner_id;
    this->isVacancy = isVacancy;
}

Location::~Location()
{
    delete ui;
}

void Location::on_button_save_clicked()
{
    QString addr = ui->edit_addr->text();
    QString ward = ui->edit_ward->text();
    QString district = ui->edit_district->text();
    QString city = ui->edit_city->text();
    if (addr.size() > 0 && district.size() > 0 && city.size() > 0) {
        QSqlQuery query;
        query.prepare("INSERT INTO location(street_addr, ward, district, city, other_details) VALUES (:addr, :ward, :district, :city, NULL)");
        query.bindValue(":addr", addr);
        query.bindValue(":ward", ward);
        query.bindValue(":district", district);
        query.bindValue(":city", city);

        if (isVacancy) {
            // Insert into vacancy location_id
        }

        if (query.exec()) {
            hide();
            if (isVacancy) {
                ((Vacancy*) parentWidget())->loadLocation();
            }
            else {
                ((recruiterProfile*) parentWidget())->loadLocation();
            }
            parentWidget()->show();
            delete ui;
        }
    }
}
