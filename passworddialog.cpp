#include "passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *pwrt) : QDialog (pwrt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    password = new QLineEdit;
    repeat_password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    repeat_password->setEchoMode(QLineEdit::Password);
    QLabel *lbl_pas = new QLabel("&Пароль:");
    QLabel *lbl_rep_pas = new QLabel("&Повторите пароль:");
    lbl_pas->setBuddy(password);
    lbl_rep_pas->setBuddy(repeat_password);
    QPushButton *btn_ok = new QPushButton("&OK");
    QPushButton *btn_cancel = new QPushButton("&Cancel");
    connect(btn_ok, SIGNAL(clicked()), SLOT(accept()));
    connect(btn_cancel, SIGNAL(clicked()), SLOT(accept()));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lbl_pas, 0, 0);
    layout->addWidget(password, 0, 1);
    layout->addWidget(lbl_rep_pas, 1, 0);
    layout->addWidget(repeat_password, 1, 1);
    layout->addWidget(btn_ok, 2, 0);
    layout->addWidget(btn_cancel, 2, 1);
    setLayout(layout);
}

std::optional<QString> PasswordDialog::getPassword() const
{
    return password->text() == repeat_password->text() ?
                std::optional<QString>{password->text()} : std::nullopt;
}
