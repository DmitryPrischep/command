#ifndef DIR_CONTROLLER_H
#define DIR_CONTROLLER_H

#include <QObject>
#include <QString>
#include <QSet>

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
    QSet<QString> list_of_files;
    Options options;
public:
    explicit Dir_Controller();
    explicit Dir_Controller(const QStringList &list);
    Dir_Controller& operator << (const QString &);
    bool contains(const QString &);
    void remove(const QString &);
    void clearAll();
signals:

public slots:
    //Отправка списка файлов на архивацию и сжатие
    QSet<QString> sendList() const;
    Options sendOptions() const;
};

#endif // DIR_CONTROLLER_H
