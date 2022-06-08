#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCharFormat>
#include <QVariant>
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
    void      mousePressEvent(QMouseEvent *event);

    void      mouseMoveEvent(QMouseEvent *event);

private slots:
    void      on_pb_close_clicked();

    void      on_pb_minimize_clicked();

    void      on_tb_Setting_clicked();

    void      on_tb_bold_clicked(bool checked);

    void      on_tb_underline_clicked(bool underline);

    void      on_tb_StrikeOut_clicked();

    void      on_tb_align_left_clicked(bool checked);

    void      on_tb_align_center_clicked(bool checked);

    void      on_tb_align_right_clicked(bool checked);

    void      on_tb_save_clicked();

    void      on_tb_load_clicked();

    void      setSettings(const QString &str, const QVariant &value);

    QVariant  getSettings(const QString &str);

    void      on_textEdit_cursorPositionChanged();

    void      on_textEdit_selectionChanged();

private:
    Ui::MainWindow *ui;
    QPoint          dragPosition;
    Settings       *_settingPage;
    QFont           _font;
    QString         currentFile;
};

#endif // MAINWINDOW_H
