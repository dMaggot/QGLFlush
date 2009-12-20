#include <QtGui/QApplication>
#include "qglflushwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGLFlushWindow w;
    w.show();
    return a.exec();
}
