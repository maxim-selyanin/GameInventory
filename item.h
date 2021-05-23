#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QPixmap>
#include "commondefinitions.h"

class Item
{
    ItemType type;
    QString picWay{};

    void setPicWay(ItemType t);


public:
    Item(ItemType t);
    QPixmap getPixmap() const;
};

#endif // ITEM_H
