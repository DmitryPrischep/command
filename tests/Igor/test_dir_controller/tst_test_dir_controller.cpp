#include <QtTest>
#include <QStringList>
#include "../../../dir_controller.h"
// add necessary includes here

class Test_Dir_Controller : public QObject
{
    Q_OBJECT

public:
    Test_Dir_Controller();
    ~Test_Dir_Controller();

private slots: 
    void test_sendList_data();
    void test_sendList();

};

Test_Dir_Controller::Test_Dir_Controller()
{

}

Test_Dir_Controller::~Test_Dir_Controller()
{

}

void Test_Dir_Controller::test_sendList_data()
{
   QTest::addColumn<QStringList>("list_of_directories");
   QTest::addColumn<QSet<QString>>("result_data");
   QStringList list;
   QSet<QString> answer;
   list << "/dir1" << "/dir2/dir" << "/";
   answer = list.toSet();
   QTest::addRow("test_1") << list << answer;
   list.clear();
   list << "/dir/dir1/dir2/dir3/main.cpp" << "/a.out" << "/temp.o" << "C:\\hab.png";
   answer = list.toSet();
   QTest::addRow("test_2") << list << answer;
}

void Test_Dir_Controller::test_sendList()
{
   QFETCH(QStringList, list_of_directories);
   QFETCH(QSet<QString>, result_data);
   Dir_Controller dir_controller(list_of_directories);
   QCOMPARE(dir_controller.sendList(), result_data);
}

QTEST_APPLESS_MAIN(Test_Dir_Controller)

#include "tst_test_dir_controller.moc"
