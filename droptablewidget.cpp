#include "droptablewidget.h"
#include <QDebug>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QSound>
#include "commondefinitions.h"
#include <QDrag>

AppleDropTableWidget::AppleDropTableWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
    this->setDragDropMode(QAbstractItemView::DragDrop);
}

void AppleDropTableWidget::playSound() const
{
    QSound sound(appleNibbleSoundPath);
    sound.play();
}

void AppleDropTableWidget::dropEvent(QDropEvent *event)
{
    QModelIndex index = this->indexAt(event->pos());
    QString mimeString = event->mimeData()->text();
    if (mimeString.startsWith(appleLabelDragText)) {
        int type = mimeString.split("/").last().toInt();
        emit itemAddedOn(index.row(), index.column(), static_cast<ItemType>(type), 1);
    } else if (mimeString.startsWith(tableDragText)) {
        auto parts = mimeString.split('/');
        int fromRow = parts[1].toInt();
        int fromColumn = parts[2].toInt();
        emit moveItemsFrom(fromRow, fromColumn, index.row(), index.column());
    }
}

void AppleDropTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void AppleDropTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void AppleDropTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QModelIndex index = this->indexAt(event->pos());
        playSound();
        emit itemDeletedOn(index.row(), index.column(), ItemType::apple, 1);
    } else if (event->button() == Qt::LeftButton) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QModelIndex index = this->indexAt(event->pos());

        QString mimeText = QString(tableDragText)
                + '/'
                + QString().setNum(index.row())
                + '/'
                + QString().setNum(index.column());
        mimeData->setText(mimeText);
        drag->setMimeData(mimeData);

        drag->exec();
    }
}
