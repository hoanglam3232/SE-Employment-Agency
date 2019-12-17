#ifndef LOCATION_H
#define LOCATION_H

#include <QDialog>

namespace Ui {
class Location;
}

class Location : public QDialog
{
    Q_OBJECT

public:
    explicit Location(QWidget *parent = nullptr, int owner_id = -1, bool isVacancy = false);
    ~Location();

private slots:
    void on_button_save_clicked();

private:
    Ui::Location *ui;
    int oid;
    bool isVacancy;
};

#endif // LOCATION_H
