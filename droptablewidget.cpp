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
    //позволяем драгать и дропать на табличку
    this->setDragDropMode(QAbstractItemView::DragDrop);
}

void AppleDropTableWidget::playSound()
{
    //играем звук
    QSound::play(appleNibbleSoundPath);
}

void AppleDropTableWidget::dropEvent(QDropEvent *event)
{
    QModelIndex index = this->indexAt(event->pos());
    QString mimeString = event->mimeData()->text();
    //если дроп пришёл из виджета с яблочком
    if (mimeString.startsWith(appleLabelDragText)) {
        //смотрим тип
        int type = mimeString.split("/").last().toInt();
        //кидаем сигнал
        emit itemAddedOn(index.row(), index.column(), static_cast<ItemType>(type), 1);
    } else if (mimeString.startsWith(tableDragText)) {//если дроп пришёл из инвентаря
        auto parts = mimeString.split('/');
        //смотрим откуда
        int fromRow = parts[1].toInt();
        int fromColumn = parts[2].toInt();
        //кидаем сигнал
        emit moveItemsFrom(fromRow, fromColumn, index.row(), index.column());
    }
}

//чтобы можно было ловить дроп ивенты
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
    //ПКМ
    if (event->button() == Qt::RightButton) {
        QModelIndex index = this->indexAt(event->pos());
        //удаляем одно яблоко
        emit itemDeletedOn(index.row(), index.column(), ItemType::apple, 1);
    } else if (event->button() == Qt::LeftButton) {//ЛКМ
        //стартуем драг
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QModelIndex index = this->indexAt(event->pos());

        //заливаем инфу о драге
        QString mimeText = QString(tableDragText)
                + '/'
                + QString().setNum(index.row())
                + '/'
                + QString().setNum(index.column());
        mimeData->setText(mimeText);
        drag->setMimeData(mimeData);
        //execute
        drag->exec();
    }
}
