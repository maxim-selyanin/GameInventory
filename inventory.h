#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "item.h"

///
/// \brief реализует модель данных, хранящую данные о количестве предметов в инвентаре
/// этот функционал можно было реализовать прямо в AppleDropTableWidget,
/// но я сделал отдельный класс в целях уменьшения связности проекта
/// и большей автономности его частей
///
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
    //error value для количества, чтобы не запутаться
    static constexpr int amountErrVal = -1;

    //строки-столбцы
    const int rows;
    const int columns;
    //матрица
    ItemMatrix matrix;

    //есть ли айтем с ключом itemKey в мапе map?
    bool mapHasItem(const SingleItemStorageType &map, ItemTypeStorage itemKey) const;
    //добавляем howMuchAdded айтемов типа type в мапу itemsMap
    [[nodiscard]] int addItemToStorage(SingleItemStorageType &itemsMap, ItemType type, int howMuchAdded);
    //удаляем howMuchAdded айтемов типа type из мапы itemsMap
    [[nodiscard]] int deleteItemFromStorage(SingleItemStorageType &itemsMap, ItemType type, int howMuchDeleted);

    //перемещаем все айтемы из from в to
    void moveItemsFromImpl(int fromRow, int fromColumn, int toRow, int toColumn);

    //смотрим, сколько айтемов типа type лежит в мапе map
    int seeItemAmount(const SingleItemStorageType &map, ItemType type) const;

    //есть ли в матрице позиция row x column?
    bool isValidPosition(int row, int column) const;

public:
    explicit Inventory(int rows_, int columns_, QObject *parent = nullptr);
    //очищаем все данные
    void clear();

public slots:
    //добавляем howMuchAdded айтемов типа type в клетку row x column
    void addItem(int row, int column, ItemType type, int howMuchAdded);//
    //удаляем howMuchAdded айтемов типа type из клетки row x column
    void deleteItem(int row, int column, ItemType type, int howMuchDeleted);//

    //перемещаем все айтемы из from в to
    void moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn);

    //сколько айтемов типа type лежит в клетке row x column
    int getItemAmount(int row, int column, ItemType type);

signals:
    //после добавления предмета типа type в клетку row x column в этой клетке стало newAmount предметов этого типа
    void itemAdded(int row, int column, ItemType type, int newAmount);
    //после удаления предмета типа type из клетки row x column в этой клетке стало newAmount предметов этого типа
    void itemDeleted(int row, int column, ItemType type, int newAmount);
    //съели яблоко, нужно воспроизвести звук
    void itemEaten();
    //в клетке row x column лежит amount предметов типа type
    void itemAmountOn(int row, int column, ItemType type, int amount);
};

#endif // INVENTORY_H
