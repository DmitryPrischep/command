#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <optional>
#include <QPushButton>
#include <QGridLayout>

class PasswordDialog : public QDialog
{
    Q_OBJECT

    QLineEdit *password;
    QLineEdit *repeat_password;
public:
    explicit PasswordDialog(QWidget *pwrt = nullptr);
    std::optional<QString> getPassword() const;
};

#endif // PASSWORDDIALOG_H
