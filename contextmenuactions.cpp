#include "contextmenuactions.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
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
    qDebug() << filePaths;
    if (filePaths.isEmpty()) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        nullptr, "Delete Files", "Are you sure you want to delete the selected items?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        for (const QString &filePath : filePaths)
        {
            QFileInfo info(filePath);
            if (info.isDir())
            {
                QDir dir(filePath);
                if (dir.removeRecursively())
                    qDebug() << "Deleted directory: " << filePath;
                else
                    qWarning() << "Failed to delete directory: " << filePath;
            }
            else if (info.isFile())
            {
                QFile file(filePath);
                if (file.remove())
                    qDebug() << "Deleted file: " << filePath;
                else
                    qWarning() << "Failed to delete file: " << filePath;
            }
        }
    }
}


// Add to Favourites
void ContextMenuActions::addorRemoveFavourites(const QStringList &filePaths)
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

    // Read existing favorites
    QStringList existingFavorites;
    QFile readFile(favFile);
    if (readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&readFile);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                existingFavorites.append(line);
            }
        }
        readFile.close();
    }

    // Toggle favorite status
    QSet<QString> favSet(existingFavorites.begin(), existingFavorites.end());
    QStringList added, removed;

    for (const QString &filePath : filePaths) {
        if (favSet.contains(filePath)) {
            favSet.remove(filePath);
            removed.append(filePath);
            qDebug() << "Removed from favourites: " << filePath;
        } else {
            favSet.insert(filePath);
            added.append(filePath);
            qDebug() << "Added to favourites: " << filePath;
        }
    }

    // Write updated favorites
    QFile writeFile(favFile);
    if (writeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&writeFile);
        for (const QString &fav : favSet) {
            out << fav << "\n";
        }
        writeFile.close();
    } else {
        qDebug() << "Failed to write to file: " << favFile << " Error: " << writeFile.errorString();
        return;
    }

    // Notify user with a pop-up
    QString message;
    if (!added.isEmpty()) {
        message += "Added to Favourites:\n" + added.join("\n") + "\n\n";
    }
    if (!removed.isEmpty()) {
        message += "Removed from Favourites:\n" + removed.join("\n");
    }

    if (!message.isEmpty()) {
        QMessageBox::information(nullptr, "Favourites Updated", message.trimmed());
    }
}


void ContextMenuActions::viewProperties(const QStringList &filePaths) {
    if (filePaths.isEmpty()) return;

    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/file_index.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "ViewPropsConnection");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Failed to open DB: " << db.lastError().text();
        return;
    }

    QString message;

    for (const QString &path : filePaths) {
        QFileInfo info(path);
        QString fileName = info.fileName();
        QString created = info.birthTime().isValid() ? info.birthTime().toString(Qt::ISODate) : "Unavailable";

        QSqlQuery query(db);
        QString sizeStr = "Unknown";
        QString modified;

        if (info.isDir()) {
            query.prepare("SELECT size FROM directories WHERE path = ?");
            query.addBindValue(path);
            if (query.exec() && query.next()) {
                qint64 size = query.value(0).toLongLong();
                sizeStr = QString::number(size / 1024.0, 'f', 2) + " KB";
            }
        } else {
            query.prepare("SELECT size, modified FROM files WHERE path = ?");
            query.addBindValue(path);
            if (query.exec() && query.next()) {
                qint64 size = query.value(0).toLongLong();
                sizeStr = QString::number(size / 1024.0, 'f', 2) + " KB";
                modified = query.value(1).toString();
            }
        }

        message += QString("Name: %1\nPath: %2\nSize: %3\nCreated: %4\n")
                       .arg(fileName, path, sizeStr, created);

        if (!modified.isEmpty()) {
            message += "Modified: " + modified + "\n";
        }

        message += "\n";
    }

    db.close();
    QSqlDatabase::removeDatabase("ViewPropsConnection");

    QMessageBox msgBox;
    msgBox.setWindowTitle("File/Folder Properties");
    msgBox.setText(message.trimmed());
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

