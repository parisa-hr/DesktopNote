#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui
{
class Settings;
}

class Settings: public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);

    ~Settings();

    void  initialSetting(QColor c, QString fontFamily, int size);

signals:
    void  changingTextColor(QColor color);

    void  changingTextFont(QFont font);

    void  changingFontSize(int size);

private slots:
    void  on_pb_changeColor_clicked();

    void  on_spinBox_valueChanged(int arg1);

    void  on_fontComboBox_currentFontChanged(const QFont &f);

private:
    Ui::Settings *ui;
    QColor        color = Qt::black;
};

#endif // SETTINGS_H
