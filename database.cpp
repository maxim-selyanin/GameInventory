#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

void DatabaseHolder::insertQuery(ItemTypeStorage id, int row, int column, int newAmount)
{
    //вставляем строку в inventory
    QSqlQuery query(database);

    query.prepare("insert into inventory values (:id, :row, :column, :newAmount);");
    query.bindValue(":id", id);
    query.bindValue(":row", row);
    query.bindValue(":column", column);
    query.bindValue(":newAmount", newAmount);

    query.exec();
}

void DatabaseHolder::updateQuery(ItemTypeStorage id, int row, int column, int newAmount)
{
    //обновляем amount в нужной строке inventory
    QSqlQuery query(database);

    query.prepare("update inventory set amount = :newAmount where item_id = :id and row = :row and col = :column;");
    query.bindValue(":id", id);
    query.bindValue(":row", row);
    query.bindValue(":column", column);
    query.bindValue(":newAmount", newAmount);

    query.exec();
}

void DatabaseHolder::deleteQuery(ItemTypeStorage id, int row, int column)
{
    //удаляем строку из inventory
    QSqlQuery query(database);

    query.prepare("delete  from inventory where item_id = :id and row = :row and col = :column;");
    query.bindValue(":id", id);
    query.bindValue(":row", row);
    query.bindValue(":column", column);

    query.exec();
}

DatabaseHolder::DatabaseHolder(const QString &databasePath, const QString &connectionName)
    : database(QSqlDatabase::addDatabase("QSQLITE", connectionName))
{
    //ставим имя датабазы и открываем её
    database.setDatabaseName(databasePath);
    database.open();
}

bool DatabaseHolder::isValid() const
{
    //является ли бд валидной и открытой?
    return database.isValid() && database.isOpen();
}

void DatabaseHolder::addNewItemType(ItemType type)
{
    if (!isValid()) {
        return;
    }
    //добавляем новый тип предмета в items
    QSqlQuery query(database);
    query.prepare("insert into items values (:id, :name, :picPath);");
    query.bindValue(":id", static_cast<ItemTypeStorage>(type));
    query.bindValue(":name", getTypeAsString(type));
    query.bindValue(":picPath", getPicPath(type));
    query.exec();
}

void DatabaseHolder::changeAmount(ItemType type, int row, int column, int newAmount)
{
    if (!isValid()) {
        return;
    }
    QSqlQuery query(database);

    //смотрим количество предметов данного типа в данной клетке
    auto id = static_cast<ItemTypeStorage>(type);
    query.prepare("select amount from inventory where item_id = :id and row = :row and col = :column;");
    query.bindValue(":id", id);
    query.bindValue(":row", row);
    query.bindValue(":column", column);

    //если изначальный запрос проходит успешно
    if (query.exec()) {
        if (query.next()) {//запрос что то возвращает
            //строка уже есть
            if (newAmount == 0) {
                deleteQuery(id, row, column);
            } else {
                updateQuery(id, row, column, newAmount);
            }
        } else {//запрос ничего не возвращает
            //строки нет
            insertQuery(id, row, column, newAmount);
        }
    }
}

void DatabaseHolder::clearInventory()
{
    if (!isValid()) {
        return;
    }
    QSqlQuery query(database);
    query.prepare("delete from inventory;");
    query.exec();
}
