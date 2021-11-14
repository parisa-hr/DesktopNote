#include "settings.h"
#include "ui_settings.h"

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
