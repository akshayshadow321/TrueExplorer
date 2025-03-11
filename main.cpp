#include "trueexplorer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrueExplorer w;
    w.show();
    return a.exec();
}
