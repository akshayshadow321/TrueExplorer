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

TrueExplorer::TrueExplorer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrueExplorer)
    // ,dir(QDir::rootPath())
{
    ui->setupUi(this);
    QFileIconProvider iconProvider;
    IconSetup();
    ui->nameSortRadioButton->setChecked(true);
    ui->listViewRadioButton->setChecked(true);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    dir.setPath("C:/Users/aksha/Projects/temp_folder");

    connect(ui->nameSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->timeSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->sizeSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->extensionSortRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->tileViewRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);
    connect(ui->listViewRadioButton, &QRadioButton::clicked, this, &TrueExplorer::reloadDirectory);


    loadDirectory(dir.path());

}

TrueExplorer::~TrueExplorer()
{
    delete ui;
}

void TrueExplorer::updateBreadcrumbs(const QString &path) {
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
    // if (path.isEmpty() || path == dir.path()) return;

    qDebug() << "Loading directory:" << path;
    dir.setPath(path);
    if (historyIndex == -1 || !directoryHistory.contains(path)) {
        if (historyIndex < directoryHistory.size() - 1) {
            // If navigating after going Back, trim the forward history
            directoryHistory = directoryHistory.mid(0, historyIndex + 1);
        }
        directoryHistory.append(path);
        if (directoryHistory.size() > 10) {
            directoryHistory.removeFirst();  // Keep only the last 10 entries
        }

        historyIndex = directoryHistory.size() - 1;
    }

    qDebug() << directoryHistory;
    // Clear and setup treeWidget
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Name");

    QDir dir(path);
    if (!dir.exists()) return;

    // Handle tile view mode
    if (ui->tileViewRadioButton->isChecked()) {
        ui->treeWidget->setHeaderHidden(true);
        ui->treeWidget->setRootIsDecorated(false);
        ui->treeWidget->setIconSize(QSize(64, 64));
    }

    updateBreadcrumbs(path);
    QFileIconProvider iconProvider;

    // Sorting logic
    QDir::SortFlags sortFlag = QDir::Name;
    if (ui->nameSortRadioButton->isChecked()) {
        sortFlag = QDir::Name;
    } else if (ui->timeSortRadioButton->isChecked()) {
        sortFlag = QDir::Time;
    } else if (ui->sizeSortRadioButton->isChecked()) {
        sortFlag = QDir::Size;
    } else if (ui->extensionSortRadioButton->isChecked()) {
        sortFlag = QDir::Type;
    }

    // Load directory items
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, sortFlag);
    for (const QFileInfo &entry : entries) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, entry.fileName());
        item->setIcon(0, iconProvider.icon(entry));
        item->setData(0, Qt::UserRole, entry.absoluteFilePath());
    }
}


void TrueExplorer::testFunction(){
    std::cout << "Test Function Invoked!" << std::endl;
}

void TrueExplorer::keyPressEvent(QKeyEvent *event) {
    if (event->matches(QKeySequence::Copy)) {
        copySelectedItems();
    } else if (event->matches(QKeySequence::Cut)) {
        cutSelectedItems();
    } else if (event->matches(QKeySequence::Paste)) {
        pasteItems();
    } else if (event->key() == Qt::Key_Delete) {
        deleteSelectedItems();
    } else {
        QMainWindow::keyPressEvent(event);  // Pass other key events to parent
    }
}

void TrueExplorer::copySelectedItems() {
    clipboardPaths.clear();
    for (QTreeWidgetItem *item : ui->treeWidget->selectedItems()) {
        QString filePath = item->data(0, Qt::UserRole).toString();
        clipboardPaths.append(filePath);
    }
    cutMode = false;  // Mark as copied, not cut
}

void TrueExplorer::cutSelectedItems() {
    clipboardPaths.clear();
    for (QTreeWidgetItem *item : ui->treeWidget->selectedItems()) {
        clipboardPaths.append(item->data(0, Qt::UserRole).toString());
    }
    cutMode = true;
}


void TrueExplorer::pasteItems() {
    if (clipboardPaths.isEmpty()) return;

    for (const QString &srcPath : clipboardPaths) {
        QFileInfo fileInfo(srcPath);
        QString destPath = dir.absolutePath() + "/" + fileInfo.fileName();

        // Handle duplicate filenames
        int count = 1;
        while (QFile::exists(destPath) || QDir(destPath).exists()) {
            destPath = dir.absolutePath() + QString("/%1_copy%2.%3")
            .arg(fileInfo.completeBaseName())
                .arg(count++)
                .arg(fileInfo.suffix());
        }

        if (fileInfo.isDir()) {
            // Copy/Move a directory
            QDir sourceDir(srcPath);
            QDir targetDir(destPath);

            if (sourceDir.exists()) {
                if (copyDirectory(srcPath, destPath)) {
                    qDebug() << "Copied Folder:" << srcPath << "->" << destPath;
                    if (cutMode) sourceDir.removeRecursively();
                } else {
                    QMessageBox::warning(this, "Error", "Failed to copy folder: " + srcPath);
                }
            }
        } else {
            // Copy/Move a file
            if (cutMode) {
                if (QFile::rename(srcPath, destPath)) {
                    qDebug() << "Moved:" << srcPath << "->" << destPath;
                } else {
                    QMessageBox::warning(this, "Error", "Failed to move " + srcPath);
                }
            } else {
                if (QFile::copy(srcPath, destPath)) {
                    qDebug() << "Copied:" << srcPath << "->" << destPath;
                } else {
                    QMessageBox::warning(this, "Error", "Failed to copy " + srcPath);
                }
            }
        }
    }

    // Clear clipboard if cut
    if (cutMode) clipboardPaths.clear();

    // Reload UI
    loadDirectory(dir.absolutePath());
}

void TrueExplorer::deleteSelectedItems() {
    QList<QTreeWidgetItem*> selectedItems = ui->treeWidget->selectedItems();
    if (selectedItems.isEmpty()) return;

    if (QMessageBox::question(this, "Delete", "Are you sure?") == QMessageBox::Yes) {
        for (QTreeWidgetItem *item : selectedItems) {
            QString filePath = item->data(0, Qt::UserRole).toString();
            QFile file(filePath);
            if (file.exists() && !file.remove()) {
                QMessageBox::warning(this, "Error", "Failed to delete " + filePath);
            }
            delete item;  // Remove from UI
        }
    }
}

bool TrueExplorer::copyDirectory(const QString &source, const QString &destination) {
    QDir sourceDir(source);
    if (!sourceDir.exists()) return false;

    QDir destinationDir(destination);
    if (!destinationDir.exists()) {
        if (!destinationDir.mkpath(destination)) return false;
    }

    QStringList files = sourceDir.entryList(QDir::Files);
    for (const QString &file : files) {
        QString srcFilePath = source + "/" + file;
        QString destFilePath = destination + "/" + file;
        if (!QFile::copy(srcFilePath, destFilePath)) return false;
    }

    QStringList subDirs = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subDir : subDirs) {
        QString srcSubDirPath = source + "/" + subDir;
        QString destSubDirPath = destination + "/" + subDir;
        if (!copyDirectory(srcSubDirPath, destSubDirPath)) return false;
    }

    return true;
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
     QTreeWidgetItem *item = ui->treeWidget->currentItem();
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

void TrueExplorer::deleteSelectedItem() {
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (!item) return;

    QString filePath = item->data(0, Qt::UserRole).toString();
    QFileInfo fileInfo(filePath);

    if (QMessageBox::question(this, "Delete", "Are you sure you want to delete this?") == QMessageBox::Yes) {
        bool success = false;

        if (fileInfo.isDir()) {
            QDir dir(filePath);
            success = deleteFolderContents(dir); // Custom function to remove contents
            if (success) {
                success = dir.rmdir(filePath); // Remove empty folder
            }
        } else {
            success = QFile::remove(filePath); // Remove file
        }

        if (success) {
            delete item; // Remove from UI
            qDebug() << "Deleted:" << filePath;
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete " + filePath);
        }
    }
}

bool TrueExplorer::deleteFolderContents(QDir &dir) {
    bool success = true;

    // Get all entries inside the folder
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            QDir subDir(entry.filePath());
            success = deleteFolderContents(subDir) && subDir.rmdir(entry.filePath());
        } else {
            success = QFile::remove(entry.filePath());
        }

        if (!success) break;
    }

    return success;
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

void TrueExplorer::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString filePath = item->data(0, Qt::UserRole).toString();
    QFileInfo fileInfo(filePath);
    if (fileInfo.isDir()) {
        loadDirectory(filePath);
    } else {
        QUrl fileUrl = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(fileUrl);
    }
}


void TrueExplorer::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QList<QTreeWidgetItem *> selectedItems = ui->treeWidget->selectedItems();
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
    QAction *addToFavourites = new QAction("Add to Favourites", &contextMenu);
    QAction *viewProperties = new QAction("View Properties", &contextMenu);

    connect(cutAction, &QAction::triggered, this, [=]() { ContextMenuActions::cutFiles(clipboardPaths, cutMode, filePaths); });
    connect(copyAction, &QAction::triggered, this, [=]() { ContextMenuActions::copyFiles(clipboardPaths, cutMode, filePaths); });
    connect(pasteAction, &QAction::triggered, this, [=]() {
        QTreeWidgetItem *targetItem = selectedItems.first();
        QString targetDir = targetItem->data(0, Qt::UserRole).toString();
        if (!targetDir.isEmpty()) ContextMenuActions::pasteFiles(clipboardPaths, cutMode, targetDir);
    });
    connect(deleteAction, &QAction::triggered, this, [=]() { ContextMenuActions::deleteFiles(filePaths); });
    connect(addToFavourites, &QAction::triggered, this, [=]() { ContextMenuActions::addToFavourites(filePaths); });
    connect(viewProperties, &QAction::triggered, this, [=]() { ContextMenuActions::viewProperties(filePaths); });

    contextMenu.addAction(cutAction);
    contextMenu.addAction(copyAction);
    contextMenu.addAction(pasteAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(addToFavourites);
    contextMenu.addAction(viewProperties);

    contextMenu.exec(ui->treeWidget->mapToGlobal(pos));
}

void TrueExplorer::IconSetup() {
    if (!ui) return; // Prevent crashes if UI is null

    QIcon newFileButtonIcon(":/images/images/new_file.png");
    QIcon newFolderButtonIcon(":/images/images/new_folder.png");
    QIcon settingButtonIcon(":/images/images/settings.png");

    ui->newFileButton->setIcon(newFileButtonIcon);
    ui->newFileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->newFileButton->setIconSize(QSize(70, 70));

    ui->newFolderButton->setIcon(newFolderButtonIcon);
    ui->newFolderButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->newFolderButton->setIconSize(QSize(70, 70));

    ui->viewIndexToolButton->setIcon(newFileButtonIcon);
    ui->viewIndexToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->viewIndexToolButton->setIconSize(QSize(70, 70));

    ui->settingsToolButton->setIcon(settingButtonIcon);
    ui->settingsToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->settingsToolButton->setIconSize(QSize(70, 70));

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

