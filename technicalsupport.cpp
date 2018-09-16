#include "technicalsupport.h"
#include "ui_technicalsupport.h"

extern QString path;
extern double dpiPercent;
#define DEBUG_ACTIVE 0

TechnicalSupport::TechnicalSupport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TechnicalSupport)
{
    ui -> setupUi(this);
    ui -> buttonLeft -> setIcon( QIcon(":/pictures/pictures/arrow_left.png") );
    ui -> buttonLeft -> setIconSize( QSize(40,40) );
    ui -> buttonRight -> setIcon( QIcon(":/pictures/pictures/arrow_right.png") );
    ui -> buttonRight -> setIconSize( QSize(40,40) );
    ui -> buttonHome -> setIcon( QIcon(":/pictures/pictures/home.png") );
    ui -> buttonHome -> setIconSize( QSize(40,40) );
    connect( this, SIGNAL(setTextBrowser(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
    on_buttonHome_clicked();
    ui -> buttonRight -> setEnabled( false );
    ui -> buttonLeft -> setEnabled( false );
    ui -> treeWidget -> setFont( QFont("Segoe UI", 900/dpiPercent, QFont::Light ,false) );

    ui -> textGeneralInformation -> insertHtml(
        "<b><p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;>Informacje ogólne</span></p></b>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/sigma_LOGO.png /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Opis programu</b></u></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Raportowanie v1.0 jest programem do raportowania pracy "
        "urządzeń linii produkcyjnej na podstawie rejestrów zdarzeń (logów), w postaci plików CSV. Użytkownik ma możliwość wygenerowania raportu według własnych kryteriów: przedział czasowy, rodzaj raportu,  ilość maszyn.</span></p>"
    );

    ui -> textMenu ->insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Menu</b></span></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1600/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/menu.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><u><b>Opis</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Menu zawiera dwie zakładki:</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Plik</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(800/dpiPercent)+"pt;></span><img src=:/pictures/pictures/menu_file.png /></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Pomoc</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;></span><img src=:/pictures/pictures/menu_help.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui -> textFile ->insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Plik</b></span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/menu_file.png /></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(800/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><u><b>EKSPORTUJ JAKO &gt;&gt; </b></u></span><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600;></span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600;> </span><img src=:/pictures/pictures/menu_export.png /></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> Otwiera menu eksportu. Zawiera następujące opcje:</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>		</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;> <img src=:/pictures/pictures/pdf.png /> <span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> eksportuj do pdf - eksportuje tabelę do pliku pdf.</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> </span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;> <img src=:/pictures/pictures/csv.png /> <span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> eksportuj do csv - eksportuje tabelę do pliku csv.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>DRUKUJ</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;> <img src=:/pictures/pictures/print.png /> <span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600;> </span><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Otwiera standardowe okno drukowania Windows ®,  pozwalając  użytkownikowi wydrukować zawartość tabeli.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u> AKTUALIZUJ PLIKI CSV </u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;> <img src=:/pictures/pictures/refresh.png /> <span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Aktualizuje pliki CSV. Program wczytuje pliki CSV do pamięci podczas uruchamiania programu. Ewentuale zmiany w plikach wymagają aktualizacji.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>USTAW ŚCIEŻKĘ DLA REJESTRÓW ZDARZEŃ </u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;>  <img src=:/pictures/pictures/csv_path.png />  U<span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>stawia ścieżkę źródłową dla rejestrów zdarzeń ( plików CSV ).</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>USTAW ŚCIEŻKĘ EKSPORTU PLIKÓW</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;> <img src=:/pictures/pictures/export_path.png /><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> Ustawia miejsce docelowe eksportu plików.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>ZAMKNIJ</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;> <img src=:/pictures/pictures/exit.png /> <span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> Zamyka program.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui -> textReportTable ->insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Tabela raportu</b></span></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1400/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/table.png /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Opis</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Tabela raportu przedstawia wybrany przez użytkownika raport. W przypadku raportu awarii pierwsza kolumna to nazwa awarii, natomiast druga ilość jej wystąpień w wybranym przez użytkownika przedziale czasowym. W przypadku raportu dla urządzeń pierwsza kolumna to nazwa wybranego urządzenia, natomiast kolejne przedstawiają wybrany typ raportu.</span></p></body></html>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui -> textMessages -> insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Komunikaty</b></span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1400/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>WYBÓR DATY</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>1. Data rozpoczęcia nie może przekraczać daty zakończenia.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_date1.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>2. Data rozpoczęcia nie może być równa dacie zakończenia.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_date2.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>3. Data rozpoczęcia lub zakończenia nie może przekraczać aktualnej daty.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_date3.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>4. Godzina nie została wpisana przez użytkownika. Jej domyślna wartość to 00.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_hour.png /></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(800/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>ZATWIERDZENIE RAPORTU</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>1. Nie został wybrany raport główny.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> </span><img src=:/pictures/pictures/msg_noreport.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>2. Nie zaznaczono typu raportu lub rodzaju urządzenia w przypadku raportu dla urządzeń.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_nodevice.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>3. Nie wybrano ścieżki do odczytu rejestrów zdarzeń ( plików CSV ).</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_nocsvpath.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>4. W ścieżce do odczytu rejestrów zdarzeń brakuje wszystkich potrzebnych plików. Komunikat wyświetla brakujące pliki.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_nofiles.png /></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(800/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>KOMUNIKATY INFORMACYJNE</u></b></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>1. Ze wzgledu na brak wygenerowanego raportu nie możliwe jest wykonanie jednej z wymienionych opcji: drukowanie, eksport do pliku csv, eksport do pliku pdf.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_notable2.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>2. Eksport do pliku pdf lub csv przebiegł pomyślnie.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_pdfexport.png /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_csvexport.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>3. Rozpoczęto drukowanie wygenerowanego raportu.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_print.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>4. Ścieżka do rejestrów zdarzeń ( plików CSV ) została zapisana poprawnie. Nastąpi automatyczna aktualizacja plików.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/msg_csvsave.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui -> textMainScreen -> insertHtml(
        "<b><p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;>Okno główne</span></p></b>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size::"+QString::number(1600/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/main_window.png /></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Główny ekran zawiera 6 głównych obszarów:</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>1. Menu,</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>2. Ustawianie przedziału czasowego,</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>3. Wybór raportu,</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>4. Wyszukiwanie,</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>5. Tabela raportu,</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>6. Status aplikacji</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; text-decoration: underline;></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>MENU</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Pasek menu programu zawiera 2 elementy:</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Plik</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Pomoc</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Indywidualny opis poszczególnych pozycji menu umieszczono na innej stronie.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>USTAWIENIE CZASU</b></u></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Obszar wyboru przedziału czasowego, w jakim mają być wyszukiwane dane. Bardziej obszerny opis umieszczono na innej stronie.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>WYBÓR RAPORTU</b></u></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Obszar składa się z trzech pól wyboru oraz przycisku zatwierdzenia. W kolejności od lewej do prawej: wybór raportu głownego, wybór raportu dla urządzeń, wybór urządzeń, przycisk zatwierdzenia. Bardziej obszerny opis umieszczono na innej stronie.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>WYSZUKIWANIE</b></u></span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/searchline.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Pole przeszukiwania tabeli raportu. Wielkość liter nie ma znaczenia.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>TABELA RAPORTU</b></u></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Obszar wyświetlania wygenerowanego raportu. Bardziej obszerny opis umieszczono na innej stronie.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>STATUS APLIKACJI</b></u></span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(800/dpiPercent)+"pt;></span><img src=:/pictures/pictures/status.png /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Obszar informujący o aktualnym statusie aplikacji. Składa się z:</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>1. Pola tekstowego - wyświetla informacje o aktualnym stanie aplikacji.</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>2. Paska statusu - informuje o aktualnym postępie zadań.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><br /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui -> textHelp -> insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Pomoc</b?</span></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/menu_help.png /></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1400/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>WSPARCIE TECHNICZNE</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(800/dpiPercent)+"pt;>   </span><img src=:/pictures/pictures/help.png /><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> Otwiera okno wsparcia technicznego.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>O PROGRAMIE</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(800/dpiPercent)+"pt;>   </span><img src=:/pictures/pictures/about.png /> <span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Otwiera okno przedstawiające informacje dotyczące programu.</span></p></body></html>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui ->  textSetDate -> insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Ustawianie przedziału czasowego</b></span></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/setdate.png /></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt; font-weight:600;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Opis</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Obszar ustawiania przedziału czasowego można podzielić na dwa pola:</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* pole wyboru początkowej daty wraz z godziną.</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* pole wyboru końcowej daty wraz z godziną.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Wybór daty</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/arrow_down.png /><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Aby wybrać datę należy nacisnąć strzałkę. Wybór polega na zaznaczeniu intresującej daty lewym przyciskiem myszy.</span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:8pt;>  </span><img src=:/pictures/pictures/date.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Po wybraniu daty pojawi się okno, w którym należy wpisać godzinę a  następnie zatwierdzić przyciskiem.</span></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:8pt;>  </span><img src=:/pictures/pictures/hour.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    ui -> textReports -> insertHtml(
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><b>Wybór raportu</b></span></p>"
        "<p align=center style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1800/dpiPercent)+"pt; font-weight:600;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Opis</b></u></span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Obszar wyboru daty składa się z następująych elementów:</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* wybór raportu głównego</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* wybór raportu dla urządzeń</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* wybór urządzeń</span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* przycisk zatwierdzenia</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>WYBÓR RAPORTU GŁÓWNEGO</b></u></span></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Do wyboru dostępne są: </span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/main_report.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>1. Wybierz raport - pozycja neutralna</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>2. Raport awarii - ilość wystąpień awarii w wybranym przez użytkownika przedziale czasowym.</span></p>"
        "<p align=justify style margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>3. Raport dla urządzeń - informacje o urządzeniach w wybranym przez użytkownika przedziale czasowym. Dokładny opis w poniższym punkcie.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>WYBÓR RAPORTU</b></u></span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/device_reports.png /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>W przypadku wybrania raportu dla urządzeń pola: typ raportu oraz rodzaj urządzenia stają się aktywne, o czym sygnalizuje zielona strzałka.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Typ raportu</b></u></span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/type_report.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(800/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Pozwala na wybór określonej przez użytkownika kombinacji 4 raportów:</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Czas awarii urządzenia - ilość godzin awarii w wybranym przez użytkownika przedziale czasowym.</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Czas pracy urządzenia - ilość godzin pracy w wybranym przez użytkownika przedziale czasowym.</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Ilość rozruchów urządzenia - ilość wystąpień rozruchów urządzenia w wybranym przez użytkownika przedziale czasowym.</span></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>* Ilość wystąpień awarii urządzenia - ilość wystąpień awarii urządzenia w wybranym przez użytkownika przedziale czasowym.</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=justify style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>Urządzenie</b></u></span><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;> - pozwala na wybór określonych przez użytkownika urządzeń</span></p>"
        "<p align=justify style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/device_report.png /></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:"+QString::number(1000/dpiPercent)+"pt;><br /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt; font-weight:600; text-decoration: underline;><b><u>PRZYCISK ZATWIERDZENIA</b></u></span></p>"
        "<p align=center style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><img src=:/pictures/pictures/accept_button.png /></p>"
        "<p style= margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><span style= font-size:"+QString::number(1000/dpiPercent)+"pt;>Zatwierdza wybrany przez użytkownika raport. W przypadku błędu wyświetla odpowiedni komunikat. Bardziej obszerny opis komunikatów o błędach umieszczono na innej stronie.</span></p>"
        "<p style=-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;><br /></p>"
    );

    moveCoursorUp();
}

TechnicalSupport::~TechnicalSupport()
{
    delete ui;
}

void TechnicalSupport::moveCoursorUp()
{
    ui -> textReports -> moveCursor(QTextCursor::Start);
    ui -> textGeneralInformation -> moveCursor(QTextCursor::Start);
    ui -> textMenu -> moveCursor(QTextCursor::Start);
    ui -> textFile -> moveCursor(QTextCursor::Start);
    ui -> textReportTable -> moveCursor(QTextCursor::Start);
    ui -> textMainScreen -> moveCursor(QTextCursor::Start);
    ui -> textHelp -> moveCursor(QTextCursor::Start);
    ui -> textSetDate -> moveCursor(QTextCursor::Start);
    ui -> textMessages -> moveCursor(QTextCursor::Start);
}

void TechnicalSupport::on_treeWidget_itemSelectionChanged()
{
    moveCoursorUp();
    QString itemName = ui -> treeWidget -> currentItem() -> text(ui -> treeWidget -> currentColumn());
    emit setTextBrowser( findIndex( itemName ));
}

int TechnicalSupport::findIndex( QString itemName )
{
    int idx{};

    if( itemName == "Informacje ogólne" ) idx = 0;
    else if( itemName == "Okno główne" ) idx = 1;
    else if( itemName == "Menu" ) idx = 2;
    else if( itemName == "Plik" ) idx = 3;
    else if( itemName == "Pomoc" ) idx = 4;
    else if( itemName == "Ustawianie przedziału czasowego" ) idx = 5;
    else if( itemName == "Wybór raportu" ) idx = 6;
    else if( itemName == "Tabela raportu" ) idx = 7;
    else if( itemName == "Komunikaty aplikacji" ) idx = 8;

    return idx;
}

void TechnicalSupport::on_buttonLeft_clicked()
{
    ui -> buttonRight -> setEnabled(true);
    if( it != treeList.begin() )
    {
        --it;
        emit setTextBrowser( findIndex( (*it)->text(0) ));
    }
    if (it == treeList.begin()) ui -> buttonLeft -> setEnabled(false);
}

void TechnicalSupport::on_buttonRight_clicked()
{
    ui -> buttonLeft -> setEnabled(true);
    std::list<QTreeWidgetItem*>::iterator before_end;
    before_end = treeList.end();
    --before_end;
    if( it != before_end )
    {
        ++it;
        emit setTextBrowser( findIndex( (*it)->text(0) ));
    }
    if (it == before_end) ui -> buttonRight -> setEnabled(false);
}


void TechnicalSupport::on_buttonHome_clicked()
{
    ui -> treeWidget -> setCurrentItem( ui->treeWidget->itemAt(0,0));
    on_treeWidget_itemPressed( ui -> treeWidget -> itemAt( 0, 0 ), 0 );
    if( treeList.size() == 1 )
    {
        ui -> buttonRight -> setEnabled(false);
        ui -> buttonLeft -> setEnabled(false);
    }
}

void TechnicalSupport::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    if ( treeList.empty() ) /* first item */
    {
        treeList.push_back( item );
        it = treeList.begin();
        ui -> buttonLeft -> setEnabled(true);
    }
    else
    {
        std::list<QTreeWidgetItem*>::iterator before_end;
        before_end = treeList.end();
        --before_end;

        if( it != before_end ) /* if iterator different from list end */
            {
                /* cut the list and add new item */
                treeList.erase(++it, treeList.end());
                --it;
                if ( treeList.size() == 1 && (*it)->text(column) == item->text(column) )
                    return;
                else
                {
                    treeList.push_back( item );
                    it = treeList.end();
                    --it;
                    if( treeList.size() == 2 )
                        ui -> buttonLeft -> setEnabled(true);
                    ui -> buttonRight -> setEnabled(false);
                }
            }

        else
        {
            if( item->text(column) == treeList.back()->text(column) ) /* if item reapeted */
            {
                ui -> treeWidget -> setCurrentItem( item );
                emit setTextBrowser( findIndex( item->text(0) ));
            }
            else /* add item to list */
            {
                ui -> buttonLeft -> setEnabled(true);
                treeList.push_back( item );
                ++it;
            }
        }
    }

    #if (DEBUG_ACTIVE==1)
        for( auto & elem : treeList )
            qDebug() << elem->text(column) << endl;
        qDebug() << endl;
    #endif
}
