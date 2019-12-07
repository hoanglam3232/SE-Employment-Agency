#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>


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

private:
    Ui::signUp *ui;

    // Counts number of insertions
    int counter;
};

#endif // SIGNUP_H
