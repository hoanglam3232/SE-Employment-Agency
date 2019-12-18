#include "signup.h"
#include "ui_signup.h"

signUp::signUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUp)
{
    ui->setupUi(this);

    // Init a counter for IDs
    counterInit();
}

signUp::~signUp()
{
    delete ui;
}

void signUp::counterInit()
{
    // Query select max id
    QSqlQuery query;
    query.prepare("SELECT MAX(A.id) FROM login_account A");

    if (query.exec()) {
        if (query.next())
            counter = query.value(0).toInt();
        else
            counter = 0;
    } else {
        qDebug() << "Counter init failed";
    }
}

int signUp::getCount()
{
    return counter;
}

bool signUp::emailExisted(QString &email)
{
    // Query for entered user's email from database
    QSqlQuery query;
    query.prepare("SELECT A.email FROM login_account A WHERE A.email = :email");
    query.bindValue(":email", email);

    // Use IF to ensure only one user of the same email
    // If taken email -> MessBox "Email Taken"
    if (query.exec()) {
        // There must be only ONE user of the same email
        if (query.next()) {
            QMessageBox::information(this, "Signup", "Email already taken.");
            return true;
        }
        else {
            return false;
        }
    } else {
        qDebug() << "Signup check failed";
    }
    return false;
}

void signUp::on_backButton_clicked()
{
    this->hide();

    // Show the Login Screen
    QWidget *parent = this->parentWidget();
    parent->show();
}

void signUp::on_signupButton_clicked()
{
    // Check info must be in correct format, if not then return
    // retrieving data
    QString email = ui->edit_email->text();

    if (emailExisted(email))
        return;

    QString password = ui->edit_pass->text();
    QString gender = ui->comboBox_gender->currentText();
    QDate dob = ui->dateEdit_DoB->date();
    QString phone_num = ui->edit_contact->text();
    QString user_type = ui->comboBox_type->currentText();

    // Query insert new account
    // setting up INSERT query
    QSqlQuery query;
    query.prepare(QString("INSERT INTO login_account(id, email, password, user_type, gender, date_of_birth, phone_number, account_image, registration_date) ")
                   + QString("VALUES(:id, :email, :password, :user_type, :gender, :date_of_birth, :phone_number, :account_image, :registration_date)"));

    // binding tag-along column data
    query.bindValue(":id", ++this->counter);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":user_type", user_type);

    query.bindValue(":gender", gender);
    query.bindValue(":date_of_birth", dob);

    query.bindValue(":phone_number", phone_num);
    query.bindValue(":account_image", NULL);

    query.bindValue(":registration_date", QDate::currentDate());

    // Let user enter more specified info based on type of user
    if (query.exec()) {
        hide();
        if (user_type == "Seeker") {
            ui_app = new signUpSeeker(this);
            ui_app->show();
        } else if (user_type == "Recruiter") {
            ui_rec = new signUpRecruiter(this);
            ui_rec->show();
        }
    }
    else
        qDebug() << "signup.cpp query failed";
}
