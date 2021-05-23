#include "commondefinitions.h"

QString getStringMarker(ItemType type)
{
    QString result;
    result.setNum(static_cast<ItemTypeStorage>(type));
    return result;
}
