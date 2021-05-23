#include "application.h"
#include "mainmenu.h"
#include <QGridLayout>

void Application::deleteInventoryIfNesessary()
{
    if (inventoryWidget) {
        inventoryWidget->close();
        inventoryWidget->deleteLater();
    }
}

Application::Application(int rows_, int columns_, int argc, char *argv[])
    : QApplication(argc, argv)
    , rows(rows_)
    , columns(columns_)
    , inventory(new Inventory(rows_, columns_))
{
    mainMenu = new MainMenu;
    mainMenu->show();

    connect(mainMenu, &MainMenu::newGame, this, &Application::makeNewInventory);
    connect(mainMenu, &MainMenu::closed, mainMenu, &MainMenu::deleteLater);
    connect(mainMenu, &MainMenu::closed, this, &QApplication::quit);


    addAllItemsToGlobalStorage(itemTypes);


    connect(inventory, &Inventory::itemAdded, this, &Application::itemAmountChanged);
    connect(inventory, &Inventory::itemDeleted, this, &Application::itemAmountChanged);
}

Application::~Application()
{
    //mainmenu is already scheduled for deletion after closing
    deleteInventoryIfNesessary();
}

void Application::makeNewInventory()
{
    deleteInventoryIfNesessary();

    inventoryWidget = new InventoryWidget(rows, columns);
    connect(inventoryWidget, &InventoryWidget::showMainMenu, this, &Application::showBackMainMenu);

    connect(inventoryWidget, &InventoryWidget::itemAddedOn, inventory, &Inventory::addItem);
    connect(inventoryWidget, &InventoryWidget::itemDeletedOn, inventory, &Inventory::deleteItem);
    connect(inventoryWidget, &InventoryWidget::moveItemsFrom, inventory, &Inventory::moveItemsFrom);

    connect(this, &Application::itemAmountChangedPixmapSignal, inventoryWidget, &InventoryWidget::changedAmountOn);

    inventoryWidget->show();
}

void Application::showBackMainMenu()
{
    if (!inventoryWidget) {
        return;
    }

    inventoryWidget->setDisabled(true);

    mainMenu->raise();
}

void Application::itemAmountChanged(int row, int column, ItemType type, int newAmount)
{
    emit itemAmountChangedPixmapSignal(row, column, itemTypes[type], newAmount);
}
