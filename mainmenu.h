#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

///
/// \brief виджет главного меню
///
class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu() override;

signals:
    //сигнал о начале новой игры
    void newGame();
    //сигнал о закрытии приложения
    void exitSignal();
};
#endif // MAINMENU_H
