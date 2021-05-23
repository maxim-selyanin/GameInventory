#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "item.h"

class Inventory : public QObject
{
    Q_OBJECT

public:
    //global using declarations
    template<typename T>
    using MatrixType = QVector<QVector<T> >;
    template<typename KeyType, typename ValueType>
    using AssociativeArrayType = QMap<KeyType, ValueType>;

    using SingleItemStorageType = AssociativeArrayType<ItemTypeStorage, int>;
    using ItemMatrix = MatrixType<SingleItemStorageType>;

private:
    static constexpr int amountErrVal = -1;

    //
    const int rows;
    const int columns;
    ItemMatrix matrix;

    //
    bool mapHasItem(const SingleItemStorageType &map, ItemTypeStorage itemKey) const;
    //
    [[nodiscard]] int addItemToStorage(SingleItemStorageType &itemsMap, ItemType type, int howMuchAdded);
    [[nodiscard]] int deleteItemFromStorage(SingleItemStorageType &itemsMap, ItemType type, int howMuchDeleted);

    void moveItemsFromImpl(int fromRow, int fromColumn, int toRow, int toColumn);

    int seeItemAmount(const SingleItemStorageType &map, ItemType type) const;

    bool isValidPosition(int row, int column) const;

public:
    explicit Inventory(int rows_, int columns_, QObject *parent = nullptr);


public slots:
    void addItem(int row, int column, ItemType type, int howMuchAdded);//
    void deleteItem(int row, int column, ItemType type, int howMuchDeleted);//

    void moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn);

    int getItemAmount(int row, int column, ItemType type);//useless

signals:
    void itemAdded(int row, int column, ItemType type, int newAmount);
    void itemDeleted(int row, int column, ItemType type, int newAmount);

    void itemAmountOn(int row, int column, ItemType type, int amount);//useless
};

#endif // INVENTORY_H
