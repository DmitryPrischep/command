#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QMainWindow>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
#include <QModelIndexList>
#include <QModelIndex>
#include "dir_controller.h"
#include <QMenu>
#include <QToolBar>
#include <QIcon>
#include <assert.h>

namespace Ui {
class Main_Form;
}

class Main_Form : public QMainWindow
{
    Q_OBJECT

Dir_Controller dir_controller;
QFileSystemModel *model;
public:
    explicit Main_Form(QWidget *parent = nullptr);
    ~Main_Form();

private slots:

    void on_pushButton_clicked();

private:
    Ui::Main_Form *ui;
};

#endif // MAIN_FORM_H
