#include "databaseviewer.h"
#include "ui_databaseviewer.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>

databaseviewer::databaseviewer(const QString &dbPath, QWidget *parent)
    : QDialog(parent), ui(new Ui::databaseviewer), model(nullptr)
{
    ui->setupUi(this);

    // Create and set up the SQLite database connection
    db = QSqlDatabase::addDatabase("QSQLITE", "viewer_connection");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }

    // Get list of tables
    QStringList tables = db.tables();
    if (tables.isEmpty()) {
        QMessageBox::information(this, "No Tables", "No tables found in the database.");
        return;
    }

    // Set up model to display the first table
    model = new QSqlTableModel(this, db);
    model->setTable(tables.first());
    model->select();

    ui->tableView->setModel(model);
}

databaseviewer::~databaseviewer()
{
    db.close();  // Close the database connection
    QSqlDatabase::removeDatabase("viewer_connection");  // Remove the named connection
    delete ui;
}
