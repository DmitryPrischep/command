#include "passwordform.h"
#include "ui_passwordform.h"

PasswordForm::PasswordForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordForm)
{
    ui->setupUi(this);
}

PasswordForm::~PasswordForm()
{
    delete ui;
}
