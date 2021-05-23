#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu() override;

    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void newGame();
    void closed();
};
#endif // MAINMENU_H
