#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 *  Copyright (C) 2015,2016 Rafał Strawiński, Bartłomiej Pokrzywa
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

extern QString path;
extern QSplashScreen *splash;
extern double dpiPercent;
#define DEVICE_RAPORT_TYPE_NUM 4
#define DEBUG_ACTIVE 0
#define WorkLogCSV "LOG_PRACY0.csv"
#define StandLogCSV "LOG_GOTOWOŚĆ0.csv"
#define WorkTimeCSV "LOG_CZASU_PRACY0.csv"
#define CrashTimeCSV "LOG_CZASU_AWARII0.csv"
#define CrashCSV "LOG_AWARII0.csv"
#define DeviceNamesCSV "LOG_DEVICE.csv"
#define CrashNamesCSV "LOG_CRASH.csv"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);

    progressBar = new QProgressBar(this);
    statusLabel = new QLabel(this);
    statusLabel -> setFont( QFont("Sagoe", 9, QFont::Light ,false) );
    progressBar -> setStyleSheet( "QProgressBar {color:white; background-color: white;}");
    progressBar -> setFont( QFont("Sagoe", 9, QFont::Light ,false) );
    ui -> statusBar -> addPermanentWidget (statusLabel,1);
    ui -> statusBar -> addPermanentWidget( progressBar,1);

    ui -> comboBoxReport -> addItem( QIcon(":/pictures/pictures/logo.png"),"Wybierz raport" );
    ui -> comboBoxReport -> addItem( QIcon(":/pictures/pictures/accident_raport.png"),"Raport awarii" );
    ui -> comboBoxReport -> addItem( QIcon(":/pictures/pictures/machine_raport.png"),"Raport dla urządzeń" );
    ui -> comboBoxReport -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Bold ,false));

    ui -> dateTimeEnd -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false) );
    ui -> dateTimeEnd -> calendarWidget() -> setMinimumDate( QDate::currentDate() );
    ui -> dateTimeEnd -> setDate( QDate::currentDate() );
    connect( ui->dateTimeEnd->calendarWidget(), SIGNAL(clicked(QDate)), this, SLOT(on_CreateTimeDialog(QDate)) );

    ui -> dateTimeStart -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false));
    ui -> dateTimeStart -> calendarWidget() -> setMinimumDate( QDate::currentDate() );
    ui -> dateTimeStart -> setDate ( QDate::currentDate() );
    connect( ui->dateTimeStart->calendarWidget(), SIGNAL(clicked(QDate)), this, SLOT(on_CreateTimeDialog(QDate)) );

    proxyModel = new QSortFilterProxyModel (this);
    ui -> lineEdit -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false) );

    /* disable during start */
    ui -> labelArrow -> setEnabled(false);
    ui -> comboBoxDevice -> setEnabled(false);
    ui -> comboBoxReportType -> setEnabled(false);

    QTimer::singleShot(1000, this ,SLOT(on_ConfigureDialog()));

    exportPath = readExportPath();
}

MainWindow::~MainWindow()
{
    if( csvModel != nullptr ) delete csvModel;
    delete modelWorkLog;
    delete modelStandLog;
    delete modelCrashTime;
    delete modelWorkTime;
    delete modelCrash;
    delete ui;
}

/*
 * ---- COMBOBOXES functions ----

 * fillReportTypeCombobox() - set QStandardItemModel on comboBoxReportType (devices reports) and create reportStateVector (represent actual report state).
 * SLOT on_ReportTypeCheck() - fill reportStateVector depending on the selected checboxes (0 or 1).
 * SLOT on_ItemReportTypeClicked() - set/unset checkboxes when comboBoxReportType label is clicked.
 * fillDeviceCombobox() -
   - read devices from CSV file,
   - set QStandardItemModel on comboBoxDevice (devices),
   - create deviceStateVector (represent actual devices state),
   - create deviceNameVector (vector of devices names)

 * SLOT on_DeviceCheck() - fill reportStateVector depending on the selected checboxes (0 or 1).
 * SLOT on_ItemDeviceClicked() - set/unset checkboxes when comboBoxDevice label is clicked.
 * SLOT on_comboBoxReport_activated() - activates the selected report from comboBoxDevice
 * ClearComboboxes() - clear comboBoxReportType and comboBoxDevice

*/

void MainWindow::fillReportTypeCombobox()
{
     static bool isConnectSet = false;

     reportStateVector.clear();
     if ( itemReportModel != nullptr )
         delete itemReportModel;

     reportStateVector.reserve( DEVICE_RAPORT_TYPE_NUM );
     reportStateVector.resize ( DEVICE_RAPORT_TYPE_NUM , std::move(0) );

     itemReportModel = new QStandardItemModel( DEVICE_RAPORT_TYPE_NUM + 2, 1, this ); /* rows, col */

     for ( int i = 0; i < (DEVICE_RAPORT_TYPE_NUM + 2) ; ++i )
     {
            QStandardItem* item = new QStandardItem;
            item -> setText( typeList[i] );
            item -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false) );
            if(!i) item -> setIcon( QIcon(":/pictures/pictures/machine_type.png") );
            if(i) item -> setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
            if(i) item -> setData( Qt::Unchecked, Qt::CheckStateRole );
            itemReportModel -> setItem( i, 0, item );
     }

     connect(itemReportModel, SIGNAL(dataChanged ( const QModelIndex&, const QModelIndex&)), this, SLOT(on_ReportTypeCheck(const QModelIndex&, const QModelIndex&)));
     ui -> comboBoxReportType -> setModel( itemReportModel );
     ui -> comboBoxReportType -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Bold ,false) );
     ui -> comboBoxReportType -> setIconSize( QSize(50,50) );
     if (!isConnectSet)
     {
         connect( ui -> comboBoxReportType -> view(), SIGNAL(pressed(QModelIndex)), this, SLOT(on_ItemReportTypeClicked(QModelIndex)));
         isConnectSet = true;
     }
}

void MainWindow::on_ReportTypeCheck(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
  Q_UNUSED(bottomRight);
  QStandardItem* item = itemReportModel -> itemFromIndex( topLeft );
  static bool selectAll = false;

  if ( topLeft.row() == 1 )
  {
        int i{2};
        if ( item->checkState() == Qt::Checked )
        {
            for ( auto & elem : reportStateVector)
            {
                elem = 1;
                itemReportModel -> item( i, 0 ) -> setCheckState( Qt::Checked );
                i++;
            }
        }
        if ( item->checkState() == Qt::Unchecked && !selectAll)
        {
            for ( auto & elem : reportStateVector )
            {
                elem = 0;
                itemReportModel -> item( i, 0 ) -> setCheckState( Qt::Unchecked);
                i++;
            }
        }
  }

  else
  {
      selectAll = false;
      if( item->checkState() == Qt::Unchecked )
      {
        reportStateVector[ topLeft.row() - 2 ] = 0;
        QStandardItem * allItem = itemReportModel -> item(1,0);
        if( allItem->checkState() == Qt::Checked)
            {
                selectAll = true;
                allItem->setCheckState(Qt::Unchecked);
            }
      }
      else if( item->checkState() == Qt::Checked )
      {
        reportStateVector[ topLeft.row() - 2 ] = 1;
      }
  }

  #if (DEBUG_ACTIVE==1)
      for( uint i = 0 ; i < reportStateVector.size() ; ++i)
          std::cout << reportStateVector[i] << std::endl;
      std::cout << std::endl;
  #endif
}

void MainWindow::on_ItemReportTypeClicked(QModelIndex index)
{
     QStandardItem* item = itemReportModel -> itemFromIndex( index );
     if( index.row() == 0)
         return;
     if( item->checkState() == Qt::Unchecked )
        item->setCheckState( Qt::Checked);
     else if( item->checkState() == Qt::Checked )
        item->setCheckState( Qt::Unchecked);
}

void MainWindow::fillDeviceCombobox()
{
    static bool isConnectSet = false;

    deviceNameVector.clear();
    deviceStateVector.clear();
    if ( itemDeviceModel != nullptr )
        delete itemDeviceModel;

    csvModel = new QxtCsvModel( csvPath + "/" + QString(DeviceNamesCSV), this, false, ';' );
    itemDeviceModel = new QStandardItemModel( (csvModel->rowCount()+2), 0 , this ); /* rows, col */
    deviceNameVector.reserve( csvModel->rowCount() );
    deviceStateVector.resize( csvModel -> rowCount(), std::move(0) );

    /* fill combobox with devices */
    QModelIndex deviceIDX;
    QString deviceName;
    for ( int i = 0; i < (csvModel->rowCount()+2) ; ++i )
    {
        QStandardItem* item = new QStandardItem;

        if( i ){
            if( i == 1)
                item -> setText( "Zaznacz wszystko" );
            else{
                deviceIDX = csvModel->index( (i-2), 1 );
                deviceName = csvModel->data(deviceIDX).toString();
                item -> setText( deviceName );
                deviceNameVector.push_back( std::move(deviceName) );
            }
            item -> setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
            item -> setData( Qt::Unchecked, Qt::CheckStateRole );}
        else if ( !i )
        {
            item -> setText( "Urządzenie" );
            item -> setIcon( QIcon(":/pictures/pictures/machine.png") );
        }
        item -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false));
        itemDeviceModel -> setItem( i, 0, item );
    }

    connect( itemDeviceModel, SIGNAL( dataChanged(const QModelIndex&, const QModelIndex& )), this, SLOT( on_DeviceCheck(const QModelIndex&, const QModelIndex& )) );
    ui -> comboBoxDevice -> setModel( itemDeviceModel );
    ui -> comboBoxDevice -> setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Bold ,false) );
    ui -> comboBoxDevice -> setIconSize( QSize(50,50) );
    if( !isConnectSet )
    {
        connect(ui->comboBoxDevice -> view(), SIGNAL(pressed(QModelIndex)), this, SLOT(on_ItemDeviceClicked(QModelIndex)));
        isConnectSet = true;
    }

}

void MainWindow::on_DeviceCheck(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
  Q_UNUSED(bottomRight);
  QStandardItem *item = itemDeviceModel -> itemFromIndex( topLeft );
  static bool selectAll = false;

  if ( topLeft.row() == 1 )
  {
        int i{2};
        if ( item->checkState() == Qt::Checked )
        {
            for ( auto & elem : deviceStateVector)
            {
                elem = 1;
                itemDeviceModel -> item( i, 0 ) -> setCheckState( Qt::Checked );
                i++;
            }
        }
        if ( item->checkState() == Qt::Unchecked && !selectAll )
        {
            for ( auto & elem : deviceStateVector )
            {
                elem = 0;
                itemDeviceModel -> item( i, 0 ) -> setCheckState( Qt::Unchecked);
                i++;
            }
        }
  }

  else
  {
      selectAll = false;
      if( item->checkState() == Qt::Unchecked  )
      {
            deviceStateVector[ topLeft.row() - 2 ] = 0;
            QStandardItem * allItem = itemDeviceModel -> item(1,0);
            if( allItem->checkState() == Qt::Checked)
                {
                    selectAll = true;
                    allItem->setCheckState(Qt::Unchecked);
                }
      }
      else if( item->checkState() == Qt::Checked  )
            deviceStateVector[ topLeft.row() - 2 ] = 1;
  }

  #if (DEBUG_ACTIVE==1)
      for( uint i = 0 ; i < deviceStateVector.size() ; ++i)
          std::cout << deviceStateVector[i] << std::endl;
      std::cout << std::endl;
  #endif
}

void MainWindow::on_ItemDeviceClicked(QModelIndex index)
{
     QStandardItem* item = itemDeviceModel -> itemFromIndex( index );
     if( index.row() == 0)
         return;
     if( item->checkState() == Qt::Unchecked )
        item->setCheckState( Qt::Checked);
     else if( item->checkState() == Qt::Checked )
        item->setCheckState( Qt::Unchecked);
}

void MainWindow::fillCrashes()
{
    delete csvModel;
    csvModel = new QxtCsvModel( csvPath + "/" + QString(CrashNamesCSV), this, false, ';');
    crashNameVector.clear();
    crashNameVector.reserve( csvModel->rowCount() );
    QString crashName;

    for ( int i = 0; i < csvModel->rowCount() ; ++i )
    {
        crashName = csvModel -> data( csvModel->index( i, 1 ) ).toString();
        crashNameVector.push_back( std::move(crashName) );
    }

    #if (DEBUG_ACTIVE==1)
        for( auto & elem : crashNameVector)
            qDebug() << elem << endl;
        qDebug() << endl;
    #endif

    delete csvModel;
    csvModel = nullptr;
}

void MainWindow::on_comboBoxReport_activated(int index)
{
    progressBar -> setValue(0);

    if ( index == 0 )
    {
        statusLabel -> setText( "" );
        clearComboboxes();
    }
    if ( index == 1 )
    {
        statusLabel -> setText( "<font color='white'> Raport awarii</font>" );
        clearComboboxes();
    }
    else if ( index == 2 )
    {
        statusLabel -> setText( "<font color='white'> Raport urządzeń</font>" );
        ui -> labelArrow -> setEnabled( true );
        ui -> comboBoxDevice -> setEnabled( true );
        ui -> comboBoxReportType -> setEnabled( true );
    }

}

void MainWindow::clearComboboxes()
{
    ui->labelArrow->setEnabled( false );
    ui -> comboBoxDevice -> setEnabled( false );
    ui -> comboBoxReportType -> setEnabled( false );
    itemReportModel -> item( 1, 0 ) -> setCheckState( Qt::Checked );
    itemReportModel -> item( 1, 0 ) -> setCheckState( Qt::Unchecked );
    itemDeviceModel -> item( 1, 0 ) -> setCheckState( Qt::Checked );
    itemDeviceModel -> item( 1, 0 ) -> setCheckState( Qt::Unchecked );
}

/*
 * ---- OTHER functions ----
 * SLOT on_CreateTimeDialog() - create time dialog after date clicked
 * SLOT on_ConfigureDialog() - crate configure dialog during first run
 * SLOT on_lineEdit_textChanged() - filtering table according to the text in QLineEdit
*/

void MainWindow::on_CreateTimeDialog(QDate date)
{
    Q_UNUSED( date );

    bool isStart{};
    if( qobject_cast<QCalendarWidget *>(sender()) == ui->dateTimeStart->calendarWidget() )
        isStart = true;
    else if(qobject_cast<QCalendarWidget *>(sender()) == ui->dateTimeEnd->calendarWidget() )
        isStart = false;

    if ( ui -> dateTimeEnd -> dateTime().toString("yyyy-MM-dd") != "7000-01-01" )
    {
        if( (ui -> dateTimeStart -> dateTime() > QDateTime::currentDateTime() ||
             ui -> dateTimeEnd -> dateTime()   > QDateTime::currentDateTime()) )
        {
            QMessageBox::information( this, "Informacja" , "Data rozpoczęcia lub zakończenia przekracza aktualną datę." );
            if( isStart ) ui -> dateTimeStart -> setDateTime( QDateTime::currentDateTime() );
            else ui -> dateTimeEnd -> setDateTime( QDateTime::currentDateTime() );
            return;
        }
    }

    /* create QDialog to set the time */
    QDialog TimeDialog;
    TimeDialog.setStyleSheet( "QDialog {background-color: white;}"
                              "QLabel {background-color: transparent;}"
                              "QLineEdit {background-color: white; border: 3px solid gray; border-radius: 5px; padding: 2px;}" );
    TimeDialog.setFixedSize( 200,150 );
    TimeDialog.setWindowIcon( QIcon(":/pictures/pictures/time.png") );
    TimeDialog.setWindowTitle( "Podaj godzinę" );
    TimeDialog.setWindowFlags( (TimeDialog.windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowContextHelpButtonHint );

    /* create QLineEdit to write the time */
    QTimeEdit TimeLineEdit;
    TimeLineEdit.setDisplayFormat( "hh" );
    TimeLineEdit.setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false) );

    TimeLineEdit.setAlignment( Qt::AlignCenter );
    TimeLineEdit.setFixedHeight( 30 );

    /* create QPushButton to confirm the time */
    QPushButton ConfirmButton;
    ConfirmButton.setText( "Zatwierdź" );
    ConfirmButton.setFixedHeight( 50 );
    ConfirmButton.setFont( QFont("Calibri Light", 1500/dpiPercent, QFont::Bold ,false));
    ConfirmButton.setStyleSheet(
                "QPushButton {"
                    "border: 2px solid #199909;"
                    "border-radius: 6px;"
                    "color: white;"
                    "background-color: #116a06;"
                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 0.67, "
                        "stop: 0 #22c70d, stop: 1 #116a06);"
                "}"
                "QPushButton:pressed {"
                    "border: 2px solid #333333;"
                    "background-color: #222222;"
                    "color: white;"
                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 0.67, "
                        "stop: 0 #444444, stop: 1 #222222);"
                "}");
    connect( &ConfirmButton, SIGNAL(released()), &TimeDialog, SLOT(accept()) );

    /* create QGridLayout for TimeDialog */
    QGridLayout layout;
    layout.addWidget( &TimeLineEdit, 1, 0 );
    layout.addWidget( &ConfirmButton, 2, 0 );
    TimeDialog.setLayout( &layout );

    if ( TimeDialog.exec() == QDialog::Accepted)
    {
        if(isStart) ui -> dateTimeStart -> setTime( TimeLineEdit.time() );
        else ui -> dateTimeEnd -> setTime( TimeLineEdit.time() );
    }
    else
    {
        if( ui -> dateTimeEnd -> date().toString("yyyy-MM-dd") == "7000-01-01" && TimeLineEdit.time().toString("hh") == "22" )
        {
            player -> setMedia( QUrl("qrc:/pictures/pictures/cobede.mp3") );
            player -> play();
        }
        QMessageBox::information( this, "Informacja" , "Godzina nie została wybrana." );
    }
}

void MainWindow::on_ConfigureDialog()
{
    if ( !csvPath.isEmpty() )
    {
        if ( !missingFiles.isEmpty() )
            QMessageBox::information( this, "Informacja" , "W ścieżce źródłowej brakuje plików, zawierających rejestry zdarzeń: "+missingFiles+"" );
        return;
    }
    else
    {        
        configureDialog = new ConfigureDialog(this);
        configureDialog -> setWindowFlags(((configureDialog->windowFlags()) & ~Qt::WindowContextHelpButtonHint) );
        if ( configureDialog -> exec() == QDialog::Accepted )
                on_action_setCSVPath_triggered();
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if( ui -> tableView -> model() == nullptr && ui -> lineEdit -> text() != "" )
    {
        ui -> lineEdit -> clear();
        QMessageBox::information( this, "Informacja" , "Brak raportu w tabeli." );
        return;
    }

    if(arg1 == "ls -l fsociety")
    {
        QDialog d;
        QGridLayout lay;
        QLabel l;
        QImage pix( ":/pictures/pictures/fs.jpg" );
        d.setWindowTitle( "fsociety" );
        d.setWindowIcon( QIcon( ":/pictures/pictures/fs.jpg") );
        l.setPixmap( QPixmap::fromImage(pix.scaled(300,300,Qt::KeepAspectRatio,Qt::FastTransformation)) );
        lay.addWidget( &l, 0, 0 );
        d.setLayout( &lay );
        player -> setMedia(QUrl("qrc:/pictures/pictures/beep.mp3"));
        player -> play();
        connect( player, SIGNAL(stateChanged(QMediaPlayer::State)), &d, SLOT(close()) );
        d.exec();
    }

    QRegExp regExp( arg1, Qt::CaseInsensitive, QRegExp::Wildcard );
    proxyModel -> setFilterRegExp( regExp );
}

/*
 * ---- CSV functions ----

 * readCSV() - read CSV files with logs in different threads
 * readCsvPath() - read from binary file path to CSV files
 * generateDeviceReport() - generete selected device report and display in QTableView.
 * countLog() - counts -1's from modelWorkLog or 0's from modelStandLog. Adds counts to reportMap.
 * crashLog() - counts 1's from modelCrashLog. Adds counts to crashMap. Display  in QTableView.
 * timeLog() - Adds difference in time to reportMap:
    - clearStaticArray() - clear array maxMin[] and minMin[]
    - different() - return difference beetwen max and min time

 * configureTable() - configure QTableView, set QSortFilterProxyModel on QTableView
 * displayDeviceReport() - display devices report from reportMap to QTableView
 * displayCrashReport() - display crashes report from crashMap to QTableView
 * isReportCorrect() - return true if report can be generated
 * on_buttonAccept_clicked() - execute selected report

*/

bool MainWindow::isMissingFiles()
{
    missingFiles = "";
    QString separator = ",\n";

    if( !QFile(csvPath + "/" + QString(WorkLogCSV)).exists() )
        missingFiles += QString(WorkLogCSV) + separator;

    if( !QFile(csvPath+"/" + QString(StandLogCSV)).exists() )
        missingFiles +=  QString(StandLogCSV) + separator;

    if( !QFile(csvPath+"/" + QString(WorkTimeCSV)).exists() )
        missingFiles +=  QString(WorkTimeCSV) + separator;

    if( !QFile(csvPath+"/" + QString(CrashTimeCSV)).exists() )
        missingFiles +=  QString(CrashTimeCSV) + separator;

    if( !QFile(csvPath+"/" + QString(CrashCSV)).exists() )
        missingFiles +=  QString(CrashCSV) + separator;

    if( !QFile(csvPath+"/" + QString(DeviceNamesCSV)).exists() )
        missingFiles +=  QString(DeviceNamesCSV) + separator;

    if( !QFile(csvPath+"/" + QString(CrashNamesCSV)).exists() )
        missingFiles +=  QString(CrashNamesCSV) + separator;

    missingFiles = missingFiles.left( missingFiles.size()-2 );

    if( !missingFiles.isEmpty() )
        return true;

    return false;
}

void MainWindow::readCSV(bool isSplash)
{
    #if (DEBUG_ACTIVE==1)
        std::clock_t start;
        double duration;
        start = std::clock();
    #endif

    delete modelWorkLog;
    modelWorkLog = nullptr;
    delete modelStandLog;
    modelStandLog = nullptr;
    delete modelCrashTime;
    modelCrashTime = nullptr;
    delete modelWorkTime;
    modelWorkTime = nullptr;
    delete modelCrash;
    modelCrash = nullptr;

    csvPath = readCsvPath();
    #if (DEBUG_ACTIVE==1)
        qDebug() << "Read PATH: " << csvPath << endl;
    #endif

    if ( csvPath.isEmpty() || isMissingFiles() )
    {
        ui -> comboBoxReport -> setEnabled(false);
        ui -> comboBoxDevice -> clear();
        ui -> comboBoxReportType -> clear();
        return;
    }
    else
    {
        ui -> comboBoxReport -> setEnabled(true);
        fillReportTypeCombobox();
        fillDeviceCombobox();
        fillCrashes();
    }

    QFuture<void> t1 = QtConcurrent::run( [this](){ modelWorkLog = new QxtCsvModel( new QFile(csvPath + "/" + QString(WorkLogCSV)), 0, true, ';' );} );
    QFuture<void> t2 = QtConcurrent::run( [this](){ modelStandLog = new QxtCsvModel( new QFile(csvPath + "/" + QString(StandLogCSV)), 0, true, ';' );} );
    t1.waitForFinished();
    t2.waitForFinished();
    if( isSplash ) splash -> showMessage(QObject::tr("Please wait. Loading CSV files - PART 2/2 ..."), Qt::AlignBottom | Qt::AlignRight, Qt::white);

    QFuture<void> t3 = QtConcurrent::run( [this](){ modelCrashTime = new QxtCsvModel( new QFile(csvPath + "/" + QString(CrashTimeCSV)), 0, true, ';' );} );
    QFuture<void> t4 = QtConcurrent::run( [this](){ modelWorkTime = new QxtCsvModel( new QFile(csvPath + "/" + QString(WorkTimeCSV)), 0, true, ';' );} );
    QFuture<void> t5 = QtConcurrent::run( [this](){ modelCrash = new QxtCsvModel( new QFile(csvPath + "/" + QString(CrashCSV)), 0, true, ';' );} );
    t3.waitForFinished();
    t4.waitForFinished();
    t5.waitForFinished();
    if( isSplash ) splash -> showMessage(QObject::tr("STARTING..."), Qt::AlignBottom | Qt::AlignRight, Qt::white);

    #if (DEBUG_ACTIVE==1)
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        qDebug() << "TIME readCSV(): " << duration << endl;
    #endif
}

QString MainWindow::readCsvPath()
{
    QString csvReadPath = "";
    QFile csvFile( path+"/DefaultCSVPath.bin" );

    if ( !csvFile.open(QIODevice::ReadOnly) )
        return QString( "" );

    QDataStream in( &csvFile );
    in >> csvReadPath;
    csvFile.close();
    return csvReadPath;
}

void MainWindow::generateDeviceReport()
{
    reportMap.clear();
    uint raportNumber{};
    uint numberOfReports{};

    #if (DEBUG_ACTIVE==1)
        std::clock_t start;
        double duration;
        start = std::clock();
    #endif

    for ( const int & elem: reportStateVector )
        if ( elem == 1) numberOfReports++;

   for ( const int & elem: reportStateVector )
    {
        while( elem == 1 )
        {
            switch ( raportNumber )
            {
                case 0:
                {
                    statusLabel -> setText( "<font color='white'> Generowanie raportu urządzeń: czas awarii urządzenia ...</font>" );
                    clearStaticArray();
                    #if (DEBUG_ACTIVE==1)
                        std::cout<< "LOG_CZASU_AWARII0.csv" << std::endl;
                    #endif
                    timeLog( modelCrashTime , Count_Log::CrashTime);
                    progressBar -> setValue( progressBar->value() + (100/numberOfReports));
                    break;
                }
                case 1:
                {
                    statusLabel -> setText( "<font color='white'> Generowanie raportu urządzeń: czas pracy urządzenia ...</font>" );
                    clearStaticArray();
                    #if (DEBUG_ACTIVE==1)
                        std::cout<< "LOG_CZASU_PRACY0.csv" << std::endl;
                    #endif
                    timeLog( modelWorkTime , Count_Log::WorkTime);
                    progressBar -> setValue( progressBar->value() + (100/numberOfReports));
                    break;
                }
                case 2:
                {
                    statusLabel -> setText( "<font color='white'> Generowanie raportu urządzeń: ilość rozruchów urządzenia ...</font>" );
                    #if (DEBUG_ACTIVE==1)
                        std::cout<< "LOG_PRACY0.csv" << std::endl;
                    #endif
                    countLog( modelWorkLog , Count_Log::MinusOne );
                    progressBar -> setValue( progressBar->value() + (100/numberOfReports));
                    break;
                }
                case 3:
                {
                    statusLabel -> setText( "<font color='white'> Generowanie raportu urządzeń: ilość wystąpień awarii urządzenia ...</font>" );
                    #if (DEBUG_ACTIVE==1)
                        std::cout<< "LOG_GOTOWOŚĆ0.csv" << std::endl;
                    #endif
                    countLog( modelStandLog , Count_Log::Null );
                    progressBar -> setValue( progressBar->value() + (100/numberOfReports));
                    break;
                }
            }
            break;
        }

     raportNumber++;
    }

    progressBar -> setValue( 100 );
    statusLabel -> setText( "<font color='white'> Zakończono generowanie raportu urządzeń.</font>" );
    player -> setMedia( QUrl("qrc:/pictures/pictures/success.mp3") );
    player -> play();

    displayDeviceReport();
    ui -> tableView -> setModel( displayModel );
    configureTable( ui->tableView, numberOfReports , true );

    #if (DEBUG_ACTIVE==1)
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        qDebug() << "RAPORT TIME: " << duration << endl;
    #endif
}

void MainWindow::countLog(QxtCsvModel *& model, Count_Log equalValue)
{
    #if (DEBUG_ACTIVE==1)
        std::clock_t start;
        double duration;
        start = std::clock();
        qDebug() << "Value to count: " << static_cast<int>(equalValue) << endl;
    #endif

    /* alogrithm */
    int device{};
    QDateTime modelDate;

    for( int i = 0 ; i < model->rowCount() ; ++i )
    {
        modelDate = model->data(model->index(i,1)).toDateTime();
        if ( model->data(model->index( i, 2 )).toInt() == static_cast<int>(equalValue) &&
           ( modelDate >= ui->dateTimeStart->dateTime() && modelDate <= ui->dateTimeEnd->dateTime())
             && model->data(model->index( i , 0 )).toString() != "$RT_OFF$" &&
             model->data(model->index( i , 0 )).toString() != "VarName" )
        {
              //device = model->data(model->index( i , 0 )).toInt();
              device = nameToInt(model->data(model->index( i , 0 )).toString(), equalValue);
              if ( deviceStateVector[ device - 1] )
              {
                  if ( equalValue == Count_Log::Null ) reportMap[device].nullCount = reportMap[device].nullCount + 1;
                  else if ( equalValue == Count_Log::MinusOne ) reportMap[device].minusOneCount = reportMap[device].minusOneCount + 1;
              }
        }
    }

    #if (DEBUG_ACTIVE==1)
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        qDebug() << "TIME (): " << duration << endl;
        for( auto elem: reportMap )
        {
            if ( equalValue == Count_Log::Null ) std::cout << elem.first << " " << elem.second.nullCount << std::endl;
            else if ( equalValue == Count_Log::MinusOne ) std::cout << elem.first << " " << elem.second.minusOneCount << std::endl;
        }
    #endif
}

void MainWindow::crashLog(QxtCsvModel *& model)
{
    #if (DEBUG_ACTIVE==1)
        std::clock_t start;
        double duration;
        start = std::clock();
    #endif

    crashMap.clear();
    QDateTime modelDate;
    int crash{};

    for( int i = 0 ; i < model->rowCount() ; ++i )
    {
        modelDate = model -> data(model -> index(i,1)).toDateTime();
        if ( model -> data(model -> index( i, 2 )).toInt() == static_cast<int>(Count_Log::Crash) &&
           ( modelDate >= ui -> dateTimeStart->dateTime() && modelDate <= ui -> dateTimeEnd -> dateTime()) && model->data(model->index( i , 0 )).toString() != "$RT_OFF$")
        {
            crash = model -> data(model -> index( i , 0 )).toInt();
            crashMap[crash] = crashMap[crash] + 1;
        }
    }

    progressBar -> setValue( 100 );
    statusLabel -> setText( "<font color='white'> Zakończono generowanie raportu awarii.</font>" );
    player -> setMedia( QUrl("qrc:/pictures/pictures/success.mp3") );
    player -> play();

    displayCrashReport();
    ui -> tableView -> setModel( displayModel );
    configureTable( ui->tableView, 1 , false );

    #if (DEBUG_ACTIVE==1)
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        qDebug() << "TIME crashLog(): " << duration << endl;
        for( auto elem: crashMap )
            std::cout << elem.first << " " << elem.second << std::endl;
#endif
}

void MainWindow::timeLog(QxtCsvModel *&model, Count_Log equalValue)
{
    #if (DEBUG_ACTIVE==1)
        std::clock_t start;
        double duration;
        start = std::clock();
        qDebug() << "Value to count: " << static_cast<int>(equalValue) << endl;
    #endif

    QDateTime modelDate;
    long long minutesValue{};
    int device{};

    for( int i = 0 ; i < model->rowCount() ; ++i )
    {
        modelDate = model -> data(model -> index(i,1)).toDateTime();
        if( modelDate >= ui -> dateTimeStart -> dateTime() && modelDate <= ui -> dateTimeEnd -> dateTime() &&
               model->data(model->index( i , 0 )).toString() != "$RT_OFF$"
                && model->data(model->index( i , 0 )).toString() != "VarName")
        {
              //device = model -> data(model -> index( i , 0 )).toInt();
              device = nameToInt(model->data(model->index( i , 0 )).toString(), equalValue);
              if ( deviceStateVector[ device - 1] )
              {
                  //minutesValue =  timeStringToInt( model -> data(model -> index( i , 2 )).toString() );
                  minutesValue =  model -> data(model -> index( i , 2 )).toInt();
                  if ( equalValue == Count_Log::WorkTime )reportMap[device].workTime = diffrent(minutesValue, device-1);
                  else if ( equalValue == Count_Log::CrashTime ) reportMap[device].crashTime = diffrent(minutesValue, device-1);
              }
        }
    }

    #if (DEBUG_ACTIVE==1)
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        qDebug() << "TIME timeLog(): " << duration << endl;
        for( auto elem: reportMap )
        {
            if ( equalValue == Count_Log::WorkTime ) std::cout << elem.first << " " << elem.second.workTime << std::endl;
            else if ( equalValue == Count_Log::CrashTime ) std::cout << elem.first << " " << elem.second.crashTime << std::endl;
        }
    #endif
}

long long MainWindow::maxMin[100]{};
long long MainWindow::minMin[100]{INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
                            INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX};

void MainWindow::clearStaticArray()
{
    for ( int i = 0 ; i < 100 ; ++i )
    {
        maxMin[i] = 0;
        minMin[i] = INT_MAX;
    }
}

long long MainWindow::diffrent(long long actualMinutes, uint idx)
{
    if( actualMinutes > maxMin[idx] )
        maxMin[idx] = actualMinutes;

    if(actualMinutes < minMin[idx])
        minMin[idx] = actualMinutes;

    return ( maxMin[idx] - minMin[idx] );
}

void MainWindow::configureTable(QTableView *& table, uint numberOfReports , bool isDevice)
{
    QFont font( QFont("Calibri Light", 1500/dpiPercent, QFont::Light ,false) );
    if( isDevice)
        displayModel -> setHeaderData( 0, Qt::Horizontal, QObject::tr("Urządzenia") );
    else
        displayModel -> setHeaderData( 0, Qt::Horizontal, QObject::tr("Alarmy") );

    table -> setFont(font);
    table -> setEditTriggers( QAbstractItemView::NoEditTriggers );
    table -> horizontalHeader() -> setFixedHeight( 60 );

    for ( uint i = 0; i < numberOfReports ; ++i )
        table -> setColumnWidth( i, (ui -> tableView -> width()/(numberOfReports+1)) );
    table -> horizontalHeader() -> setStretchLastSection( true );
    table -> horizontalHeader() -> setMaximumSectionSize( (ui -> tableView -> width()/(numberOfReports+1)) );

    for ( int z =0; z < displayModel -> rowCount(); ++z )
       {
         for ( int y =0; y < displayModel -> columnCount(); ++y )
             {
                QStandardItem *item= displayModel -> item( z ,y );
                item -> setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
             }
       }

    proxyModel -> setSourceModel( displayModel );
    proxyModel -> setFilterKeyColumn( -1 );
    proxyModel -> setDynamicSortFilter( true );
    table -> setModel( proxyModel );
}

void MainWindow::displayDeviceReport()
{
    delete displayModel;
    displayModel = nullptr;
    displayModel = new QStandardItemModel( this );

    displayModel -> insertColumns( displayModel -> columnCount(), 1, QModelIndex() ); /* add column for device name */
    /* insert rows */
    for( uint i = 0 ; i < deviceStateVector.size() ; ++i )
    {
        if( deviceStateVector[i] )
        {
            displayModel -> insertRows( displayModel -> rowCount(), 1, QModelIndex() );
            displayModel -> setData( displayModel -> index( (displayModel -> rowCount()-1),0), deviceNameVector[i] );
        }

    }

    /* insert columns */
    uint nextRow = 0;
    uint nextColumn = 1;

    for( uint i = 0; i < DEVICE_RAPORT_TYPE_NUM; ++i ) //value loop
    {
        if( reportStateVector[i] )
        {
            displayModel -> insertColumns( displayModel -> columnCount(), 1, QModelIndex() );

            for( uint j = 0 ; j < deviceStateVector.size() ; ++j )
            {
                if( deviceStateVector[j] )
                {
                    switch ( i )
                    {
                        case 0:
                        {
                            displayModel -> setData( displayModel -> index(nextRow,nextColumn),reportMap[j+1].crashTime );
                            displayModel -> setHeaderData( nextColumn, Qt::Horizontal, QObject::tr("Czas awarii [h]") );
                            break;
                        }
                        case 1:
                        {
                            displayModel -> setData( displayModel -> index(nextRow,nextColumn),reportMap[j+1].workTime );
                            displayModel -> setHeaderData( nextColumn, Qt::Horizontal, QObject::tr("Czas pracy [h]") );
                            break;
                        }
                        case 2:
                        {
                            displayModel -> setData( displayModel -> index(nextRow,nextColumn),reportMap[j+1].minusOneCount );
                            displayModel -> setHeaderData( nextColumn, Qt::Horizontal, QObject::tr("Ilość rozruchów") );
                            break;
                        }
                        case 3:
                        {
                            displayModel -> setData( displayModel -> index(nextRow,nextColumn),reportMap[j+1].nullCount );
                            displayModel -> setHeaderData( nextColumn, Qt::Horizontal, QObject::tr("Ilość awarii"));
                            break;
                        }
                    }
                ++nextRow;
                }

            }
        ++nextColumn;
        nextRow = 0;
        }
    }
}

void MainWindow::displayCrashReport()
{
    delete displayModel;
    displayModel = nullptr;
    displayModel = new QStandardItemModel( this );

    displayModel->insertColumns( displayModel -> columnCount(), 1, QModelIndex() ); /* add column for crash name */
    displayModel->insertColumns( displayModel -> columnCount(), 1, QModelIndex() ); /* add column for count log  */
    displayModel -> setHeaderData( 1, Qt::Horizontal, QObject::tr("Ilość awarii") );

    for( uint i=0; i < crashNameVector.size() ; ++i )
    {
            if(crashMap[i+1]!=0) {
            displayModel -> insertRows( displayModel -> rowCount(),1,QModelIndex() );
            displayModel -> setData( displayModel -> index((displayModel -> rowCount()-1),0), crashNameVector[i] );
            displayModel -> setData( displayModel -> index((displayModel -> rowCount()-1),1), crashMap[i+1] );
            }
    }
}

bool MainWindow::isReportCorrect()
{
    if ( csvPath.isEmpty())
    {
        QMessageBox::information( this, "Informacja" , "Nie skonfigurowano ścieżki źródłowej plików, zawierających rejestry zdarzeń w formacie *.csv." );
        return false;
    }
    if ( !missingFiles.isEmpty() )
    {
        QMessageBox::information( this, "Informacja" , "W ścieżce źródłowej brakuje plików, zawierających rejestry zdarzeń: "+missingFiles+"" );
        return false;
    }
    else if( (ui -> dateTimeEnd -> dateTime()) < (ui -> dateTimeStart -> dateTime()) )
    {
        QMessageBox::information( this, "Informacja" , "Data rozpoczęcia przekracza datę zakończenia." );
        return false;
    }
    else if( (ui -> dateTimeEnd -> dateTime()) == (ui -> dateTimeStart -> dateTime()) )
    {
        QMessageBox::information( this, "Informacja" , "Daty nie mogą być równe." );
        return false;
    }

    return true;
}

void MainWindow::on_buttonAccept_clicked()
{
    if( !isReportCorrect() )
        return;

    if ( ui -> comboBoxReport ->currentIndex() != 0 )
    {

        if ( ui -> comboBoxReport -> currentIndex() == 1 )
        {
            statusLabel -> setText( "" );
            progressBar -> setValue( 0 );
            crashLog( modelCrash );
        }
        else if ( ui -> comboBoxReport -> currentIndex() == 2 )
        {
            /* isChecked() lambda function*/
            auto isChecked = [this]()->bool
            {
                bool isDevice{false};
                bool isRaport{false};
                for ( auto & elem: deviceStateVector )
                {
                    if( elem == 1 )
                    {
                        isDevice = true;
                        break;
                    }
                }

                for ( auto & elem: reportStateVector )
                {
                    if( elem == 1 )
                    {
                        isRaport = true;
                        break;
                    }
                }

                return ( isRaport && isDevice );
            };
            /***********************************/
            if( isChecked() )
            {
                statusLabel -> setText( "" );
                progressBar -> setValue( 0 );
                generateDeviceReport();
            }
            else QMessageBox::information( this, "Informacja" , "Nie wybrano maszyny lub raportu." );

        }
    }
    else QMessageBox::information( this, "Informacja" , "Nie wybrano rodzaju raportu." );
}

/*
 * ---- TOOL BAR functions ----

 * on_action_refreshCSV_triggered() - refresh CSV files
 * on_action_print_triggered() - print QTableView
 * on_action_pdf_triggered() - create pdf file from QTableView
 * grabTable() - create and return temporary QTableView for print
 * printTable() - print QTableView
 * on_action_csv_triggered() - create csv file from QTableView
 * on_action_setCSVPath_triggered() - saves in binary file path to CSV files
 * on_action_SetExportPath_triggered() - saves in binary file path to export

*/

void MainWindow::on_action_refreshCSV_triggered()
{
    if( csvPath.isEmpty() )
        QMessageBox::information( this, "Informacja" , "Nie skonfigurowano ścieżki źródłowej plików, zawierających rejestry zdarzeń w formacie *.csv." );

    else
    {
        statusLabel -> clear();
        statusLabel -> setText( "<font color='white'> Rozpoczęcie aktualizacji. Proszę czekać ... </font>" );
        progressBar -> setValue( 0 );

        ui -> tableView -> setModel( NULL );
        readCSV( false );

        progressBar -> setValue( 100 );
        statusLabel -> setText( "<font color='white'> Zaktualizowano pliki CSV.</font>" );
        player -> setMedia( QUrl("qrc:/pictures/pictures/success.mp3") );
        player -> play();

        if ( !missingFiles.isEmpty() )
            QMessageBox::information( this, "Informacja" , "W ścieżce źródłowej brakuje plików, zawierających rejestry zdarzeń: "+missingFiles+"" );
    }
}

void MainWindow::on_action_print_triggered()
{
    if( ui -> tableView -> model() == nullptr )
    {
        QMessageBox::information( this, "Informacja" , "Brak raportu w tabeli." );
        return;
    }
    printTable( Print_type::Direct );
}

void MainWindow::on_action_pdf_triggered()
{
    if( ui -> tableView -> model() == nullptr )
    {
        QMessageBox::information( this, "Informacja" , "Brak raportu w tabeli." );
        return;
    }
    printTable( Print_type::Pdf );
}

QPixmap MainWindow::grabTable()
{
    const int rows = ui -> tableView -> model() -> rowCount();
    const int columns = ui -> tableView -> model() -> columnCount();

    double totalWidth = ui -> tableView -> verticalHeader() -> width();
    for ( int c = 0; c < columns; ++c )
        totalWidth += ui -> tableView -> columnWidth(c);

    double totalHeight = ui -> tableView -> horizontalHeader() -> height();
    for ( int r = 0; r < rows; ++r )
        totalHeight += ui -> tableView -> rowHeight(r);

    QTableView tempTable( ui->tableView );
    tempTable.setFixedHeight( totalHeight );
    tempTable.setModel( ui -> tableView -> model() );
    tempTable.setFixedSize( totalWidth, totalHeight );
    tempTable.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    tempTable.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    tempTable.verticalHeader() -> hide();
    tempTable.horizontalHeader()->setStyleSheet("font: 22px;");


    for ( int i = 0; i < ui -> tableView -> model() -> columnCount() ; ++i )
        tempTable.setColumnWidth( i, ui -> tableView -> columnWidth(0) );
    tempTable.horizontalHeader() -> setStretchLastSection( true );

    QPixmap grabPixmap = QPixmap::grabWidget( &tempTable );
    return grabPixmap;

}

void MainWindow::printTable(Print_type type)
{
    QPrinter printer( QPrinter::HighResolution );
    QString pdfFile;
    QString filters( "Pliki PDF (*.pdf);;Wszystkie pliki (*.*)" );
    QString pdfFilter( "Pliki PDF (*.pdf)" );

    switch ( type )
    {

        case Print_type::Pdf:
        {
            if( exportPath.isEmpty() )
                pdfFile = QFileDialog::getSaveFileName( this, "Zapisz plik", QDir::homePath(), filters, &pdfFilter );
            else
                pdfFile = QFileDialog::getSaveFileName( this, "Zapisz plik", exportPath, filters, &pdfFilter );

            if ( pdfFile.isEmpty() )
                return;

            printer.setOutputFileName( pdfFile );
            printer.setOutputFormat( QPrinter::PdfFormat );
            printer.setFullPage( true );
            printer.setPageMargins( 15, 0, 15, 0, QPrinter::Millimeter );
            break;
        }
        case Print_type::Direct:
        {
            QPrintDialog dialog( &printer, this );
            dialog.setWindowTitle( tr("Wydrukuj raport") );
            if ( dialog.exec() != QDialog::Accepted ) return;
            printer.setFullPage( true );
            printer.setPageMargins( 15, 0, 15, 0, QPrinter::Millimeter );
            break;
        }
        default:
            break;

    }


    QPainter painter( &printer );

    if( type == Print_type::Direct ) painter.scale( 4, 4 );
    if( type == Print_type::Pdf ) painter.scale( 8, 8 );

    QPixmap pixmap = grabTable();

    QRectF sourceRect;
    double totalPageHeight = ui -> tableView -> horizontalHeader() -> height();
    int columnCount = 0;
    int rowCount = 0;
    int pageCount = 1;

    QFont headerFont;
    headerFont.setFamily("Calibri");
    headerFont.setPixelSize(1200/dpiPercent);
    headerFont.setWeight(1200/dpiPercent);
    painter.setFont( headerFont );

    QPoint offsetPdf, offsetDirect;
    offsetPdf.setX( 50 );
    offsetPdf.setY( 100 );
    offsetDirect.setX( -50 );
    offsetDirect.setY( 100 );

    // First take the rows that fit into one page
    for ( int h = 0; h < ui -> tableView -> model() -> rowCount(); h++ )
    {
        totalPageHeight += ui -> tableView -> rowHeight(h);
        double totalPageWidth = ui -> tableView -> verticalHeader() -> width();

        if ( rowCount == 49 || h == ui -> tableView -> model() -> rowCount() - 1 )
        {
            // Then take the columns that fit into one page
            for ( int w = 0; w < ui -> tableView -> model() -> columnCount(); w++ )
            {
                totalPageWidth += ui -> tableView -> columnWidth(w);
                if ( columnCount == 5 || (w == ui -> tableView -> model() -> columnCount() - 1) )
                {
                    sourceRect.setWidth( totalPageWidth );
                    sourceRect.setHeight( totalPageHeight + 14 );
                    if( type == Print_type::Pdf )
                    {
                        if( pageCount == 1 )
                        {
                            painter.drawText( QPoint(50, 50), "Wygenerowano: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") );
                            painter.drawText( QPoint(50 + ui -> tableView -> columnWidth(0), 50), "Od: " + ui -> dateTimeStart -> dateTime().toString("yyyy-MM-dd hh") );
                            painter.drawText( QPoint(50 + ui -> tableView -> columnWidth(0), 75), "Do: " + ui -> dateTimeEnd -> dateTime().toString("yyyy-MM-dd hh") );
                        }
                        painter.drawPixmap( printer.pageRect().topLeft()+offsetPdf, pixmap, sourceRect );

                    }
                    if( type == Print_type::Direct )
                    {
                        if( pageCount == 1 )
                        {
                            painter.drawText( QPoint(-50, 50), "Wygenerowano: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
                            painter.drawText( QPoint(-50 + ui -> tableView -> columnWidth(0), 50), "Od: " + ui -> dateTimeStart -> dateTime().toString("yyyy-MM-dd hh") );
                            painter.drawText( QPoint(-50 + ui -> tableView -> columnWidth(0), 75), "Do: " + ui -> dateTimeEnd -> dateTime().toString("yyyy-MM-dd hh") );
                        }
                        painter.drawPixmap( printer.pageRect().topLeft()+offsetDirect, pixmap, sourceRect );
                    }

                    sourceRect.setLeft( sourceRect.left() + totalPageWidth );

                    if ( w != ui -> tableView -> model() -> columnCount() - 1 )
                        printer.newPage();

                    totalPageWidth = 0;
                    columnCount = 0;
                }
                else
                {
                    columnCount++;
                }
            }


            sourceRect.setTop( sourceRect.top() + totalPageHeight + 7 );
            sourceRect.setLeft( 0 );

            if (h != ui -> tableView -> model() -> rowCount() - 1)
            {
                ++pageCount;
                printer.newPage();
            }

            totalPageHeight = 0;
            rowCount = 0;
        }
        else
        {
            rowCount++;
        }
    }
    if( type == Print_type::Direct ) QMessageBox::information( this, "Informacja", "Rozpoczęto drukowanie." );
    if( type == Print_type::Pdf ) QMessageBox::information( this, "Informacja", "Wyeksportowano do pliku .pdf" );
}

void MainWindow::on_action_csv_triggered()
{
    if( ui -> tableView -> model() == nullptr )
    {
        QMessageBox::information( this, "Informacja" , "Brak raportu w tabeli." );
        return;
    }

    QString pathFile;
    QString filters( "Pliki CSV (*.csv);;Wszystkie pliki (*.*)" );
    QString csvFilter( "Pliki CSV (*.csv)" );
    if( exportPath.isEmpty() )
        pathFile = QFileDialog::getSaveFileName( this, "Zapisz plik", QDir::homePath(), filters, &csvFilter );
    else
        pathFile = QFileDialog::getSaveFileName( this, "Zapisz plik", exportPath , filters, &csvFilter );

    if ( pathFile.isEmpty() )
        return;

    QFile csvFile(pathFile);
    if ( !csvFile.open(QIODevice::WriteOnly) )
        {
            QMessageBox::information( this, "Informacja", "Wyeksportowano do pliku .csv" );
            return;
        }
    QTextStream out( &csvFile );
    QString data;
    QString separator = ";";
    uint numberOfColumns = ui -> tableView -> model() -> columnCount();

    /* fill headers */
    for( uint col = 0; col < numberOfColumns; ++col)
        data += ui -> tableView -> model() -> headerData(col ,Qt::Horizontal).toString() + separator;
    out << data << endl;

    /* fill cells */
    for( int row = 0 ; row < ui -> tableView -> model() -> rowCount() ; ++row )
    {
        data.clear();
        for ( uint col = 0; col < numberOfColumns ; ++col )
            data += ui -> tableView -> model() -> data( ui -> tableView -> model() -> index(row,col)).toString() + separator;
        out << data << endl;
    }   

    csvFile.close();
    QMessageBox::information( this, "Informacja" , "Wyeksportowano do pliku .csv ." );
}

void MainWindow::on_action_setCSVPath_triggered()
{
    QString csvWritePath;
    if( csvPath.isEmpty() ) csvWritePath = QFileDialog::getExistingDirectory( this, tr("Wybierz plik"), QDir::homePath() );
    else  csvWritePath = QFileDialog::getExistingDirectory( this, tr("Wybierz plik"), csvPath);

    if( csvWritePath.isEmpty() )
        return;

    QFile csvFile( path+"/DefaultCSVPath.bin" );
    if ( !csvFile.open(QIODevice::WriteOnly) )
        {
            QMessageBox::information( this, "Informacja", "Nie można otworzyć pliku do zapisania ścieżki." );
            return;
        }

    QDataStream out( &csvFile );
    out << csvWritePath;
    csvFile.close();
    QMessageBox::information( this, "Informacja" , "Ścieżka zapisana poprawnie. Nastąpi automatyczna aktualizacja rejestrów zdarzeń." );
    csvPath = csvWritePath;

    on_action_refreshCSV_triggered();
}

void MainWindow::on_action_SetExportPath_triggered()
{
    QString csvWritePath;
    if( exportPath.isEmpty() )
        csvWritePath = QFileDialog::getExistingDirectory( this, tr("Wybierz plik"), QDir::homePath() );
    else
        csvWritePath = QFileDialog::getExistingDirectory( this, tr("Wybierz plik"), exportPath);


    if( csvWritePath.isEmpty() )
        return;

    QFile csvFile( path+"/DefaultExportPath.bin" );
    if ( !csvFile.open(QIODevice::WriteOnly) )
        {
            QMessageBox::information( this, "Informacja", "Nie można otworzyć pliku do zapisania ścieżki." );
            return;
        }

    QDataStream out( &csvFile );
    out << csvWritePath;
    csvFile.close();
    exportPath = csvWritePath;
    QMessageBox::information( this, "Informacja" , "Ścieżka do eksportu plików zapisana poprawnie." );
}

int MainWindow::timeStringToInt(QString input)
{
    QStringList timeList = input.split( ":" );

    if( timeList.size() > 3 )
        return 0;
    else return ( timeList.at(0).toInt() );
}

int MainWindow::nameToInt(QString name, Count_Log type)
{
    int tmp = -1;
    QStringList tmpList;

    if(type == Count_Log::Null || type == Count_Log::MinusOne)
    {
        tmpList = name.split("{");
        tmpList = tmpList.at(1).split("}");
        tmp = tmpList.at(0).toInt();
        return tmp;

    }
    else if(type == Count_Log::CrashTime || type == Count_Log::WorkTime)
    {
        tmpList = name.split("_");
        tmp = tmpList.at(2).toInt();
        return tmp;
    }
    else
        return tmp;

}

QString MainWindow::readExportPath()
{
    QString exportReadPath = "";
    QFile csvFile( path+"/DefaultExportPath.bin" );

    if ( !csvFile.open(QIODevice::ReadOnly) )
        return QString("");

    QDataStream in( &csvFile );
    in >> exportReadPath;
    csvFile.close();
    return exportReadPath;
}

void MainWindow::on_action_close_triggered()
{
    QApplication::quit();
}

void MainWindow::on_action_about_triggered()
{
    about aboutDialog( this );
    aboutDialog.setWindowFlags( ((configureDialog->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowContextHelpButtonHint) );
    aboutDialog.setWindowTitle( "O programie Raportowanie" );
    aboutDialog.setWindowIcon( QIcon( ":/pictures/pictures/sigma.png") );
    aboutDialog.exec();
}

void MainWindow::on_action_technicalSupport_triggered()
{
    TechnicalSupport technicalSupportDialog( this );
    technicalSupportDialog.setWindowFlags( ((configureDialog->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowContextHelpButtonHint) );
    technicalSupportDialog.setWindowTitle( "Wparcie techniczne");
    technicalSupportDialog.setWindowIcon( QIcon( ":/pictures/pictures/help.png") );
    technicalSupportDialog.exec();
}
