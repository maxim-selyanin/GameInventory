#include "item.h"

void Item::setPicWay(ItemType t)
{
    switch (t) {
    case ItemType::apple: {
        picWay = smallApplePath;
        return;
    }
    }
}

Item::Item(ItemType t)
    : type(t)
{
    setPicWay(type);
}

QPixmap Item::getPixmap() const
{
    return QPixmap(picWay);
}
