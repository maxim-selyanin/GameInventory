#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

class DragAppleLabel : public QLabel
{
    Q_OBJECT

public:
    explicit DragAppleLabel(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGLABEL_H
