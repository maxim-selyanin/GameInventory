#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include "commondefinitions.h"

///
/// \brief инкапсулирует запросы к базе данных
///
class DatabaseHolder
{
    QSqlDatabase database;

    //запрос на вставку новой строки
    void insertQuery(ItemTypeStorage id, int row, int column, int newAmount);
    //запрос на апдейт amount в строке с id, row, column
    void updateQuery(ItemTypeStorage id, int row, int column, int newAmount);
    //запрос на удаление строки с id, row, column
    void deleteQuery(ItemTypeStorage id, int row, int column);

public:
    //принимает путь к базе данных и имя соединения
    DatabaseHolder(const QString &databasePath, const QString &connectionName = QLatin1String(QSqlDatabase::defaultConnection));

    //валидна ли бд?
    bool isValid() const;
    //добавляет новый тип в таблицу items
    void addNewItemType(ItemType type);
    //меняет количество предметов в строке type, row, column в таблице inventory
    void changeAmount(ItemType type, int row, int column, int newAmount);
    //очищает таблицу inventory
    void clearInventory();
};

#endif // DATABASE_H
