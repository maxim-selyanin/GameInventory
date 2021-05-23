#include "application.h"
#include "mainmenu.h"
#include <QGridLayout>
#include <QMainWindow>

Application::Application(const QString &databasePath, int rows_, int columns_, int argc, char *argv[])
    : QApplication(argc, argv)
    , rows(rows_)
    , columns(columns_)
    , databaseHandle(databasePath, databaseConnectionName)
    , inventory(new Inventory(rows_, columns_))
{
    //сигналы от инвентаря
    connect(inventory, &Inventory::itemAdded, this, &Application::itemAmountChanged);
    connect(inventory, &Inventory::itemDeleted, this, &Application::itemAmountChanged);

    //добавляем все имеющиеся типа в мапу itemTypes и в таблицу items
    addAllItemsToGlobalStorage(itemTypes, databaseHandle);

    //главное меню
    MainMenu *mainMenu = new MainMenu;
    connect(mainMenu, &MainMenu::newGame, this, &Application::makeNewInventory);
    connect(mainMenu, &MainMenu::exitSignal, this, &QApplication::quit, Qt::QueuedConnection);


    mainWindow = new QMainWindow;
    mainWindow->setMinimumSize(1150, 800);
    mainWindow->setMenuWidget(mainMenu);
    mainWindow->show();
}

Application::~Application()
{
    //mainmenu and inventory are children of mainWindow
    mainWindow->deleteLater();
    inventory->deleteLater();
    clearInventoryInDatabase();
}

void Application::makeNewInventory()
{
    //очищаем инвентари в модели данных и в базе данных
    clearInventoryInDatabase();
    inventory->clear();

    //создаём новый виджет с инвентарём
    InventoryWidget *inventoryWidget = new InventoryWidget(rows, columns);

    //коннектим нужные сигналы-слоты
    connect(inventoryWidget, &InventoryWidget::showMainMenu, this, &Application::showBackMainMenu);
    connect(inventory, &Inventory::itemEaten, inventoryWidget, &InventoryWidget::playSound);
    connect(inventoryWidget, &InventoryWidget::itemAddedOn, inventory, &Inventory::addItem);
    connect(inventoryWidget, &InventoryWidget::itemDeletedOn, inventory, &Inventory::deleteItem);
    connect(inventoryWidget, &InventoryWidget::moveItemsFrom, inventory, &Inventory::moveItemsFrom);
    connect(this, &Application::itemAmountChangedPixmapSignal, inventoryWidget, &InventoryWidget::changedAmountOn);

    //убираем менюшку
    mainWindow->menuWidget()->hide();
    mainWindow->setCentralWidget(inventoryWidget);
    mainWindow->show();
    mainWindow->centralWidget()->show();
}

void Application::showBackMainMenu()
{
    //дизаблим виджет с инвентарём, показываем менюшку
    mainWindow->centralWidget()->setDisabled(true);
    mainWindow->menuWidget()->show();
}

void Application::clearInventoryInDatabase()
{
    //чистим таблицу inventory
    databaseHandle.clearInventory();
}

void Application::itemAmountChanged(int row, int column, ItemType type, int newAmount)
{
    //кидаем сигналы об изменении количества предметов типа type на newAmount в клетке row x column
    emit itemAmountChangedPixmapSignal(row, column, itemTypes[type], newAmount);
    databaseHandle.changeAmount(type, row, column, newAmount);
}
