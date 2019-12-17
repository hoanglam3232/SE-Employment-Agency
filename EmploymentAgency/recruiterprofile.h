#ifndef RECRUITERPROFILE_H
#define RECRUITERPROFILE_H

#include <QDialog>
#include "vacancy.h"
// TODO add search

namespace Ui {
class recruiterProfile;
}

class recruiterProfile : public QDialog
{
    Q_OBJECT

public:
    explicit recruiterProfile(QWidget *parent = nullptr, int id = -1, int view = -1);
    ~recruiterProfile();
    void loadPro();
    void loadVac();
    void loadApp();
    void loadLocation();
    void setSession(int ID, int Type);

private slots:
    void on_button_reload_clicked();

    void on_button_search_clicked();

    void on_button_toggleEditMode_clicked();

    void on_button_logOut_clicked();

    void on_button_addVac_clicked();

    void on_button_delVac_clicked();

    void on_button_delApp_clicked();

    void on_tableView_vacancy_doubleClicked(const QModelIndex &index);

    void on_tableView_application_doubleClicked(const QModelIndex &index);

private:
    Ui::recruiterProfile *ui;
    QSqlQueryModel *vacancy_model;
    QSqlQueryModel *applicant_model;

    Vacancy *vacancy;
    // TODO add search

    int editMode; // 1 is read-only, 0 is read/write
    int view; // -1 is owner, 0 is standard_view, 1 is seeker_view

    int sessionID, sessionType;
    int id;
};

#endif // RECRUITERPROFILE_H
