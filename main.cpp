#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int  main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication  a(argc, argv);

    a.setApplicationName("MyNotes");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("Parisa_hr");

    MainWindow  w;

    w.setWindowIcon(QIcon(":/images/images/tack.svg"));
    w.setWindowTitle("Note");

    w.show();

    return a.exec();
}
