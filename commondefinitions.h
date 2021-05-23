#ifndef COMMONDEFINITIONS_H
#define COMMONDEFINITIONS_H

#include <QString>

using ItemTypeStorage = int;
//enum для хранения типов предметов
enum class ItemType : ItemTypeStorage {
    apple = 1//ВСЕГДА ДОЛЖНО БЫТЬ НАВЕРХУ
};

//возвращает строку, в которой номер данного типа
QString getStringMarker(ItemType type);
//возвращает строку с названием данного типа
QString getTypeAsString(ItemType type);
//возвращает путь к картинке для данного типа
QString getPicPath(ItemType type);

//пути к картинкам
constexpr char defaultPicPath[] = ":/images/defaultpic.jpg";
constexpr char bigApplePath[] = ":/images/bigapple.jpg";
constexpr char smallApplePath[] = ":/images/smallapple.jpg";
constexpr char appleNibbleSoundPath[] = ":/sounds/applenibble.wav";

//миме дата для drag'n'drop ивентов
constexpr char appleLabelDragText[] = "appleLabelDrag";
constexpr char tableDragText[] = "tableDrag";

#endif // COMMONDEFINITIONS_H
