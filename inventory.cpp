#include "inventory.h"
#include <QDebug>

bool Inventory::mapHasItem(const SingleItemStorageType &map, ItemTypeStorage itemKey) const
{
    return map.find(itemKey) != map.cend();
}

int Inventory::addItemToStorage(Inventory::SingleItemStorageType &itemsMap, ItemType type, int howMuchAdded)
{
    auto key = static_cast<ItemTypeStorage>(type);
    if (mapHasItem(itemsMap, key)) {//такой элемент уже есть
        itemsMap[key] += howMuchAdded;
    } else {//такого элемента ещё нет
        itemsMap[key] = howMuchAdded;
    }
    return itemsMap[key];
}

int Inventory::deleteItemFromStorage(Inventory::SingleItemStorageType &itemsMap, ItemType type, int howMuchDeleted)
{
    auto key = static_cast<ItemTypeStorage>(type);
    //такой элемент есть
    if (mapHasItem(itemsMap, key)) {
        int &count = itemsMap[key];
        if (count - howMuchDeleted >= 0) {
            count -= howMuchDeleted;
        } else {
            qDebug() << "Inventory::deleteItemFromStorage - deleting too much items from storage";
            count = 0;
        }
        return count;
    } else {//такого элемента нет
        qDebug() << "Inventory::deleteItemFromStorage - deleting unexistent item";
    }
    return amountErrVal;
}

void Inventory::moveItemsFromImpl(int fromRow, int fromColumn, int toRow, int toColumn)
{
    SingleItemStorageType &from = matrix[fromRow][fromColumn];
    SingleItemStorageType &to = matrix[toRow][toColumn];

    for (auto i = from.begin(); i != from.end(); ++i) {
        auto type = static_cast<ItemType>(i.key());
        int amountAdded = addItemToStorage(to, type, i.value());
        emit itemAdded(toRow, toColumn, type, amountAdded);

        i.value() = 0;
        emit itemDeleted(fromRow, fromColumn, type, 0);
    }
}

int Inventory::seeItemAmount(const SingleItemStorageType &map, ItemType type) const
{
    auto key = static_cast<ItemTypeStorage>(type);
    if (mapHasItem(map, key)) {
        return map[key];
    } else {
        qDebug() << "Inventory::seeItemAmount - looking for amount of unexistent item";
        return amountErrVal;
    }
}

bool Inventory::isValidPosition(int row, int column) const
{
    return row < matrix.size() && column < matrix[row].size();
}

Inventory::Inventory(int rows_, int columns_, QObject *parent)
    : QObject(parent)
    , rows(rows_)
    , columns(columns_)
    , matrix(rows_, QVector<SingleItemStorageType>(columns_))
{
    qDebug() << matrix;
}

int Inventory::getItemAmount(int row, int column, ItemType type)
{
    if (isValidPosition(row, column)) {
        int amount = seeItemAmount(matrix[row][column], type);
        if (amount != amountErrVal) {
            emit itemAmountOn(row, column, type, amount);
        }
        return amount;
    } else {
        qDebug() << "Inventory::getItemAmount - invalid position";
        return amountErrVal;
    }
}

void Inventory::addItem(int row, int column, ItemType type, int howMuchAdded)
{
    //валидная позиция
    if (isValidPosition(row, column)) {
        SingleItemStorageType &itemsMap = matrix[row][column];
        int newAmount = addItemToStorage(itemsMap, type, howMuchAdded);
        emit itemAdded(row, column, type, newAmount);
    } else {//невалидная позиция
        qDebug() << "Inventory::addItem - invalid position";
    }
}

void Inventory::deleteItem(int row, int column, ItemType type, int howMuchDeleted)
{
    //валидная позиция
    if (isValidPosition(row, column)) {
        SingleItemStorageType &itemsMap = matrix[row][column];
        int newAmount = deleteItemFromStorage(itemsMap, type, howMuchDeleted);
        emit itemDeleted(row, column, type, newAmount);
    } else {//невалидная позиция
        qDebug() << "Inventory::deleteItem - invalid position";
    }
}

void Inventory::moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (isValidPosition(fromRow, fromColumn) && isValidPosition(toRow, toColumn)) {
        moveItemsFromImpl(fromRow, fromColumn, toRow, toColumn);
    }
}
