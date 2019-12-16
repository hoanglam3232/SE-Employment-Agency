#ifndef SEEKEREXPERIENCE_H
#define SEEKEREXPERIENCE_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class seekerExperience;
}

class seekerExperience : public QDialog
{
    Q_OBJECT

public:
    explicit seekerExperience(QWidget *parent = nullptr);
    ~seekerExperience();
    void setID(int);

private slots:
    void on_button_saveInfo_clicked();

private:
    Ui::seekerExperience *ui;
    int id;
};

#endif // SEEKEREXPERIENCE_H
