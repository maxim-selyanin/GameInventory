#include "mainmenu.h"
#include <QPushButton>
#include <QGridLayout>
#include <QCloseEvent>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    //кнопочки
    QPushButton *newGameBtn = new QPushButton("New Game", this);
    QPushButton *exitBtn = new QPushButton("Exit", this);

    QGridLayout *layout = new QGridLayout(this);

    //кидаем кнопочки на сетчатый лейаут
    layout->addWidget(newGameBtn, 0, 0);
    layout->addWidget(exitBtn, 0, 1);

    this->setLayout(layout);

    //коннектим сигналы
    connect(newGameBtn, &QPushButton::pressed, this, &MainMenu::newGame);
    connect(exitBtn, &QPushButton::pressed, this, &MainMenu::exitSignal);
    connect(exitBtn, &QPushButton::pressed, this, &QWidget::close);
}

MainMenu::~MainMenu()
{
}
