#include "main_form.h"
#include "ui_main_form.h"
#include <QDebug>
#include <QFileInfo>
extern "C" {

}
Main_Form::Main_Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_Form)
{
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui->tree->setModel(model);
    ui->tree->resizeColumnToContents(0);
    //Создаем toolbar
    //#############################################################################################
    QToolBar *bar = new QToolBar("Main_ToolBar");
    bar->addAction(ui->action_8);
    ui->action_8->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton)));
    bar->addSeparator();
    bar->addAction(ui->action_5);
    bar->addAction(ui->action_7);
    bar->addSeparator();
    bar->addAction(ui->action_11);
    bar->addSeparator();
    bar->addAction(ui->action_2);
    addToolBar(bar);
    //#############################################################################################

    //При нажатиях на файловом менеджере (или раскрытии/скрытии директорий) растягиваем поле под содержимое
    connect(ui->tree, &QTreeView::clicked, [this](){ui->tree->resizeColumnToContents(0);});
    connect(ui->tree, &QTreeView::collapsed, [this](){ui->tree->resizeColumnToContents(0);});
    connect(ui->tree, &QTreeView::expanded, [this](){ui->tree->resizeColumnToContents(0);});

}

Main_Form::~Main_Form()
{
    delete ui;
}

void Main_Form::on_pushButton_clicked()
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(ui->tree->model());
    dir_controller.clearAll(); //Очищаем предыдущий список директорий и путей файлов
    //Добавляем в список для отправки все выделенные файлы
    //Функция для получения всех файлов внутри директории
    std::function<void(string)> getFiles = [this, &getFiles](string path) -> void {
            QFileInfo fileInfo(QString::fromStdString(path));
            //Если получили файл, тогда добавляем путь до него
            if (fileInfo.isFile())
               dir_controller << path;
            else if (fileInfo.isDir()){
                /* Если директория, то применяем рекурсия и получаем все пути файлов в ней
                 * и во вложенных директориях, если таковые имеются
                */
                QFileInfoList list_files = QDir(QString::fromStdString(path)).entryInfoList(); //Получаем содержимое каталога
                foreach (QFileInfo file, list_files) { //Проходимся по всем элементам каталога
                    string filePath = file.absoluteFilePath().toStdString();
                    string fileName = file.fileName().toStdString();
                    if (fileName == "." || fileName == "..") continue;
                        getFiles(filePath); //Рекурсивно добавляем все пути из директории
                }
            }
    };

    foreach (QModelIndex index, ui->tree->selectionModel()->selectedRows()) {
        QFileInfo fileInfo = model->fileInfo(index); //Получаем информацию о файле/директории
        string file = fileInfo.absoluteFilePath().toStdString(); //Получаем абсолютный путь до файла
            getFiles(file); //Получаем все пути из директории / путь до данного файла
    }

   set<string> temp = dir_controller.sendList(); //Временный накопитель директорий текущей операции
    foreach (string str, temp) {
       qDebug() << QString::fromStdString(str);
    }

}
