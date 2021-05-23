#ifndef COMMONDEFINITIONS_H
#define COMMONDEFINITIONS_H

#include <QString>

using ItemTypeStorage = int;
enum class ItemType : ItemTypeStorage {
    apple = 1//ВСЕГДА ДОЛЖНО БЫТЬ НАВЕРХУ
};

QString getStringMarker(ItemType type);

constexpr char defaultPicPath[] = ":/images/defaultpic.jpg";
constexpr char bigApplePath[] = ":/images/bigapple.jpg";
constexpr char smallApplePath[] = ":/images/smallapple.jpg";
constexpr char appleNibbleSoundPath[] = ":/sounds/applenibble.wav";

constexpr char appleLabelDragText[] = "appleLabelDrag";
constexpr char tableDragText[] = "tableDrag";

#endif // COMMONDEFINITIONS_H
