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

        // gender

        // dob

        // phone

        // signup date

        // seeker name

        // short desc

    }
    else {
        qDebug() << "seekerProf loadProf() query failed";
    }
}

void seekerProfile::loadEdu()
{
    // Query for info and display on screen via table
}

void seekerProfile::loadExp()
{
    // Query for info and display on screen via table
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

