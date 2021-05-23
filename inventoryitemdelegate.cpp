#include "inventoryitemdelegate.h"
#include <QDebug>
#include "commondefinitions.h"

InventoryItemDelegate::InventoryItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    //
}

QSize InventoryItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QPixmap(defaultPicPath).size();
}
