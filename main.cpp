#include "application.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QDir>

constexpr int rows = 3;
constexpr int columns = 3;
constexpr char databaseRelativePath[] = "/databases/gamedata";

/*
 * таблица gamedata создана следующими командами:

create table items (
    item_id integer primary key not null
    , item_name text
    , item_pic_path text
);

create table inventory (
    item_id integer
    , row integer
    , col integer
    , amount integer
    , foreign key (item_id) references items(item_id)
);

*/

int main(int argc, char *argv[])
{
    //находим, где лежит база данных
    QDir dir{QDir::currentPath()};
    dir.cdUp();
    dir.cd("GameInventory");
    //запускаем приложение
    Application a(dir.path() + databaseRelativePath, rows, columns, argc, argv);
    return a.exec();
}
