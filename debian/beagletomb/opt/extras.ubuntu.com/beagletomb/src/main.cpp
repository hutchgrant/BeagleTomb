#include <QtGui/QApplication>
#include "beaglemain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BeagleMain w;
    w.show();

    return a.exec();
}
