#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int  main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication  a(argc, argv);
    MainWindow    w;

    w.setWindowIcon(QIcon(":/images/images/tack.svg"));
    w.setWindowTitle("Note");
    a.setApplicationName("Note");

    w.show();

    return a.exec();
}
