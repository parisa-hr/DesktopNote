#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    setAutoFillBackground(true);

    _settingPage = new Settings(this);
    _settingPage->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void  MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void  MainWindow::on_pb_close_clicked()
{
    close();
}

void  MainWindow::on_pb_minimize_clicked()
{
    showMinimized();
}

void  MainWindow::on_tb_Setting_clicked()
{
    _settingPage->show();
}

void  MainWindow::on_tb_bold_clicked(bool checked)
{
    checked ? ui->textEdit->setFontWeight(QFont::Bold)
    : ui->textEdit->setFontWeight(QFont::Normal);
}

void  MainWindow::on_tb_underline_clicked(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void  MainWindow::on_tb_StrikeOut_clicked(bool checked)
{
    _font = ui->textEdit->font();

    if (checked)
    {
        _font.setStrikeOut(true);

        ui->textEdit->setCurrentFont(_font);
    }
}

void  MainWindow::on_tb_align_left_clicked(bool checked)
{
    ui->tb_align_right->setChecked(false);
    ui->tb_align_center->setChecked(false);

    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignLeft);
    }
}

void  MainWindow::on_tb_align_center_clicked(bool checked)
{
    ui->tb_align_left->setChecked(false);
    ui->tb_align_right->setChecked(false);

    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignCenter);
    }
}

void  MainWindow::on_tb_align_right_clicked(bool checked)
{
    ui->tb_align_center->setChecked(false);
    ui->tb_align_left->setChecked(false);

    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignRight);
    }
}
