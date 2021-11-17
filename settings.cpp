#include "settings.h"
#include "ui_settings.h"
#include <QColorDialog>

Settings::Settings(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    setAutoFillBackground(true);
    ui->spinBox->setValue(9);
}

Settings::~Settings()
{
    delete ui;
}

void  Settings::initialSetting(QColor c, QString fontFamily, int size)
{
    ui->pb_changeColor->setStyleSheet(QString("* {background-color:rgba(%1,%2,%3,%4);}").arg(c.red()).arg(
                                                                            c.green()).arg(c.blue()).arg(c.alpha()));
    QFont  f;
    f.setFamily(fontFamily);
    ui->fontComboBox->setCurrentFont(f);

    ui->spinBox->setValue(size);
}

void  Settings::on_pb_changeColor_clicked()
{
    color = QColorDialog::getColor(Qt::black, this);

    ui->pb_changeColor->setStyleSheet(QString("* {background-color:rgba(%1,%2,%3,%4);}").arg(color.red()).arg(
                                                                            color.green()).arg(color.blue()).arg(color.alpha()));

    emit  changingTextColor(color);
}

void  Settings::on_spinBox_valueChanged(int arg1)
{
    emit  changingFontSize(arg1);
}

void  Settings::on_fontComboBox_currentFontChanged(const QFont &f)
{
    emit  changingTextFont(f);
}
