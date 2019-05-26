#include "passwordform.h"
#include "ui_passwordform.h"

PasswordForm::PasswordForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordForm)
{
    ui->setupUi(this);
    connect(ui->cancel_button, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->ok_button, SIGNAL(clicked()), SLOT(accept()));
}

PasswordForm::~PasswordForm()
{
    delete ui;
}

QString PasswordForm::getPassword() const
{
    return ui->password->text();
}
