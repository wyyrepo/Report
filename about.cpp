#include "about.h"
#include "ui_about.h"

extern QString path;
extern double dpiPercent;

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi( this );
    QImage pix( ":/pictures/pictures/sigma.png" );
    ui -> label -> setPixmap( QPixmap::fromImage(pix.scaled(130,130,Qt::KeepAspectRatio,Qt::FastTransformation)) );

    ui -> labelURL -> setText( "<a href=\"http://www.sigmasa.pl/\">Witryna firmy SIGMA S.A.</a>" );
    ui -> labelURL ->setTextFormat( Qt::RichText );
    ui -> labelURL ->setTextInteractionFlags( Qt::TextBrowserInteraction );
    ui -> labelURL ->setOpenExternalLinks( true );
    ui -> labelURL -> setFont( QFont("Calibri Light", 1200/dpiPercent, QFont::Light ,false) );

    ui -> textEdit -> setFont( QFont("Calibri Light", 1200/dpiPercent, QFont::Light ,false));
    ui -> textEdit -> insertHtml("<b>Raportowanie v1.0</b><br/><br/>"
                                 "Utworzono Paź 22 2015 09:49:14<br/><br/>"
                                 "Copyright © 1996-2015 SIGMA S.A. Wszelkie prawa zastrzeżone.<br/>");
}

about::~about()
{
    delete ui;
}

