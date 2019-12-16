#ifndef SEEKEREDUCATION_H
#define SEEKEREDUCATION_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class seekerEducation;
}

class seekerEducation : public QDialog
{
    Q_OBJECT

public:
    explicit seekerEducation(QWidget *parent = nullptr);
    ~seekerEducation();
    void setID(int);

private slots:
    void on_button_saveInfo_clicked();

private:
    Ui::seekerEducation *ui;
    int id;
};

#endif // SEEKEREDUCATION_H
