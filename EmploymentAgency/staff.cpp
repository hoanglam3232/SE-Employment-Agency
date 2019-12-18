#include "staff.h"
#include "ui_staff.h"

#include <QMessageBox>

Staff::Staff(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);

    // set the staff `id`
    this->id = id;

    // the query table
    query_model = new QSqlQueryModel();
    ui->tableView_query->setSelectionBehavior(QAbstractItemView::SelectRows);

    // The queued vacancies table
    vacancies_model = new QSqlQueryModel();
    ui->tableView_vacancies->setSelectionBehavior(QAbstractItemView::SelectRows);

    loadQueuedVacancies();
}

Staff::~Staff()
{
    delete ui;
}

void Staff::loadQueuedVacancies()
{
    QSqlQuery query;
    query.prepare("SELECT recruiter_id, vacancy_id, position FROM vacancy WHERE agency_approval = 0 AND seen_by_agency = 0");
    query.exec();

    // set query for the model
    vacancies_model->setQuery(query);

    // finally setting the model for tableView
    ui->tableView_vacancies->setModel(vacancies_model);
}

void Staff::updateApproval(int vacancyID)
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO vacancy_approval(staff_id, vacancy_id, approval_date, staff_decision, details)")
                  + QString("VALUES(:staff_id, :vacancy_id, :approval_date, :staff_decision, :details)"));
    query.bindValue(":staff_id", this->id);
    query.bindValue(":vacancy_id", vacancyID);
    query.bindValue(":approval_date", this->id);
    query.bindValue(":staff_decision", 1);
    query.bindValue(":details", "");
}

void Staff::on_pushButton_run_clicked()
{
    QString command = ui->command->toPlainText();
    QSqlQuery query;
    query.prepare(command);
    if (query.exec()) {
        ui->output_note->setPlainText("Query successful!");
        query_model->setQuery(query);

        // finally set the model for tableView
        ui->tableView_query->setModel(query_model);
    } else {
        ui->output_note->setPlainText("Query failed.");
    }

}

void Staff::on_pushButton_logout_clicked()
{
    hide();
    parentWidget()->show();
    delete ui;
}

void Staff::on_tableView_vacancies_doubleClicked(const QModelIndex &index)
{

}

void Staff::on_pushButton_accept_clicked()
{
    if (ui->tableView_vacancies->selectionModel()->currentIndex().isValid()) {
        int rowIndex = ui->tableView_vacancies->selectionModel()->currentIndex().row();
        int selectedVacancyID = vacancies_model->index(rowIndex, 1).data().toInt();
        QMessageBox::information(this, "Call", vacancies_model->index(rowIndex, 1).data().toString());
        QSqlQuery query;

        query.prepare("UPDATE vacancy SET agency_approval = 1 AND seen_by_agency = 1 WHERE vacancy_id = :id");
        //query.bindValue(":id", vacancies_model->index(rowIndex , 1).data().toString());
        query.bindValue(":id", selectedVacancyID);

        if (query.exec()) {
            loadQueuedVacancies();
            updateApproval(selectedVacancyID);
        }
    }
    else {
        QMessageBox::warning(this, tr("Error"),
                                       tr("No vacancy selected"),
                                       QMessageBox::Ok,
                                       QMessageBox::Ok);
    }
}

void Staff::on_pushButton_decline_clicked()
{

}
