#ifndef APPLICATION_H
#define APPLICATION_H

#include "mainmenu.h"
#include "inventorywidget.h"
#include <QApplication>
#include "itemstorage.h"
#include "inventory.h"
#include "database.h"
#include <QMainWindow>

///
/// \brief класс приложения, реализующий логику программы и взаимодействие между объектами
///
class Application : public QApplication
{
    Q_OBJECT

    //количество строк и столбцов в инвентаре
    const int rows;
    const int columns;

    //главное окно
    QMainWindow *mainWindow = nullptr;

    //мапа с типами и картинками предметов
    GlobalItemStorage itemTypes{};
    //дефолтное connection name для QSqlDatabase
    QString databaseConnectionName{"defaultdbc"};
    //класс, реализующий запросы к бд
    DatabaseHolder databaseHandle;
    //инвентарь
    Inventory *inventory;

public:
    explicit Application(const QString &databasePath, int rows_, int columns_, int argc, char *argv[]);

    ~Application();

private slots:
    //создать новый виджет инвентаря
    void makeNewInventory();
    //показать главное меню из виджета инвентаря
    void showBackMainMenu();
    //очистить таблицу с инвентарём в базе данных
    void clearInventoryInDatabase();

public slots:
    //изменилось количество символов типа type в строке row, столбце column, новое количество - newAmount
    void itemAmountChanged(int row, int column, ItemType type, int newAmount);

signals:
    //кидает сигнал на InventoryWidget с готовой картинкой для нужного типа
    void itemAmountChangedPixmapSignal(int row, int column, const QPixmap &pic, int newAmount);
};

#endif // APPLICATION_H
