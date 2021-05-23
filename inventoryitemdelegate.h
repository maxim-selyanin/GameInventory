#ifndef INVENTORYITEMDELEGATE_H
#define INVENTORYITEMDELEGATE_H

#include <QStyledItemDelegate>

///
/// \brief делегат, устанавливающий нужный размер клетки
///
class InventoryItemDelegate : public QStyledItemDelegate
{
public:
    explicit InventoryItemDelegate(QObject *parent = nullptr);
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // INVENTORYITEMDELEGATE_H
