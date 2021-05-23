#ifndef DROPTABLEWIDGET_H
#define DROPTABLEWIDGET_H

#include <QTableWidget>
#include "commondefinitions.h"

class AppleDropTableWidget : public QTableWidget
{
    Q_OBJECT

    void playSound() const;

protected:
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;

public:
    explicit AppleDropTableWidget(int rows, int columns, QWidget *parent = nullptr);

signals:
    void itemAddedOn(int row, int column, ItemType type, int amountOf);
    void itemDeletedOn(int row, int column, ItemType type, int amountOf);

    void moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn);
};

#endif // DROPTABLEWIDGET_H
