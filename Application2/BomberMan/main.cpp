#include "BomberMan.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BomberMan w;
    w.show();
    return a.exec();
}
