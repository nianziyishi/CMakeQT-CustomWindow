#include "GUIMain.h"
#include <QtWidgets/QApplication>
#include "Demo/QWindowDemo.h"

int GUIMain(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWindowDemo w;
    w.show();
    return a.exec();
}
