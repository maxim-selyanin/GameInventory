#ifndef ITEMSTORAGE_H
#define ITEMSTORAGE_H

#include "item.h"
#include <QMap>

using GlobalItemStorage = QMap<ItemType, QPixmap>;

void addItemToGlobalStorage(GlobalItemStorage &storage, ItemType type);
void addAllItemsToGlobalStorage(GlobalItemStorage &storage);

#endif // ITEMSTORAGE_H
