#include "trueexplorer.h"
#include "./ui_trueexplorer.h"
#include "contextmenuactions.h"
#include <QIcon>
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileIconProvider>
#include <iostream>
#include <QInputDialog>
#include <QMenu>
#include <QBrush>
#include <QKeyEvent>
#include <QFile>
#include <QFileDialog>
#include "databaseviewer.h"
#include "indexinghandler.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTreeWidgetItem>
#include <qprocess.h>
#include <qstandardpaths.h>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSqlRecord>
#include <QClipboard>
#include <QGuiApplication>

TrueExplorer::TrueExplorer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrueExplorer)
    ,dir(QDir::rootPath())
{
    ui->setupUi(this);
    indexinghandler::checkAndInitializeIndexing();
    startFileMonitoringProcess();
    QFileIconProvider iconProvider;
    IconSetup();
    ui->nameSortRadioButton->setChecked(true);
    ui->treeWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    populateDrives();

    connect(ui->driveTable, &QTableWidget::cellClicked,
            this, &TrueExplorer::onDriveClicked);

    connect(ui->nameSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->timeSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->sizeSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->extensionSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->barGraphRadioButton, &QRadioButton::clicked, this, [this]() {
        if (!ui->sizeSortRadioButton->isChecked())
            ui->sizeSortRadioButton->setChecked(true);
        reloadDirectory();
    });
    loadDirectory(dir.path());


}

TrueExplorer::~TrueExplorer()
{
    delete ui;
}

void TrueExplorer::updateBreadcrumbs(const QString &path)
{
    QLayout *layout = ui->breadcrumbWidget->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        delete item->widget(); // Delete the widget
        delete item; // Delete the layout item
    }

    // qDebug() << "Path to split: " << path;
    QString normalizedPath = path;
    if (!normalizedPath.endsWith("/")) {
        normalizedPath += "/";
    }
    normalizedPath.replace("\\", "/");
    // qDebug() << "After replacing : " << normalizedPath;
    QString separator = QDir::separator();
    // qDebug() << "Separator is" << separator;
    QStringList pathComponents = normalizedPath.split("/", Qt::SkipEmptyParts);
    layout->setAlignment(Qt::AlignLeft);
    // qDebug() << "Path components after split: " << pathComponents;


    if (pathComponents.isEmpty()) {
        qDebug() << "Failed to split the path correctly.";
        return;
    }


    QString cumulativePath;
    for (int i = 0; i < pathComponents.size(); ++i) {
        cumulativePath += (i > 0 ? separator : "") + pathComponents[i];


        QPushButton *breadcrumbButton = new QPushButton(pathComponents[i]);
        breadcrumbButton->setFlat(true);
        breadcrumbButton->setStyleSheet("text-decoration: underline; color: white;");


        connect(breadcrumbButton, &QPushButton::clicked, this, [this, cumulativePath]() {
            this->loadDirectory(cumulativePath);
        });


        layout->addWidget(breadcrumbButton);


        if (i < pathComponents.size() - 1) {
            QLabel *separatorLabel = new QLabel(">");
            layout->addWidget(separatorLabel);
        }
    }


    ui->breadcrumbWidget->update();
}



void TrueExplorer::loadDirectory(const QString &path) {
    qDebug() << "Loading directory:" << path;

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString favouritesPath = appDataPath + "/favourites.txt";
    QString recentFilesPath = appDataPath + "/recentfiles.txt";

    if (path == favouritesPath || path == recentFilesPath) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open file:" << path;
            return;
        }

        ui->treeWidget_2->clear();
        ui->treeWidget_2->setColumnCount(3);
        ui->treeWidget_2->setHeaderLabels(QStringList() << "Name" << "Size" << "Last Modified");
        ui->treeWidget_2->setColumnWidth(0, 300);
        updateBreadcrumbs(path);

        QTextStream in(&file);
        QFileIconProvider iconProvider;
        QStringList lines;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) lines.append(line);
        }

        std::reverse(lines.begin(), lines.end());

        for (const QString &line : lines) {
            QFileInfo fileInfo(line);
            if (!fileInfo.exists()) continue;

            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_2);
            item->setText(0, fileInfo.fileName());
            item->setIcon(0, iconProvider.icon(fileInfo));
            item->setData(0, Qt::UserRole, fileInfo.absoluteFilePath());
            item->setText(1, fileInfo.isDir() ? "-" : QLocale().formattedDataSize(fileInfo.size()));
            item->setText(2, fileInfo.lastModified().toString("yyyy-MM-dd hh:mm"));
        }

        file.close();
        return;
    }

    dir.setPath(path);
    if (historyIndex == -1 || !directoryHistory.contains(path)) {
        directoryHistory.append(path);
        if (directoryHistory.size() > 20) directoryHistory.removeFirst();
        historyIndex = directoryHistory.size() - 1;
    }

    qDebug() << directoryHistory;

    ui->treeWidget_2->clear();
    ui->treeWidget_2->setColumnCount(3);
    ui->treeWidget_2->setHeaderLabels(QStringList() << "Name" << "Size" << "Last Modified");
    ui->treeWidget_2->setColumnWidth(0, 300);

    QDir dir(path);
    if (!dir.exists()) return;

    updateBreadcrumbs(path);
    QFileIconProvider iconProvider;

    QDir::SortFlags sortFlag = QDir::Name;
    if (ui->nameSortRadioButton->isChecked()) sortFlag = QDir::Name;
    else if (ui->timeSortRadioButton->isChecked()) sortFlag = QDir::Time;
    else if (ui->extensionSortRadioButton->isChecked()) sortFlag = QDir::Type;

    // Open SQLite DB
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/file_index.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IndexConnection");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Failed to open index database:" << db.lastError().text();
    }

    QSqlQuery query(db);
    QFileInfoList entries;

    // Manual size sort using DB
    if (ui->sizeSortRadioButton->isChecked()) {
        QFileInfoList rawEntries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden, QDir::Name);
        QVector<QPair<QFileInfo, qint64>> sizePairs;

        for (const QFileInfo &entry : rawEntries) {
            QString absPath = entry.absoluteFilePath();
            qint64 size = 0;

            if (entry.isDir()) {
                query.prepare("SELECT size FROM directories WHERE path = ?");
            } else {
                query.prepare("SELECT size FROM files WHERE path = ?");
            }

            query.addBindValue(absPath);
            if (query.exec() && query.next()) {
                size = query.value(0).toLongLong();
            } else {
                size = entry.size();  // fallback
            }

            sizePairs.append(qMakePair(entry, size));
        }

        std::sort(sizePairs.begin(), sizePairs.end(), [](const auto &a, const auto &b) {
            return a.second > b.second;  // Descending size
        });

        for (const auto &pair : sizePairs) {
            entries.append(pair.first);
        }
    } else {
        entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden, sortFlag);
    }

    qint64 maxSize = 1;
    QVector<QPair<QTreeWidgetItem*, qint64>> sizedItems;

    for (const QFileInfo &entry : entries) {
        QString absPath = entry.absoluteFilePath();
        qint64 size = 0;

        if (entry.isDir()) {
            query.prepare("SELECT size FROM directories WHERE path = ?");
        } else {
            query.prepare("SELECT size, modified FROM files WHERE path = ?");
        }

        query.addBindValue(absPath);
        QString modDate;
        if (query.exec() && query.next()) {
            size = query.value(0).toLongLong();
            if (!entry.isDir() && query.record().count() > 1)
                modDate = query.value(1).toString();
        } else {
            size = entry.size();
        }

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_2);
        item->setText(0, entry.fileName());
        item->setIcon(0, iconProvider.icon(entry));
        item->setData(0, Qt::UserRole, absPath);
        item->setText(1, QLocale().formattedDataSize(size));
        if (!entry.isDir())
            item->setText(2, !modDate.isEmpty() ? QDateTime::fromString(modDate, Qt::ISODate).toString("yyyy-MM-dd hh:mm")
                                                : entry.lastModified().toString("yyyy-MM-dd hh:mm"));
        else
            item->setText(2, "");

        sizedItems.append(qMakePair(item, size));
        if (size > maxSize) maxSize = size;
    }

    // Apply Bar Graph background if selected
    if (ui->barGraphRadioButton->isChecked()) {
        for (auto &pair : sizedItems) {
            QTreeWidgetItem *item = pair.first;
            qint64 size = pair.second;

            double ratio = static_cast<double>(size) / maxSize;
            int percent = static_cast<int>(ratio * 100);

            QLinearGradient gradient(0, 0, 1, 0);
            gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
            gradient.setColorAt(0, QColor("#3498db"));
            gradient.setColorAt(ratio, QColor("#3498db"));
            gradient.setColorAt(ratio + 0.001, QColor(53, 53, 53));  // Background fallback
            gradient.setColorAt(1, QColor(53, 53, 53));

            item->setBackground(0, QBrush(gradient));
        }
    }

    db.close();
    QSqlDatabase::removeDatabase("IndexConnection");
}



void TrueExplorer::on_treeWidget_2_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString filePath = item->data(0, Qt::UserRole).toString();
    QFileInfo fileInfo(filePath);

    if (fileInfo.isFile()) {
        QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(appDataPath); // Ensure directory exists
        QString recentFilePath = appDataPath + "/recentfiles.txt";

        // Read all existing entries
        QStringList lines;
        QFile readFile(recentFilePath);
        if (readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&readFile);
            while (!in.atEnd()) {
                QString line = in.readLine().trimmed();
                if (!line.isEmpty()) lines.append(line);
            }
            readFile.close();
        }

        // Append the new path (remove if already exists to avoid duplication)
        lines.removeAll(filePath);
        lines.append(filePath);

        // Keep only the last 30 entries
        while (lines.size() > 30)
            lines.removeFirst();

        // Write updated list back to file
        QFile writeFile(recentFilePath);
        if (writeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream out(&writeFile);
            for (const QString &line : lines)
                out << line << '\n';
            writeFile.close();
        }
    }

    // Navigate or open file
    if (fileInfo.isDir()) {
        loadDirectory(filePath);
    } else {
        QUrl fileUrl = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(fileUrl);
    }
}

void TrueExplorer::on_treeWidget_2_customContextMenuRequested(const QPoint &pos)
{
    QList<QTreeWidgetItem *> selectedItems = ui->treeWidget_2->selectedItems();
    if (selectedItems.isEmpty())
        return;

    QStringList filePaths;
    for (QTreeWidgetItem *item : selectedItems)
    {
        filePaths.append(item->data(0, Qt::UserRole).toString());
    }

    QMenu contextMenu(this);

    QAction *cutAction = new QAction("Cut", &contextMenu);
    QAction *copyAction = new QAction("Copy", &contextMenu);
    QAction *pasteAction = new QAction("Paste", &contextMenu);
    QAction *deleteAction = new QAction("Delete", &contextMenu);
    QAction *copyPathAction = new QAction("Copy Path", &contextMenu); // ← NEW ACTION
    QAction *addorRemoveFavourites = new QAction("Add/Remove Favourites", &contextMenu);
    QAction *viewProperties = new QAction("View Properties", &contextMenu);

    connect(cutAction, &QAction::triggered, this, [=]() {
        ContextMenuActions::cutFiles(clipboardPaths, cutMode, filePaths);
    });
    connect(copyAction, &QAction::triggered, this, [=]() {
        ContextMenuActions::copyFiles(clipboardPaths, cutMode, filePaths);
    });
    connect(pasteAction, &QAction::triggered, this, [=]() {
        QTreeWidgetItem *targetItem = selectedItems.first();
        QString targetDir = targetItem->data(0, Qt::UserRole).toString();
        if (!targetDir.isEmpty())
            ContextMenuActions::pasteFiles(clipboardPaths, cutMode, targetDir);
    });
    connect(deleteAction, &QAction::triggered, this, [=]() {
        ContextMenuActions::deleteFiles(filePaths);
    });
    connect(addorRemoveFavourites, &QAction::triggered, this, [=]() {
        ContextMenuActions::addorRemoveFavourites(filePaths);
    });
    connect(viewProperties, &QAction::triggered, this, [=]() {
        ContextMenuActions::viewProperties(filePaths);
    });

    // 🔗 Connect Copy Path
    connect(copyPathAction, &QAction::triggered, this, [=]() {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(filePaths.join("\n"));
    });

    // Add actions to context menu
    contextMenu.addAction(cutAction);
    contextMenu.addAction(copyAction);
    contextMenu.addAction(pasteAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(copyPathAction);
    contextMenu.addAction(addorRemoveFavourites);
    contextMenu.addAction(viewProperties);

    contextMenu.exec(ui->treeWidget_2->mapToGlobal(pos));
}


void TrueExplorer::performSearch() {
    QString searchText = ui->searchLineEdit->toPlainText().trimmed();
    if (searchText.isEmpty()) return;

    qDebug() << "Search Text: " << searchText;

    bool searchInCurrentDir = ui->currentDirRadioButton->isChecked();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/file_index.db");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return;
    }

    QSqlQuery query;

    if (searchInCurrentDir) {
        QString currentDirPath = dir.absolutePath();
        qDebug() << "Searching in current directory: " << currentDirPath;

        query.prepare("SELECT file_name, path, size FROM files WHERE file_name LIKE ? AND path LIKE ?");
        query.addBindValue("%" + searchText + "%");
        query.addBindValue(currentDirPath + "/%");  // match subfiles
    } else {
        query.prepare("SELECT file_name, path, size FROM files WHERE file_name LIKE ?");
        query.addBindValue("%" + searchText + "%");
    }

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    populateTreeWidget(query);
}



void TrueExplorer::populateTreeWidget(QSqlQuery &query) {
    ui->treeWidget_2->clear();  // Clear previous results

    ui->treeWidget_2->setColumnCount(1);
    ui->treeWidget_2->setHeaderLabel("Name");

    QFileIconProvider iconProvider;

    while (query.next()) {
        QString name = query.value(0).toString();
        QString path = query.value(1).toString();
        qint64 size = query.value(2).toLongLong();  // Convert to qint64 for proper size representation

        QFileInfo fileInfo(path);

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_2);
        item->setText(0, name);
        item->setIcon(0, iconProvider.icon(fileInfo)); // Assign appropriate file/folder icon
        item->setData(0, Qt::UserRole, path); // Store full path for reference

        ui->treeWidget_2->addTopLevelItem(item);
    }
}


void TrueExplorer::testFunction(){
    std::cout << "Test Function Invoked!" << std::endl;
}

void TrueExplorer::keyPressEvent(QKeyEvent *event) {
    QList<QTreeWidgetItem *> selectedItems = ui->treeWidget_2->selectedItems();
    QStringList filePaths;
    for (QTreeWidgetItem *item : selectedItems) {
        filePaths.append(item->data(0, Qt::UserRole).toString());
    }

    if (event->matches(QKeySequence::Copy)) {
        if (!filePaths.isEmpty())
            ContextMenuActions::copyFiles(clipboardPaths, cutMode, filePaths);

    } else if (event->matches(QKeySequence::Cut)) {
        if (!filePaths.isEmpty())
            ContextMenuActions::cutFiles(clipboardPaths, cutMode, filePaths);

    } else if (event->matches(QKeySequence::Paste)) {
        QTreeWidgetItem *targetItem = ui->treeWidget_2->currentItem();
        if (targetItem) {
            QString targetDir = targetItem->data(0, Qt::UserRole).toString();
            if (!targetDir.isEmpty())
                ContextMenuActions::pasteFiles(clipboardPaths, cutMode, targetDir);
        }

    } else if (event->key() == Qt::Key_Delete) {
        if (!filePaths.isEmpty())
            ContextMenuActions::deleteFiles(filePaths);

    } else {
        QMainWindow::keyPressEvent(event);  // Forward to base class
    }
}


void TrueExplorer::on_prevDirectoryButton_clicked()
{
    if (dir.cdUp()) {
        TrueExplorer::loadDirectory(dir.absolutePath());
    } else {
        QMessageBox::warning(this, "Error", "Already at the root directory!");
    }
}

void TrueExplorer::on_newFileButton_clicked()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, "Create New File",
                                             "Enter file name:", QLineEdit::Normal,
                                             "NewFile.txt", &ok);

    if (!ok || fileName.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid file name.");
        return;
    }

    QString invalidChars = "\\/:*?\"<>|";
    for (QChar ch : invalidChars) {
        if (fileName.contains(ch)) {
            QMessageBox::warning(this, "Error", "File name contains invalid characters.");
            return;
        }
    }

    QString filePath = dir.absolutePath() + "/" + fileName;

    int count = 1;
    while (QFile::exists(filePath)) {
        filePath = dir.absolutePath() + QString("/%1(%2)").arg(fileName).arg(count++);
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "";  // Empty file
        file.close();

        // Refresh directory view to reflect the new file
        loadDirectory(dir.absolutePath());
    } else {
        QMessageBox::warning(this, "Error", "Failed to create file.");
    }
}

void TrueExplorer::renameSelectedItem()
{
     QTreeWidgetItem *item = ui->treeWidget_2->currentItem();
    if (!item) return;

    QString oldName = item->text(0);
    QString oldPath = dir.absoluteFilePath(oldName);

    bool ok;
    QString newName = QInputDialog::getText(this, "Rename File",
                                            "Enter new file name:", QLineEdit::Normal,
                                            oldName, &ok);

    if (!ok || newName.trimmed().isEmpty()) return;

    QString newPath = dir.absoluteFilePath(newName);

    if (QFile::rename(oldPath, newPath)) {
        item->setText(0, newName);
    } else {
        QMessageBox::warning(this, "Error", "Failed to rename file.");
    }
}




void TrueExplorer::on_newFolderButton_clicked()
{
    bool ok;
    QString folderName = QInputDialog::getText(this, "Create New Folder",
                                               "Enter folder name:", QLineEdit::Normal,
                                               "NewFolder", &ok);

    if (!ok || folderName.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid folder name.");
        return;
    }

    QString invalidChars = "\\/:*?\"<>|";
    for (QChar ch : invalidChars) {
        if (folderName.contains(ch)) {
            QMessageBox::warning(this, "Error", "Folder name contains invalid characters.");
            return;
        }
    }

    QString folderPath = dir.absolutePath() + "/" + folderName;

    int count = 1;
    while (QDir(folderPath).exists()) {
        folderPath = dir.absolutePath() + QString("/%1(%2)").arg(folderName).arg(count++);
    }

    QDir dirInstance;
    if (dirInstance.mkdir(folderPath)) {
        loadDirectory(dir.absolutePath());
    } else {
        QMessageBox::warning(this, "Error", "Failed to create folder.");
    }
}


void TrueExplorer::on_reloadButton_clicked()
{
    loadDirectory(dir.absolutePath());
}


void TrueExplorer::reloadDirectory()
{
    loadDirectory(dir.absolutePath());
}

void TrueExplorer::IconSetup() {
    if (!ui) return; // Prevent crashes if UI is null

    QIcon newFileButtonIcon(":/images/images/new_file.png");
    QIcon newFolderButtonIcon(":/images/images/new_folder.png");
    QIcon settingButtonIcon(":/images/images/settings.png");
    QIcon quickAccess(":/images/images/quick_access_icon.png");
    QIcon favoritesIcon(":/images/images/star.png");

    ui->newFileButton->setIcon(newFileButtonIcon);
    ui->newFileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->newFileButton->setIconSize(QSize(70, 70));

    ui->newFolderButton->setIcon(newFolderButtonIcon);
    ui->newFolderButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->newFolderButton->setIconSize(QSize(70, 70));

    ui->viewIndexToolButton->setIcon(newFileButtonIcon);
    ui->viewIndexToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->viewIndexToolButton->setIconSize(QSize(70, 70));

    ui->recentFilesButton->setIcon(quickAccess);

    ui->favoritesButton->setIcon(favoritesIcon);

    ui->prevFolderButton->setIcon(QIcon(":/images/images/back_arrow.png"));
    ui->nextFolderButton->setIcon(QIcon(":/images/images/foward_arrow.png"));
    ui->prevDirectoryButton->setIcon(QIcon(":/images/images/up_arrow.png"));
    ui->reloadButton->setIcon(QIcon(":/images/images/reload.png"));
}


void TrueExplorer::on_prevFolderButton_clicked()
{
    if (historyIndex > 0) {
        historyIndex--;
        loadDirectory(directoryHistory[historyIndex]);
    }
}

void TrueExplorer::on_nextFolderButton_clicked()
{
    if (historyIndex < directoryHistory.size() - 1) {
        historyIndex++;
        loadDirectory(directoryHistory[historyIndex]);
    }
}


void TrueExplorer::on_searchButton_clicked()
{
    performSearch();
}


void TrueExplorer::on_searchLineEdit_textChanged()
{
    performSearch();
}

void TrueExplorer::populateDrives() {
    QFileInfoList driveList = dir.drives();

    ui->driveTable->setRowCount(driveList.size());
    ui->driveTable->setColumnCount(1);
    ui->driveTable->setHorizontalHeaderLabels(QStringList() << "Drives:");

    for (int i = 0; i < driveList.size(); ++i) {
        QString drivePath = driveList[i].absoluteFilePath();

        // Create item with icon and text
        QTableWidgetItem *item = new QTableWidgetItem(drivePath);
        item->setIcon(QIcon::fromTheme("drive-harddisk")); // Or use custom icon
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);  // Read-only

        ui->driveTable->setItem(i, 0, item);
    }

    // Layout tweaks
    ui->driveTable->horizontalHeader()->setStretchLastSection(true);
    ui->driveTable->verticalHeader()->setVisible(false);
    ui->driveTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void TrueExplorer::onDriveClicked(int row, int column) {
    QTableWidgetItem *item = ui->driveTable->item(row, column);
    if (item) {
        QString drivePath = item->text();
        loadDirectory(drivePath); // 🔄 Pass the path
    }
}

void TrueExplorer::on_favoritesButton_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/favourites.txt";
    loadDirectory(filePath);
}


void TrueExplorer::on_viewIndexToolButton_clicked()
{
    /* QString filePath = QStandardPaths::AppDataLocation + "/file_index.db";*/ // Change this to your actual file path
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/file_index.db";

    if (!QFile::exists(filePath)) {
        QMessageBox::warning(this, "File Not Found", "The specified database file was not found.");
        return;
    }

    databaseviewer *viewer = new databaseviewer(filePath, this);
    viewer->exec(); // or viewer->show(); for modeless window
}


void TrueExplorer::on_recentFilesButton_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/recentfiles.txt";
    loadDirectory(filePath);
}


void TrueExplorer::startFileMonitoringProcess() {
    QString exePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/monitor.exe";

    // Start the process in detached mode
    bool success = QProcess::startDetached(exePath);

    if (success) {
        qDebug() << "Detached process started successfully.";
    } else {
        qDebug() << "Failed to start detached process.";
    }
}

