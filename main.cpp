#include "trueexplorer.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon appIcon(":/images/images/Logo.png");  // Make sure the icon is in the resources
    a.setWindowIcon(appIcon);

    TrueExplorer w;
    w.show();
    return a.exec();
}
