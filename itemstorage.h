#ifndef ITEMSTORAGE_H
#define ITEMSTORAGE_H

#include "item.h"
#include <QMap>
#include "database.h"

///
/// \brief хранилище всех типов предметов и их картинок
///
using GlobalItemStorage = QMap<ItemType, QPixmap>;

//добавить предмет типа type в хранилище и в табличку items базы данных
void addItemToGlobalStorage(GlobalItemStorage &storage, DatabaseHolder &db, ItemType type);
//добавить все имеющиеся типы предметов в хранилище и в табличку items базы данных
void addAllItemsToGlobalStorage(GlobalItemStorage &storage, DatabaseHolder &db);

#endif // ITEMSTORAGE_H
