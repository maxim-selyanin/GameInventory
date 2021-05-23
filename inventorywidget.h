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

    //строки-столбцы
    const int rows;
    const int columns;

    //инвентарь per se
    AppleDropTableWidget *tableWidget = nullptr;

    //создания инвентаря, яблочного виджета и кнопки главного меню
    AppleDropTableWidget* createTableWidget();
    DragAppleLabel* createAppleWidget();
    QPushButton* createMainMenuButton();

    //pixmap с нарисованным числом amount справа внизу
    static QPixmap getPixmap(const QPixmap &pixmap, int amount);

    //параметры текста на вышеописанной пиксмапе
    static constexpr int textHorizontalOffset = 20;
    static constexpr int textVerticalOffset = 20;
    static constexpr int textSize = 10;

public:
    explicit InventoryWidget(int rows_, int columns_, QWidget *parent = nullptr);
    ~InventoryWidget() override;

public slots:
    //в клетке row x column стало newAmount предметов с картинкой pic
    void changedAmountOn(int row, int column, const QPixmap &pic, int newAmount);//

signals:
    //показать главное меню
    void showMainMenu();
    //в клетку row x column добавили amountOf предметов типа type
    void itemAddedOn(int row, int column, ItemType type, int amountOf);
    //из клетки row x column удалили amountOf предметов типа type
    void itemDeletedOn(int row, int column, ItemType type, int amountOf);
    //из клетки fromRow x fromColumn переместили все предметы в клетку toRow x toColumn
    void moveItemsFrom(int fromRow, int fromColumn, int toRow, int toColumn);
    //нужно воспроизвести звук
    void playSound();
};

#endif // INVENTORYWIDGET_H
