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
}

Settings::~Settings()
{
    delete ui;
}

void  Settings::on_pb_changeColor_clicked()
{
    QColor  color = QColorDialog::getColor(Qt::black, this);

    ui->pb_changeColor->setStyleSheet(QString("* {background-color:rgba(%1,%2,%3,%4);}").arg(color.red()).arg(
                                                                            color.green()).arg(color.blue()).arg(color.alpha()));
}
