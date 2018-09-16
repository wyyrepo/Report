#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qxtcsvmodel.h"
#include "configuredialog.h"
#include "about.h"
#include "technicalsupport.h"

#include <QApplication>
#include <QCalendarWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QSplashScreen>
#include <QProgressBar>
#include <QPainter>
#include <QPrinter>
#include <QPrinterInfo>
#include <QtPrintSupport>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QPagedPaintDevice>
#include <QPageLayout>
#include <QtGlobal>
#include <QPoint>
#include <QRectF>
#include <QFont>
#include <QTimer>

#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <set>
#include <limits.h>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readCSV(bool isSplash = true);

private:

    Ui::MainWindow *ui{};
    QProgressBar * progressBar;
    QLabel * statusLabel;
    QString csvPath{};
    QString missingFiles{};
    QString exportPath{};

    ConfigureDialog * configureDialog{};
    QMediaPlayer * player{};
    QxtCsvModel * modelWorkLog{};
    QxtCsvModel * modelStandLog{};
    QxtCsvModel * modelCrashTime{};
    QxtCsvModel * modelWorkTime{};
    QxtCsvModel * modelCrash{};
    QxtCsvModel * csvModel{};
    QStandardItemModel * displayModel{};
    QSortFilterProxyModel * proxyModel{};
    QStandardItemModel * itemDeviceModel{};
    QStandardItemModel * itemReportModel{};

    QString typeList[6] { "Typ raportu",
                          "Zaznacz wszystko" ,
                          "Czas awarii urządzenia",
                          "Czas pracy urządzenia",
                          "Ilość rozruchów urządzenia" ,
                          "Ilość wystąpień awarii urządzenia"};

    std::vector<int> reportStateVector;
    std::vector<int> deviceStateVector;
    std::vector<QString> deviceNameVector;
    std::vector<QString> crashNameVector;

    static long long maxMin[100];
    static long long minMin[100];
    void clearStaticArray();
    long long diffrent( long long actualMinutes, unsigned int idx );

    struct Raport_COL
    {
        int minusOneCount;
        int nullCount;
        long long workTime;
        long long crashTime;
    };
    enum class Count_Log
    {
        MinusOne = -1,
        Null = 0,
        WorkTime = 1,
        CrashTime = 2,
        Crash = -1
    };
    enum class Print_type
    {
        Direct = 0,
        Pdf = 1
    };

    std::map <int, Raport_COL> reportMap;
    std::map <int, int> crashMap;

    QString readCsvPath();
    QString readExportPath();
    void fillDeviceCombobox();
    void fillReportTypeCombobox();
    void fillCrashes();
    void clearComboboxes();
    void calendarDialog();
    bool isReportCorrect();
    bool isMissingFiles();
    void generateDeviceReport();
    void countLog(QxtCsvModel *&, Count_Log );
    void timeLog(QxtCsvModel *&, Count_Log );
    void crashLog(QxtCsvModel *&);
    void displayReport();
    QPixmap grabTable();
    void printTable(Print_type type);
    void displayDeviceReport();
    void displayCrashReport();
    void configureTable(QTableView *&, unsigned int, bool);
    int timeStringToInt(QString);
    int nameToInt(QString, Count_Log);

    enum class Type_Of_Raport
    {
       Czas_awarii_urzadzenia,
       Czas_pracy_urzadzenia,
       Ilosc_rozruchow_urzadzenia,
       Ilosc_wystapien_awarii_urzadzenia,
    };

private slots:
    void on_DeviceCheck( const QModelIndex&, const QModelIndex& );
    void on_ReportTypeCheck( const QModelIndex&, const QModelIndex& );
    void on_CreateTimeDialog( QDate );
    void on_ItemReportTypeClicked(QModelIndex);
    void on_ItemDeviceClicked(QModelIndex);
    void on_ConfigureDialog();
    void on_buttonAccept_clicked();
    void on_comboBoxReport_activated(int index);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_action_pdf_triggered();
    void on_action_csv_triggered();
    void on_action_print_triggered();
    void on_action_refreshCSV_triggered();
    void on_action_setCSVPath_triggered();
    void on_action_SetExportPath_triggered();
    void on_action_close_triggered();
    void on_action_about_triggered();
    void on_action_technicalSupport_triggered();
};




#endif // MAINWINDOW_H
