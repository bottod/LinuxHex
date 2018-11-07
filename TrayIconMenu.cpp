#include "TrayIconMenu.h"

TrayIconMenu::TrayIconMenu(QWidget *parent) : QMenu(parent)
{
    setFixedWidth(212);
    initAction();
}

void TrayIconMenu::initAction()
{
    setAction = new QAction(QIcon(":/Source/image/set.png"),"设置",this);
    quitAction = new QAction(QIcon(":/Source/image/quit.png"), "退出", this);

    addAction(setAction);
    addSeparator();
    addAction(quitAction);
}
