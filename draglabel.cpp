#include "draglabel.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include "commondefinitions.h"

DragAppleLabel::DragAppleLabel(QWidget *parent)
    : QLabel(parent)
{
    //
}

void DragAppleLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
           QDrag *drag = new QDrag(this);
           QMimeData *mimeData = new QMimeData;

           mimeData->setText(QString(appleLabelDragText) + "/" + getStringMarker(ItemType::apple));
           drag->setMimeData(mimeData);

           drag->exec();
       }
}
