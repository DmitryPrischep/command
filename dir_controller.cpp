#include "dir_controller.h"
Dir_Controller::Dir_Controller()
{

}

Dir_Controller::Dir_Controller(const set<string> &list)
{
    clearAll(); //Стираем предыдущие директории и пути файлов
    list_of_files = list;
}

Dir_Controller &Dir_Controller::operator <<(const string &dir)
{
  list_of_files.insert(dir);
  return *this;
}

bool Dir_Controller::contains(const string &dir)
{
    return list_of_files.count(dir) > 0;
}

void Dir_Controller::remove(const string &dir)
{
    list_of_files.erase(dir);
}

void Dir_Controller::clearAll()
{
    list_of_files.clear();
}

set<string> Dir_Controller::sendList() const
{
    return list_of_files;
}

Options Dir_Controller::sendOptions() const
{
  return options;
}
