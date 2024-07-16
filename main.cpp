
#include "mainapp_wnd.h"
#include <QApplication>
#include <QThread>
#include <QMetaMethod>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int b = 1;
    mainApp_Wnd w;
    w.show();

    return a.exec();
}
