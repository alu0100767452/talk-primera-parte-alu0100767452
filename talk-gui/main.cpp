#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("ULL Sistemas Operativos Avanzados");
    QApplication::setOrganizationDomain("ull.es");
    QApplication::setApplicationName("Talk GUI");

    MainWindow w;
    w.show();

    return a.exec();
}
