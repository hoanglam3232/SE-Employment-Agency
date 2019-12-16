#ifndef SEEKERPROFILE_H
#define SEEKERPROFILE_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>

// TODO include edu and exp

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
    explicit seekerProfile(QWidget *parent = nullptr, int id = -1, int view = 1);
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

private:
    Ui::seekerProfile *ui;
    
    // TODO add edu & exp model
    
    int sessionID, sessionType;
    bool editMode; // 1: read/write; 0: read only
    int id; // accID
};

#endif // SEEKERPROFILE_H
