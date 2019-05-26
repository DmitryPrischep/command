#ifndef PASSWORDFORM_H
#define PASSWORDFORM_H

#include <QDialog>
#include <QPushButton>
#include <QString>

namespace Ui {
class PasswordForm;
}

class PasswordForm : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordForm(QWidget *parent = nullptr);
    ~PasswordForm();
    QString getPassword() const;

private:
    Ui::PasswordForm *ui;
};

#endif // PASSWORDFORM_H
