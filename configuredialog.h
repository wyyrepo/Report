#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include <QImage>

namespace Ui {
class ConfigureDialog;
}

class ConfigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureDialog(QWidget *parent = 0);
    ~ConfigureDialog();

private slots:
    void on_buttonConfigure_clicked();

private:
    Ui::ConfigureDialog *ui;
};

#endif // CONFIGUREDIALOG_H
