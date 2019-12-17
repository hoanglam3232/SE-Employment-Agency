#include "search.h"
#include "ui_search.h"
#include "seekerprofile.h"
#include "recruiterprofile.h"
#include <QMessageBox>

Search::Search(QWidget *parent, int view) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);

    // model for table view
    model = new QSqlQueryModel();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // set state to 0
    // | 0 is `Profiles`,
    // | 1 is `Vacancies`
    state = 0;

    // set perspective
    // | 0 is standard
    // | 1 is seeker view
    this->view = view;

}

Search::~Search()
{
    delete ui;
}

void Search::setSession(int ID, int Type) {
    this->sessionID = ID;
    this->sessionType = Type;
}


QString Search::prepareCommand() {
    if (state == 0) // `Profiles` mode
    {
        // getting the necessary data
        QString email = ui->lineEdit_primary->text();
        QString name  = ui->lineEdit_secondary->text();
        QString user_type = ui->comboBox_usertype->currentText();
        int ut_flag = (user_type == "Recruiters"? 1 : 0); // setting flag,
                                                          // 1 is recruiter, 0 otherwise

        // create the basic query
        QString basic_cmd = "SELECT L.id, L.email AS Email FROM login_account L, " + QString(ut_flag == 1? "recruiter H " : "seeker H ");

        // add where clauses
        QString extension = "WHERE L.id = " + QString(ut_flag == 1? "H.recruiter_id " : "H.seeker_id ");

        if (email != "")
            extension += "AND L.email = '" + email + "' ";
        if (name != "") {
            if (ut_flag == 1)
                extension += "AND H.from_company = '" + name + "' ";
            else
                extension += "AND H.name = '" + name + "' ";
        }
        return basic_cmd + extension;
    }
    else // `Vacancies` mode
    {
        QString position = ui->lineEdit_primary->text();
        QString company_name  = ui->lineEdit_secondary->text();

        // create the basic query
        QString basic_cmd = "SELECT V.vacancy_id, V.position AS Position, R.from_company AS Company FROM vacancy V, recruiter R ";

        // add where clauses
        QString extension = "WHERE R.recruiter_id = V.recruiter_id ";

        if (position != "")
            extension += "AND V.position = '" + position + "' ";
        if (company_name != "")
            extension += "AND R.from_company = '" + company_name + "' ";

        return basic_cmd + extension;
    }
}


void Search::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int rowidx = ui->tableView->selectionModel()->currentIndex().row(); // get the selected row

        int id = model->index(rowidx , 0).data().toInt();                   // get `id` from the selected row
        if (state == 0) {
            if (ui->comboBox_usertype->currentText() == "Seekers") {
                // if the clicked row belongs to a seeker
                seekerProfile *searched = new seekerProfile(this, id, 1);
                searched->setSession(this->sessionID, this->sessionType);
                searched->setModal(true);
                searched->exec();
            } else {
                // if the clicked row belongs to a recruiter
                recruiterProfile *searched = new recruiterProfile(this, id, 1);
                searched->setSession(this->sessionID, this->sessionType);
                searched->setModal(true);
                searched->exec();
            }
        } else {
            // if the clicked row belongs to a vacancy
            Vacancy *cur = new Vacancy(this);
            cur->setSession(this->sessionID, this->sessionType);
            cur->setID(id);
            cur->closeLocationButtons(); // no need for these buttons now

            cur->setModal(true);
            cur->exec();
        }
    }
}

void Search::on_pushButton_load_clicked()
{
    QSqlQuery query;
    query.prepare(prepareCommand());
    query.exec();

    // set query for the model
    model->setQuery(query);

    // finally setting the model for tableView
    ui->tableView->setModel(model);
}

void Search::on_pushButton_current_clicked()
{
    if (state == 0) {
        ui->label_title->setText("VACANCIES");
        ui->label_primary->setText("Position");
        ui->label_secondary->setText("Company");
        ui->comboBox_usertype->hide();
    }
    else {
       ui->label_title->setText("PROFILES");
       ui->label_primary->setText("Email");
       ui->label_secondary->setText("Name");
       ui->comboBox_usertype->show();
    }

    // reset the table view with an empty query
    QSqlQuery query;
    query.prepare("");
    query.exec();
    model->setQuery(query);

    // switching states
    state ^= 1;
}

void Search::on_pushButton_profile_clicked()
{
    this->hide();
    parentWidget()->show();

    delete ui;
}
