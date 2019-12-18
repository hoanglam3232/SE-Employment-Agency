#ifndef SEEKERPROFILE_H
#define SEEKERPROFILE_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>

#include "seekereducation.h"
#include "seekerexperience.h"
#include "search.h"

namespace Ui {
class seekerProfile;
}

class seekerProfile : public QDialog
{
    Q_OBJECT

public:
    // There should be 2 views, 
    // the account owner view (editable) 
    // and visitor view (non-editable).
    explicit seekerProfile(QWidget *parent = nullptr, int id = -1, int view = 0);
    ~seekerProfile();
    void loadProf();
    void loadEdu();
    void loadExp();
    int getID();
    void setSession(int ID, int Type);

private slots:
    void on_button_reload_clicked();

    void on_button_search_clicked();

    void on_button_toggleEditMode_clicked();

    void on_button_addExp_clicked();

    void on_button_delExp_clicked();

    void on_button_addEdu_clicked();

    void on_button_delEdu_clicked();

    void on_button_logOut_clicked();

private:
    Ui::seekerProfile *ui;
    
    QSqlQueryModel *edu_model;
    QSqlQueryModel *exp_model;

    Search *searcher;

    int sessionID, sessionType;
    bool editMode; // 0: read/write; 1: read only
    int id; // accID
};

#endif // SEEKERPROFILE_H
