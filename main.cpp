#include "MainWidget.h"
#include <QApplication>

//#include "OptionDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("LinuxHex");
    app.setOrganizationName("LinuxHex");
    app.setWindowIcon(QIcon(":/Source/image/app.png"));

    MainWidget w;
    w.show();

    return app.exec();
}