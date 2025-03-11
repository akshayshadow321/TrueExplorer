#include "contextmenuactions.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>

ContextMenuActions::ContextMenuActions()
{

}

void ContextMenuActions::cutFiles(QStringList &clipboardPaths, bool &cutMode, const QStringList &filePaths)
{
    clipboardPaths = filePaths;
    cutMode = true;
    qDebug() << "Cut: " << clipboardPaths;
}

// Copy Files
void ContextMenuActions::copyFiles(QStringList &clipboardPaths, bool &cutMode, const QStringList &filePaths)
{
    clipboardPaths = filePaths;
    cutMode = false;
    qDebug() << "Copied: " << clipboardPaths;
}

// Paste Files
void ContextMenuActions::pasteFiles(QStringList &clipboardPaths, bool &cutMode, const QString &targetDir)
{
    if (clipboardPaths.isEmpty() || targetDir.isEmpty()) return;

    for (const QString &filePath : clipboardPaths)
    {
        QFileInfo fileInfo(filePath);
        QString newFilePath = targetDir + "/" + fileInfo.fileName();

        if (cutMode)
        {
            QFile::rename(filePath, newFilePath);
            qDebug() << "Moved file to: " << newFilePath;
        }
        else
        {
            QFile::copy(filePath, newFilePath);
            qDebug() << "Copied file to: " << newFilePath;
        }
    }

    if (cutMode)
    {
        clipboardPaths.clear();
        cutMode = false;
    }
}

// Delete Files
void ContextMenuActions::deleteFiles(const QStringList &filePaths)
{
    if (filePaths.isEmpty()) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        nullptr, "Delete Files", "Are you sure you want to delete these files?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        for (const QString &filePath : filePaths)
        {
            QFile file(filePath);
            if (file.exists())
            {
                file.remove();
                qDebug() << "Deleted file: " << filePath;
            }
        }
    }
}

// Add to Favourites
void ContextMenuActions::addToFavourites(const QStringList &filePaths)
{
    if (filePaths.isEmpty()) {
        qDebug() << "empty";
        return;
    }

    QString favDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString favFile = favDir + "/favourites.txt";

    // Ensure the directory exists
    QDir dir(favDir);
    if (!dir.exists()) {
        if (!dir.mkpath(favDir)) {
            qDebug() << "Failed to create directory: " << favDir;
            return;
        }
    }

    QFile file(favFile);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        for (const QString &filePath : filePaths)
        {
            out << filePath << "\n";
            qDebug() << "Added to favourites: " << filePath;
        }
        file.close();
    }
    else
    {
        qDebug() << "Failed to open file: " << favFile << " Error: " << file.errorString();
    }
}
// View Properties
void ContextMenuActions::viewProperties(const QStringList &filePaths)
{
    if (filePaths.isEmpty()) return;

    QString details;
    for (const QString &filePath : filePaths)
    {
        QFileInfo fileInfo(filePath);
        details += QString("File: %1\nSize: %2 bytes\nCreated: %3\nModified: %4\n\n")
                       .arg(fileInfo.fileName())
                       .arg(fileInfo.size())
                       .arg(fileInfo.birthTime().toString())
                       .arg(fileInfo.lastModified().toString());
    }

    QMessageBox::information(nullptr, "File Properties", details);
}
