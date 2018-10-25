#include <QtTest>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "../../../dir_controller.h"

class Test_Dir_Controller : public QObject
{
    Q_OBJECT

public:
    Test_Dir_Controller();
    ~Test_Dir_Controller();

private slots: 
//    void test_sendList_data();
    void test_sendList();

};

Test_Dir_Controller::Test_Dir_Controller()
{

}

Test_Dir_Controller::~Test_Dir_Controller()
{

}

void Test_Dir_Controller::test_sendList()
{
    /*
   QFETCH(QStringList, list_of_directories);
   QFETCH(QSet<QString>, result_data);
   Dir_Controller dir_controller(list_of_directories);
   QCOMPARE(dir_controller.sendList(), result_data);
   */
    QFile file;
    //Функция для создания нового пустого файла
    auto createFile = [&file](QString path) {
       file.setFileName(path);
       file.open(QIODevice::WriteOnly);
       file.close();
    };
    //Создаем первый файл
    createFile("example1.txt");
    //Создаем второй файл
    createFile("example2.txt");
    //Создаем директорию
    QDir().mkdir("Folder1");
    //И в ней создаем файлы
    createFile("Folder1/example3.txt");
    createFile("Folder1/example4.txt");
    createFile("Folder1/example5.txt");
    //Создаем вложенную директорию
    QDir().mkdir("Folder1/Folder2");
    //И в ней создаем файл
    createFile("Folder1/Folder2/example6.txt");
    /* Затем создаем еще одну директорию,
     * в которой не будет ни одного файла
     * (архиватор не будет добавлять папку,
     * в которой нет файлов
    */
    QDir().mkdir("Folder1/Folder2/Folder3");
    QStringList data;
    QString this_dir = QDir().absolutePath();
    //Заносим все пути до файлов в список
    data << this_dir + "/example1.txt" << this_dir + "/example2.txt" <<
            this_dir + "/Folder1/example3.txt" << this_dir + "/Folder1/example4.txt" <<
            this_dir + "/Folder1/example5.txt" << this_dir + "/Folder1/Folder2/example6.txt";
    //Выполняем инстанцирование класса Dir_Controller
    Dir_Controller dir_controller(data);
    //Сравниваем результаты
    QCOMPARE(QSet<QString>(data.toSet()), dir_controller.sendList());
    //Очистка временных файлов теста

    [this_dir]() {
        //Удаляем созданную папку Folder1 и все ее подпапки и подфайлы
        QDir(this_dir + "/Folder1").removeRecursively();
        //Удаляем файлы в данном каталоге
        QFile(this_dir + "/example1.txt").remove();
        QFile(this_dir + "/example2.txt").remove();
    }();
}

QTEST_APPLESS_MAIN(Test_Dir_Controller)

#include "tst_test_dir_controller.moc"
