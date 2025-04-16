#ifndef DATABASEVIEWER_H
#define DATABASEVIEWER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>


namespace Ui {
class databaseviewer;
}

class databaseviewer : public QDialog
{
    Q_OBJECT

public:
    explicit databaseviewer(const QString &dbPath, QWidget *parent = nullptr);
    ~databaseviewer();

private:
    Ui::databaseviewer *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // DATABASEVIEWER_H
