#include "commondefinitions.h"

QString getStringMarker(ItemType type)
{
    QString result;
    result.setNum(static_cast<ItemTypeStorage>(type));
    return result;
}

QString getTypeAsString(ItemType type)
{
    switch (type) {
    case ItemType::apple: return "apple";
    }
}

QString getPicPath(ItemType type)
{
    switch (type) {
    case ItemType::apple: return smallApplePath;
    }
}
