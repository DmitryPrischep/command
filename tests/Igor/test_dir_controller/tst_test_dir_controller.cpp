#include <QtTest>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <set>
#include "../../../dir_controller.h"
using namespace std;
enum Mode {FILE_MODE, LOGIC_MODE}; //Режимы файл/логика
class Test_Dir_Controller : public QObject
{
    Q_OBJECT
    Dir_Controller dir_controller;
    static void create_File_in_FileSystem(string path);
    static void create_File_in_LogicView(string path);
    void (*mode[2])(string); //Функция для создания нового пустого файла
    void (*create_File)(string);
public:
    Test_Dir_Controller();
    ~Test_Dir_Controller();

private slots: 
    void test_sendList(); //Тестирование на работу с файловой системой
};


void Test_Dir_Controller::create_File_in_FileSystem(string path)
{
    QFile file;
    file.setFileName(QString::fromStdString(path));
    file.open(QIODevice::WriteOnly);
    file.close();
}

void Test_Dir_Controller::create_File_in_LogicView(string path)
{
    list_of_files.insert(path);
}

Test_Dir_Controller::Test_Dir_Controller()
{
    mode[Mode::FILE_MODE] = create_File_in_FileSystem;
    mode[Mode::LOGIC_MODE] = create_File_in_LogicView;
}

Test_Dir_Controller::~Test_Dir_Controller()
{

}

set<string>& operator << (set<string>& list, const string &path) {
   list.insert(path);
   return list;
}

void Test_Dir_Controller::test_sendList()
{
    //Функция для создания нового пустого файла
    //Устанавливаем режим для работы с файлами
    int MODE_TEST = Mode::FILE_MODE;
    function<void(string)> create_Folder = [MODE_TEST](string path) {
        if (MODE_TEST == Mode::FILE_MODE) {
            QDir().mkdir(QString::fromStdString(path));
        }
    };
    for (int i = 0; i < 2; ++i) {
        create_File = mode[MODE_TEST];
        //#### Создание файлов и директорий ########
        //Создаем первый файл
        create_File("example1.txt");
        //Создаем второй файл
        create_File("example2.txt");
        //Создаем директорию
        create_Folder("Folder1");
        //И в ней создаем файлы
        create_File("Folder1/example3.txt");
        create_File("Folder1/example4.txt");
        create_File("Folder1/example5.txt");
        //Создаем вложенную директорию
        create_Folder("Folder1/Folder2");
        //И в ней создаем файл
        create_File("Folder1/Folder2/example6.txt");
        /* Затем создаем еще одну директорию,
        * в которой не будет ни одного файла
        * (архиватор не будет добавлять папку,
        * в которой нет файлов
        */
        create_Folder("Folder1/Folder2/Folder3");
        string this_dir = QDir().absolutePath().toStdString();
        //Заносим все пути до файлов в список
        set<string> expected;
        expected << (this_dir + string("/example1.txt")) << (this_dir + "/example2.txt") <<
            (this_dir + "/Folder1/example3.txt") << (this_dir + "/Folder1/example4.txt") <<
            (this_dir + "/Folder1/example5.txt") << (this_dir + "/Folder1/Folder2/example6.txt");
        //Выполняем инстанцирование класса Dir_Controller
        //#############Сравниваем результаты#############################
        QCOMPARE(expected, dir_controller.sendList());
        //Очистка временных файлов теста
        if (MODE_TEST == Mode::FILE_MODE) {
            [this_dir]() {
                //Удаляем созданную папку Folder1 и все ее подпапки и подфайлы
                QDir(QString::fromStdString(this_dir + "/Folder1")).removeRecursively();
                //Удаляем файлы в данном каталоге
                QFile(QString::fromStdString(this_dir + "/example1.txt")).remove();
                QFile(QString::fromStdString(this_dir + "/example2.txt")).remove();
            }();
        }
        else {}
        MODE_TEST = Mode::LOGIC_MODE; //Переходим в режим логики
    }
    foreach (string str, list_of_files) {
      qDebug() << QString::fromStdString(str);
    }
}

QTEST_APPLESS_MAIN(Test_Dir_Controller)

#include "tst_test_dir_controller.moc"
