#include "item.h"

void Item::setPicWay(ItemType t)
{
    picWay = getPicPath(t);
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
