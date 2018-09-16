#include "mainwindow.h"
#include "simpleqtcryptor.h"
#include <QApplication>
#include <QProgressBar>
#include <QSplashScreen>
#include <QDir>
#include <QResource>

#define LICENSE_KEY "REPORT_LICENSE^(Ver[1.0])"

QString getHDDSerialNum();
QString getLicense();

QDir dir;
QString path = dir.absolutePath();
QSplashScreen *splash;
QString error;
double dpiPercent;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int dpiX = qApp->desktop()->logicalDpiX();
    dpiPercent = ((100*dpiX)/96);

    QResource::registerResource("pictures.rcc");

//    if( getHDDSerialNum() != getLicense() )
//    {
//        QWidget msg;
//        msg.setWindowIcon( QIcon( ":/pictures/pictures/logo.png" ) );
//        QMessageBox::critical(&msg,"Błąd Licencji", "Nieprawidłowa licencja. Proszę skontaktować się z naszym oddziałem.\n" + error);
//        return 0;
//    }

    qApp -> processEvents();
    splash = new QSplashScreen( QPixmap(":/pictures/pictures/splashscreen.png") );
    splash -> setWindowFlags( Qt::WindowStaysOnTopHint | Qt::SplashScreen );
    splash -> setFont( QFont("Sans", 1500/dpiPercent) );
    splash -> show();

    splash -> showMessage( QObject::tr("Setting up the application..."),Qt::AlignBottom | Qt::AlignRight, Qt::white );
    MainWindow w;
    w.setWindowTitle( "Raportowanie" );
    w.setWindowIcon( QIcon( ":/pictures/pictures/logo.png" ) );
    splash -> showMessage( QObject::tr("Please wait. Loading CSV files - PART 1/2 ..."),Qt::AlignBottom | Qt::AlignRight, Qt::white );
    w.readCSV();

    w.show();
    splash -> finish( &w );
    delete splash;

    return a.exec();
}

QString getHDDSerialNum()
{
    QProcess serialNum;
    serialNum.start( "wmic csproduct get uuid" );

    if(serialNum.waitForFinished())
    {
        QStringList outputList = QString(serialNum.readAllStandardOutput()).split("\n");
        return outputList.at(1).trimmed();
    }
    else return QString( "Zbyt długi czas przetwarzania." );
}

QString getLicense()
{
    QFile lic( "license.dat" );
    if( !lic.open(QIODevice::ReadOnly) )
    {
        error = "Nie znaleziono pliku ""license.dat"".";
        return error;
    }
    QDataStream in( &lic );
    QByteArray serNum;
    in >> serNum;
    lic.close();

    QSharedPointer<SimpleQtCryptor::Key> u(new SimpleQtCryptor::Key( QString(LICENSE_KEY)) );
    SimpleQtCryptor::DecryptorWizard dw(u);
    SimpleQtCryptor::Decryptor d(u, SimpleQtCryptor::SERPENT_32, SimpleQtCryptor::ModeCFB);
    QByteArray plain;
    d.decrypt(serNum,plain,true);
    QString sPlain(plain);

    if( sPlain.isEmpty() )
    {
        error = "Nieprawidłowa zawartość pliku ""license.dat"".";
        return error;
    }

    return sPlain;
}

