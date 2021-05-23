#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

///
/// \brief лейбл с источником яблока, реализует начало драг ивента
///
class DragAppleLabel : public QLabel
{
    Q_OBJECT

public:
    explicit DragAppleLabel(QWidget *parent = nullptr);
    //запускает драг ивент при нажатии ЛКМ
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGLABEL_H
