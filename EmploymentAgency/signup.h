#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

#include <signuprecruiter.h>
#include <signupseeker.h>

namespace Ui {
class signUp;
}

class signUp : public QDialog
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = nullptr);

    bool emailExisted(QString &email);

    // These functions return the number of insertion
    void counterInit();
    int getCount();

    ~signUp();

private slots:
    void on_backButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::signUp *ui;

    signUpSeeker *ui_app;
    signUpRecruiter *ui_rec;

    // Counts number of insertions
    int counter;
};

#endif // SIGNUP_H
