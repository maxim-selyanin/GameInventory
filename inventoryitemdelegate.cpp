#include "inventoryitemdelegate.h"
#include <QDebug>
#include "commondefinitions.h"

InventoryItemDelegate::InventoryItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    //
}

QSize InventoryItemDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
    return QPixmap(defaultPicPath).size();
}
