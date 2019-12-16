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
    // Testing
    counter = 10;
}

int signUp::getCount()
{
    return counter;
}

bool signUp::emailExisted(QString &email)
{
    // Query for entered user's email from database

    // Use IF to ensure only one user of the same email

    // If taken email -> MessBox "Email Taken"

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

    // Query insert new account
    // Let user enter more specified info based on type of user
}
