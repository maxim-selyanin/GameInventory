#ifndef APPLICATION_H
#define APPLICATION_H

#include "mainmenu.h"
#include "inventorywidget.h"
#include <QApplication>
#include "itemstorage.h"
#include "inventory.h"

class Application : public QApplication
{
    Q_OBJECT

    const int rows;
    const int columns;

    MainMenu *mainMenu = nullptr;
    InventoryWidget *inventoryWidget = nullptr;

    GlobalItemStorage itemTypes{};
    Inventory *inventory;

    void deleteInventoryIfNesessary();

public:
    explicit Application(int rows_, int columns_, int argc, char *argv[]);

    ~Application();

private slots:
    void makeNewInventory();
    void showBackMainMenu();

public slots:
    void itemAmountChanged(int row, int column, ItemType type, int newAmount);

signals:
    void itemAmountChangedPixmapSignal(int row, int column, const QPixmap &pic, int newAmount);

};

#endif // APPLICATION_H
