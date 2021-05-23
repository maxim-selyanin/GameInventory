#include "mainmenu.h"
#include <QPushButton>
#include <QGridLayout>
#include <QCloseEvent>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *newGameBtn = new QPushButton("New Game", this);
    QPushButton *exitBtn = new QPushButton("Exit", this);

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(newGameBtn, 0, 0);
    layout->addWidget(exitBtn, 1, 0);

    this->setLayout(layout);

    connect(newGameBtn, &QPushButton::pressed, this, &MainMenu::newGame);
    connect(exitBtn, &QPushButton::pressed, this, &MainMenu::closed);
    connect(exitBtn, &QPushButton::pressed, this, &QWidget::close);
}

MainMenu::~MainMenu()
{
}

void MainMenu::closeEvent(QCloseEvent *event)
{
    emit closed();
    event->accept();
}

