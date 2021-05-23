#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QPixmap>
#include "draglabel.h"
#include "droptablewidget.h"

class InventoryWidget : public QWidget
{
    Q_OBJECT

    const int rows;
    const int columns;

    AppleDropTableWidget *tableWidget = nullptr;

    AppleDropTableWidget* createTableWidget();
    DragAppleLabel* createAppleWidget();
    QPushButton* createMainMenuButton();

    static QPixmap getPixmap(const QPixmap &pixmap, int amount);
    static constexpr int textHorizontalOffset = 20;
    static constexpr int textVerticalOffset = 20;
    static constexpr int textSize = 10;

public:
    explicit InventoryWidget(int rows_, int columns_, QWidget *parent = nullptr);
    ~InventoryWidget();

public slots:
    void changedAmountOn(int row, int column, const QPixmap &pic, int newAmount);//

signals:
    void showMainMenu();//
    void itemAddedOn(int row, int column, ItemType type, int amountOf);//
    void itemDeletedOn(int row, int column, ItemType type, int amountOf);//
    void moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn);
};

#endif // INVENTORYWIDGET_H
