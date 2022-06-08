#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

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

    connect(_settingPage, &Settings::changingTextColor, this, [this](QColor color)
    {
        ui->textEdit->setTextColor(color);
    });
    connect(_settingPage, &Settings::changingTextFont, this, [this](QFont font)
    {
        ui->textEdit->setFontFamily(font.family());
        qDebug() << "fontFamily = " << ui->textEdit->fontFamily();
    });
    connect(_settingPage, &Settings::changingFontSize, this, [this](int w)
    {
        ui->textEdit->setFontPointSize(w);
    });


    auto  _windowPos = getSettings("windowPose").toPoint();
    move(_windowPos);

    auto  _fontColor = getSettings("fontColor").toString();
    ui->textEdit->setTextColor(_fontColor);

    auto  _fontFamily = getSettings("fontFamily").toString();
    ui->textEdit->setFontFamily(_fontFamily);

    auto  _fontSize = getSettings("fontSize").toInt();
    ui->textEdit->setFontPointSize(_fontSize);


    _settingPage->initialSetting(_fontColor, _fontFamily, _fontSize);
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

    setSettings("windowPose", pos());
    setSettings("fontColor", ui->textEdit->textColor());
    setSettings("fontFamily", ui->textEdit->currentFont().family());
    setSettings("fontSize", ui->textEdit->fontPointSize());
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

void  MainWindow::on_tb_StrikeOut_clicked()
{
    QTextCursor  cursor = ui->textEdit->textCursor();

    _font = ui->textEdit->currentFont();

    if (!cursor.selection().isEmpty())
    {
        _font.setStrikeOut(true);

        ui->textEdit->setCurrentFont(_font);
    }
    else
    {
        _font.setStrikeOut(false);

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

void  MainWindow::on_tb_save_clicked()
{
    QString  fileName;

    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty())
    {
        fileName    = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    }
    else
    {
        fileName = currentFile;
    }

    QFile  file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());

        return;
    }

    setWindowTitle(fileName);
    QTextStream  out(&file);
    QString      text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void  MainWindow::on_tb_load_clicked()
{
    QString  fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile    file(fileName);

    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());

        return;
    }

    setWindowTitle(fileName);
    QTextStream  in(&file);
    QString      text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void  MainWindow::setSettings(const QString &str, const QVariant &value)
{
    QSettings  _setting("Parisa_hr", "MyNotes");

    _setting.setValue(str, value);
}

QVariant  MainWindow::getSettings(const QString &str)
{
    QSettings  _setting("Parisa_hr", "MyNotes");
    QVariant   v;

    v = _setting.value(str);

    return v;
}

void  MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor  cursor = ui->textEdit->textCursor();

    if (!cursor.selection().isEmpty())
    {
        return;
    }

    _font.setStrikeOut(false);
    ui->textEdit->setCurrentFont(_font);
}

void  MainWindow::on_textEdit_selectionChanged()
{
    QTextCursor  cursor = ui->textEdit->textCursor();
    auto         text   = cursor.selectedText();

    qDebug() << "i am hererrr" << text;
}
