#include "configuredialog.h"
#include "ui_configuredialog.h"

extern QString path;
extern double dpiPercent;

ConfigureDialog::ConfigureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureDialog)
{
    ui->setupUi(this);
    QImage image(":/pictures/pictures/sigma.png");
    ui -> labelLogo -> setPixmap( QPixmap::fromImage(image.scaled(120,120,Qt::KeepAspectRatio,Qt::FastTransformation)) );
    ui -> buttonConfigure -> setIcon( QIcon(":/pictures/pictures/configure.png") );
    ui -> buttonConfigure -> setIconSize( QSize(6000/dpiPercent,6000/dpiPercent) );
    ui -> buttonConfigure -> setFont( QFont("Calibri Light", 1200/dpiPercent, QFont::Bold ,false));
    ui -> plainTextEdit -> setFont( QFont("Calibri Light", 1200/dpiPercent, QFont::Light ,false) );
}

ConfigureDialog::~ConfigureDialog()
{
    delete ui;
}

void ConfigureDialog::on_buttonConfigure_clicked()
{
    ConfigureDialog::accept();
}
