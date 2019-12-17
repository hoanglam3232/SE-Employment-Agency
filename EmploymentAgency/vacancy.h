#ifndef VACANCY_H
#define VACANCY_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class Vacancy;
}

class Vacancy : public QDialog
{
    Q_OBJECT

public:
    explicit Vacancy(QWidget *parent = nullptr);
    ~Vacancy();
    void setRecruiterID(int);
    void setID(int);
    void setReadOnly();
    void setSession(int ID, int Type);
    void loadLocation();
    void closeLocationButtons();

private slots:
    void on_button_reload_clicked();

    void on_button_apply_clicked();

    void on_button_back_clicked();

    void on_button_addVacancy_clicked();

    void on_button_addLocation_clicked();

    void on_button_delLocation_clicked();

private:
    Ui::Vacancy *ui;

    // TODO include location model

    // Get Vacancy ID
    void CounterInit();

    // counter for vacancy
    int counter;

    // this applies if the vacancy exists
    int id;              // id of the vacancy

    // this applies if the vacancy is in adding mode
    int idRecruiter;

    // the session info
    int sessionID, sessionType;
};

#endif // VACANCY_H
