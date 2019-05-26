#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QMainWindow>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
#include <QModelIndexList>
#include <QModelIndex>
#include "dir_controller.h"
#include "archive.h"
#include "passworddialog.h"
#include "passwordform.h"
#include <QMenu>
#include <QToolBar>
#include <QMessageBox>
#include <QIcon>
#include <assert.h>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QList>


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

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);

private slots:

    void on_archive_button_clicked();

    void on_action_11_triggered();

    void on_pushButton_2_clicked();

    void on_dearchive_button_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Main_Form *ui;
    std::string path_to_archive;
};

#endif // MAIN_FORM_H
