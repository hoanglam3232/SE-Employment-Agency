#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr, int view = 0);
    ~Search();
    QString prepareCommand();
    void setSession(int ID, int Type);

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_load_clicked();

    void on_pushButton_current_clicked();

    void on_pushButton_profile_clicked();

private:
    Ui::Search *ui;
    QSqlQueryModel *model;

    int sessionID, sessionType;

    int state; // 0 is `Profiles`,
               // 1 is `Vacancies`

    int view; // 0 is standard
                     // 1 is seeker view

};

#endif // SEARCH_H
