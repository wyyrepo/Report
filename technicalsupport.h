#ifndef TECHNICALSUPPORT_H
#define TECHNICALSUPPORT_H

#include <QDialog>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QModelIndex>
#include <list>
#include <iterator>

namespace Ui {
class TechnicalSupport;
}

class TechnicalSupport : public QDialog
{
    Q_OBJECT

public:
    explicit TechnicalSupport(QWidget *parent = 0);
    ~TechnicalSupport();

signals:
    void setTextBrowser(int idx);

private slots:
    void on_treeWidget_itemSelectionChanged();
    void on_buttonLeft_clicked();
    void on_buttonRight_clicked();
    void on_buttonHome_clicked();
    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::TechnicalSupport *ui;
    int findIndex( QString itemName );
    std::list<QTreeWidgetItem*> treeList;
    std::list<QTreeWidgetItem*>::iterator it;
    void moveCoursorUp();
};

#endif // TECHNICALSUPPORT_H
