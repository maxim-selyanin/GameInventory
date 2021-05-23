#ifndef DROPTABLEWIDGET_H
#define DROPTABLEWIDGET_H

#include <QTableWidget>
#include "commondefinitions.h"

///
/// \brief реализует отображение инвентаря
///
class AppleDropTableWidget : public QTableWidget
{
    Q_OBJECT

protected:
    //drop event
    virtual void dropEvent(QDropEvent *event) override;

    //разрешаем эти ивенты, чтобы можно было принимать дроп ивенты
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;

    //здесь происходит удаление яблок и драг ивент в другие клетки
    virtual void mousePressEvent(QMouseEvent *event) override;

public:
    explicit AppleDropTableWidget(int rows, int columns, QWidget *parent = nullptr);

public slots:
    //играть звук
    void playSound();

signals:
    //добавление айтема типа type в строку row, столбец column в количестве amountOf
    void itemAddedOn(int row, int column, ItemType type, int amountOf);
    //удаление айтема типа type из строки row, столбца column в количестве amountOf
    void itemDeletedOn(int row, int column, ItemType type, int amountOf);
    //перетаскивание всех айтемов из клетки fromRow x fromColumn в клетку toRow x toColumn
    void moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn);
};

#endif // DROPTABLEWIDGET_H
