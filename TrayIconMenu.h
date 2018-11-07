#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QMenu>
#include <QFile>

class TrayIconMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TrayIconMenu(QWidget *parent = nullptr);

private:
    void initAction();

public:
    QAction *quitAction;
    QAction *setAction;
};

#endif // TRAYICONMENU_H
