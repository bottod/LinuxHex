#include "MainWidget.h"
#include <QApplication>

#include "InfoFrame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Debug Tool");
    app.setOrganizationName("Debug Tool");
    app.setOrganizationDomain("github.com/bottod");
    app.setWindowIcon(QIcon(":/Source/image/app.png"));


    MainWidget w;
    w.show();

    return app.exec();
}
