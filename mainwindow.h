#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    // QWidget interface

protected:
    void  mousePressEvent(QMouseEvent *event);

    void  mouseMoveEvent(QMouseEvent *event);

private slots:
    void  on_pb_close_clicked();

    void  on_pb_minimize_clicked();

    void  on_tb_Setting_clicked();

private:
    Ui::MainWindow *ui;
    QPoint          dragPosition;
    Settings       *_settingPage;
};

#endif // MAINWINDOW_H
