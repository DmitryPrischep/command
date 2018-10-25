#include "dir_controller.h"

Dir_Controller::Dir_Controller()
{

}

Dir_Controller::Dir_Controller(const QStringList &list)
{
    clearAll(); //Стираем предыдущие директории и пути файлов
    foreach (QString dir, list) {
        *this << dir;
    }
}

Dir_Controller &Dir_Controller::operator <<(const QString &dir)
{
  list_of_files << dir;
  return *this;
}

bool Dir_Controller::contains(const QString &dir)
{
    return list_of_files.contains(dir);
}

void Dir_Controller::remove(const QString &dir)
{
    list_of_files.remove(dir);
}

void Dir_Controller::clearAll()
{
    list_of_files.clear();
}

QSet<QString> Dir_Controller::sendList() const
{
    return list_of_files;
}

Options Dir_Controller::sendOptions() const
{
  return options;
}
