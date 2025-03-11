#ifndef TRUEEXPLORER_H
#define TRUEEXPLORER_H
#include <QMainWindow>
#include <QDir>
#include <QListWidget>
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
    void deleteSelectedItem();

    //Button Clicks
    void on_prevDirectoryButton_clicked();

    //Event Handlers
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    // void addToFavouritesSlot();

    void testFunction();

    void on_prevFolderButton_clicked();

    void on_nextFolderButton_clicked();

private:
    Ui::TrueExplorer *ui;
    QStringList clipboardPaths;   // Store copied/cut items
    bool cutMode = false;  // Track if items are cut
    bool deleteFolderContents(QDir &dir);
    bool copyDirectory(const QString &source, const QString &destination);

    // keybind events
    void copySelectedItems();
    void cutSelectedItems();
    void pasteItems();
    void deleteSelectedItems();

    QVector<QString> directoryHistory;  // Stores visited directories
    int historyIndex = -1;              // Tracks the current position
protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // TRUEEXPLORER_H
