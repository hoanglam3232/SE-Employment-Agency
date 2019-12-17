#ifndef SIGNUPRECRUITER_H
#define SIGNUPRECRUITER_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class signUpRecruiter;
}

class signUpRecruiter : public QDialog
{
    Q_OBJECT

public:
    explicit signUpRecruiter(QWidget *parent = nullptr);
    ~signUpRecruiter();

private slots:
    void on_pushButton_finish_clicked();

private:
    Ui::signUpRecruiter *ui;
};

#endif // SIGNUPRECRUITER_H
