#include "inventorywidget.h"
#include <QGridLayout>
#include "droptablewidget.h"
#include "draglabel.h"
#include <QPushButton>
#include <QHeaderView>
#include <QScrollBar>
#include "inventoryitemdelegate.h"
#include <QPainter>
#include <QCloseEvent>
#include <QDebug>

//устанавливаем нужный размер для таблички с инвентарём
QSize getQTableWidgetSize(QTableWidget *t) {
   int w = t->verticalHeader()->width() + 4;
   for (int i = 0; i < t->columnCount(); i++){
       w += t->columnWidth(i);
   }

   int h = t->horizontalHeader()->height() + 4;
   for (int i = 0; i < t->rowCount(); i++){
       h += t->rowHeight(i);
   }

   return QSize(w, h);
}
void redoGeometry(QWidget *w) {
   const bool vis = w->isVisible();
   const QPoint pos = w->pos();
   w->hide();
   w->show();
   w->setVisible(vis);
   if (vis && !pos.isNull()) {
       w->move(pos);
   }
}


//создаём табличку с инвентарём
AppleDropTableWidget *InventoryWidget::createTableWidget()
{
    tableWidget = new AppleDropTableWidget(rows, columns, this);

    //ставим делегата
    tableWidget->setItemDelegate(new InventoryItemDelegate(tableWidget));

    //ставим скроллы под размер наполнения и убираем их
    QHeaderView *horizontalHeaderView = tableWidget->horizontalHeader();
    horizontalHeaderView->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeaderView->hide();

    QHeaderView *verticalHeaderView = tableWidget->verticalHeader();
    verticalHeaderView->setSectionResizeMode(QHeaderView::ResizeToContents);
    verticalHeaderView->hide();

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            QTableWidgetItem *i = new QTableWidgetItem;
            QPixmap pic{defaultPicPath};
            i->setData(Qt::DecorationRole, pic);
            tableWidget->setItem(row, column, i);
        }
    }
    return tableWidget;
}

//создаём виджет с яблочком
DragAppleLabel *InventoryWidget::createAppleWidget()
{
    DragAppleLabel *imageLabel = new DragAppleLabel(this);
    QPixmap apple{bigApplePath};
    imageLabel->setPixmap(apple);
    imageLabel->setFixedSize(apple.size());
    return imageLabel;
}

QPushButton *InventoryWidget::createMainMenuButton()
{
    return new QPushButton("Main Menu", this);
}

QPixmap InventoryWidget::getPixmap(const QPixmap &pixmap, int amount)
{
    QPixmap result(pixmap);
    QPainter painter(&result);

    QFont f;
    f.setPointSize(textSize);
    f.setBold(true);

    QPoint textPoint(result.width() - textHorizontalOffset, result.height() - textVerticalOffset);

    //рисуем нужно число на пиксмапе
    painter.drawText(textPoint, QString().setNum(amount));

    return result;
}

InventoryWidget::InventoryWidget(int rows_, int columns_, QWidget *parent)
    : QWidget(parent)
    , rows(rows_)
    , columns(columns_)
{
    QGridLayout *layout = new QGridLayout(this);

    //создаём три нужных виджета
    auto table = createTableWidget();
    auto apple = createAppleWidget();
    auto mainMenuButton = createMainMenuButton();



    //ставит нормальный фиксированный размер для таблицы
    redoGeometry(this);
    table->setMaximumSize(getQTableWidgetSize(table));
    table->setMinimumSize(table->maximumSize());



    //заливаем виджеты на сетчатый лейаут
    layout->addWidget(mainMenuButton, 0, 0, 1, 2);
    layout->addWidget(table, 1, 0);
    layout->addWidget(apple, 1, 1);

    this->setLayout(layout);

    //коннектим сигналы-слоты
    connect(mainMenuButton, &QPushButton::pressed, this, &InventoryWidget::showMainMenu);
    connect(table, &AppleDropTableWidget::itemAddedOn, this, &InventoryWidget::itemAddedOn);
    connect(table, &AppleDropTableWidget::itemDeletedOn, this, &InventoryWidget::itemDeletedOn);
    connect(table, &AppleDropTableWidget::moveItemsFrom, this, &InventoryWidget::moveItemsFrom);
    connect(this, &InventoryWidget::playSound, table, &AppleDropTableWidget::playSound);
}

InventoryWidget::~InventoryWidget()
{
    //
}

void InventoryWidget::changedAmountOn(int row, int column, const QPixmap &pic, int newAmount)
{
    //ставим нужную картинку
    QTableWidgetItem *myItem = tableWidget->item(row, column);
    if (newAmount > 0) {
        myItem->setData(Qt::DecorationRole, getPixmap(pic, newAmount));
    } else if (newAmount == 0) {
        myItem->setData(Qt::DecorationRole, QPixmap(defaultPicPath));
    }
}
