#include "main_form.h"
#include "ui_main_form.h"
#include <QDebug>
#include <QFileInfo>
Main_Form::Main_Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_Form)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui->tree->setModel(model);
    ui->tree->resizeColumnToContents(0);
    //#############################################################################################
    path_to_archive = "";
    //При нажатиях на файловом менеджере (или раскрытии/скрытии директорий) растягиваем поле под содержимое
    connect(ui->tree, &QTreeView::clicked, [this](){ui->tree->resizeColumnToContents(0);});
    connect(ui->tree, &QTreeView::collapsed, [this](){ui->tree->resizeColumnToContents(0);});
    connect(ui->tree, &QTreeView::expanded, [this](){ui->tree->resizeColumnToContents(0);});
    ui->archive_button->setEnabled(false);
    ui->dearchive_button->setEnabled(false);
}

Main_Form::~Main_Form()
{
    delete ui;
}

void Main_Form::dragEnterEvent(QDragEnterEvent *event)
{
        event->acceptProposedAction();

}

void Main_Form::dragMoveEvent(QDragMoveEvent *event)
{
  event->acceptProposedAction();
}

void Main_Form::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
        foreach(QUrl url, urls)
        {
            //здесь вызываем вашу функцию добавления в список, а пока строкой ниже выводим названия файлов в консоль
            qDebug()<<url.toString();
        }
}

void Main_Form::on_archive_button_clicked()
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

  // set<string> temp = dir_controller.sendList(); //Временный накопитель директорий текущей операции
   std::string password = ui->password->text().toStdString();
   std::string password_confirmation = ui->password_confirmation->text().toStdString();
   if (password == password_confirmation) {
           create_archive(dir_controller.sendList(), true, path_to_archive);
           encrypt_archive(path_to_archive, password);
           QMessageBox::information(nullptr, "Архивация", "Архив создан!");
   }
   else {
           QMessageBox::critical(nullptr, "Несовпадение паролей", "Пароли не совпадают!");
   }
   ui->password->clear();
   ui->password_confirmation->clear();
   ui->password->setFocus();

        /*
        else {
            delete set_password_dialog;
            QMessageBox::warning(nullptr, "Несоответствие", "Введенные пароли не совпадают!");
            return; //Исправить повторный ввод пароля
        }
        */
  //  foreach (string str, temp) {
  //     qDebug() << QString::fromStdString(str);
  //  }

}

void Main_Form::on_action_11_triggered()
{
    PasswordForm *w = new PasswordForm;
    w->show();
}

void Main_Form::on_pushButton_2_clicked()
{
  QString checked_string = QFileDialog::getSaveFileName(nullptr, "Выбор места для сохранения архива",
                                                            "/", "*.tartar");
  if (!checked_string.isEmpty()) {
      ui->label_with_path->setText("Путь до архива: " + checked_string);
      path_to_archive = checked_string.toStdString();
      ui->archive_button->setEnabled(true);
  }
}

void Main_Form::on_dearchive_button_clicked()
{
    PasswordForm *password_form = new PasswordForm;
    if (password_form->exec() == QDialog::Accepted) {
        QString password = password_form->getPassword(); /*ui->password->text().toStdString();*/
        decrypt_archive(path_to_archive, password.toStdString());
        QString another_path;
        for (int i = 0; i < path_to_archive.length() - 2; ++i) {
            another_path += path_to_archive[i];
        }
        dearchive(another_path.toStdString());
        QMessageBox::information(nullptr, "Распаковка", "Распаковка успешно завершена!");
    }
}

void Main_Form::on_pushButton_4_clicked()
{
    QString checked_string = QFileDialog::getOpenFileName(nullptr, "Выберите архив для распаковки",
                                                              "/", "*.tartaren");
    if (!checked_string.isEmpty()) {
        ui->label_to_archive->setText("Путь до архива: " + checked_string);
        path_to_archive = checked_string.toStdString();
        ui->dearchive_button->setEnabled(true);
    }
}
