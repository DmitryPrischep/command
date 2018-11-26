#ifndef DIR_CONTROLLER_H
#define DIR_CONTROLLER_H

#include <QObject>
#include <QString>
#include <set>
#include <experimental/vector>
#include <iostream>
using namespace std;

/*
 * Класс Dir_Controller
 * Предоставляет методы для работы с группами файлов
 * Предназначен для отправления списка всех путей до файлов,
 * которые предстоит в дальнейшем сжать и/или зашифровать.
 */

//Набор настроек приложения
struct Options {

};

class Dir_Controller : public QObject
{
    Q_OBJECT
    //Список выделенных файлов для архивации
    set<string> list_of_files;
    Options options;
public:
    explicit Dir_Controller();
    explicit Dir_Controller(const set<string> &list);
    Dir_Controller& operator << (const string &);
    bool contains(const string &);
    void remove(const string &);
    void clearAll();
signals:

public slots:
    //Отправка списка файлов на архивацию и сжатие
    set<string> sendList() const;
    Options sendOptions() const;
};

#endif // DIR_CONTROLLER_H
