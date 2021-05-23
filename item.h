#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QPixmap>
#include "commondefinitions.h"

///
/// \brief устанавливает соответствие между ItemType
/// и соответствующей ему картинкой
///
class Item
{
    ItemType type;
    QString picWay{};

    //установить относительный путь до картинки
    void setPicWay(ItemType t);


public:
    Item(ItemType t);
    //какой пиксмап у данного типа?
    QPixmap getPixmap() const;
};

#endif // ITEM_H
