#include "itemstorage.h"

void addItemToGlobalStorage(GlobalItemStorage &storage, ItemType type)
{
    storage[type] = Item(type).getPixmap();
}

void addAllItemsToGlobalStorage(GlobalItemStorage &storage)
{
    ItemType dummy = ItemType::apple;
    switch (dummy) {
    case ItemType::apple: {
        addItemToGlobalStorage(storage, ItemType::apple);
    }//no break to add all existing items
    }
}
