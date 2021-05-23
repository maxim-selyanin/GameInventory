#include "itemstorage.h"

void addItemToGlobalStorage(GlobalItemStorage &storage, DatabaseHolder &db, ItemType type)
{
    storage[type] = Item(type).getPixmap();
    db.addNewItemType(type);
}

void addAllItemsToGlobalStorage(GlobalItemStorage &storage, DatabaseHolder &db)
{
    //пробегаемся в свитче по всем имеющимся типам
    ItemType dummy = ItemType::apple;
    switch (dummy) {
    case ItemType::apple: {
        addItemToGlobalStorage(storage, db, ItemType::apple);
    }//no break to add all existing items
    }
}
