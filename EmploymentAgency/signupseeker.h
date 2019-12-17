#ifndef SIGNUPSEEKER_H
#define SIGNUPSEEKER_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class signUpSeeker;
}

class signUpSeeker : public QDialog
{
    Q_OBJECT

public:
    explicit signUpSeeker(QWidget *parent = nullptr);
    ~signUpSeeker();

private slots:
    void on_pushButton_finish_clicked();

private:
    Ui::signUpSeeker *ui;
};

#endif // SIGNUPSEEKER_H
