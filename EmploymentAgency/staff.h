#ifndef STAFF_H
#define STAFF_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class Staff;
}

class Staff : public QDialog
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = nullptr, int id = -1);
    ~Staff();
    void loadQueuedVacancies();
    void updateApproval(int vacancyID);

private slots:
    void on_pushButton_run_clicked();

    void on_pushButton_logout_clicked();

    void on_tableView_vacancies_doubleClicked(const QModelIndex &index);

    void on_pushButton_accept_clicked();

    void on_pushButton_decline_clicked();

private:
    Ui::Staff *ui;
    QSqlQueryModel *query_model;
    QSqlQueryModel *vacancies_model;

    int id;
};

#endif // STAFF_H
