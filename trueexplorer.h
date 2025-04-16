#ifndef TRUEEXPLORER_H
#define TRUEEXPLORER_H
#include <QMainWindow>
#include <QDir>
#include <QListWidget>
#include <qsqlquery.h>
#include <qtreewidget.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class TrueExplorer;
}
QT_END_NAMESPACE

class TrueExplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrueExplorer(QWidget *parent = nullptr);
    ~TrueExplorer();
    QDir dir;
    void startFileMonitoringProcess();

private slots:
    //UI Setup
    void IconSetup();
    void updateBreadcrumbs(const QString &path);
    void reloadDirectory();
    void on_reloadButton_clicked();

    //File Op
    void loadDirectory(const QString &path);
    void on_newFileButton_clicked();
    void on_newFolderButton_clicked();
    void renameSelectedItem();

    //Button Clicks
    void on_prevDirectoryButton_clicked();

    // void addToFavouritesSlot();

    void testFunction();

    void on_prevFolderButton_clicked();

    void on_nextFolderButton_clicked();

    void performSearch();

    void on_searchButton_clicked();

    void on_searchLineEdit_textChanged();

    void onDriveClicked(int row, int column);

    void on_treeWidget_2_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_2_customContextMenuRequested(const QPoint &pos);

    void on_favoritesButton_clicked();

    void on_viewIndexToolButton_clicked();

    void on_recentFilesButton_clicked();

private:
    Ui::TrueExplorer *ui;
    QStringList clipboardPaths;   // Store copied/cut items
    bool cutMode = false;  // Track if items are cut
    bool deleteFolderContents(QDir &dir);
    bool copyDirectory(const QString &source, const QString &destination);


    QVector<QString> directoryHistory;  // Stores visited directories
    int historyIndex = -1;              // Tracks the current position

    void populateTreeWidget(QSqlQuery &query);

    void populateDrives();

protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // TRUEEXPLORER_H
