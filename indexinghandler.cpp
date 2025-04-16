#include "indexinghandler.h"
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>
#include <qprocess.h>

void indexinghandler::checkAndInitializeIndexing() {
    QString flagFilePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/indexing_flag.txt";
    QFile flagFile(flagFilePath);
    if (!flagFile.exists()) {
        flagFile.open(QIODevice::WriteOnly);
        qDebug() << "Indexing not found. Running initial scan...";
        performIndexing();
        flagFile.write("indexed");
        flagFile.close();
    } else {
        qDebug() << "Index already exists. Skipping indexing.";
    }
}

void indexinghandler::performIndexing() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/file_index.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS files ("
               "id INTEGER PRIMARY KEY, "
               "path TEXT, "
               "file_name TEXT, "  // Added file_name field
               "size INTEGER, "
               "modified TEXT, "
               "type TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS directories ("
               "id INTEGER PRIMARY KEY, "
               "path TEXT, "
               "size INTEGER)");

    scanAndStoreFiles(QDir::rootPath()); // Modify path accordingly for Windows or Linux

    db.close();
}

void indexinghandler::scanAndStoreFiles(const QString &directoryPath) {
    QDir directory(directoryPath);

    // List of folders to exclude
    QStringList excludedFolders = {
        "node_modules", "venv", ".venv", "__pycache__", ".git", ".svn", ".hg",
        "build", "dist", "out", "target", "bin", "obj", ".gradle", ".idea", ".vs", ".vscode",
        "logs", "Windows", "System32", "SysWOW64", "Temp", "Library", "Application Support",
        "Trash", "Backup", "Old", "Cache", ".debug"
    };

    // List of file extensions to exclude
    QStringList excludedExtensions = {
        "tmp", "log", "cache", "bak", "swp", "dmp", "old",
        "sys", "dll", "drv", "dat", "ini", "cfg", "plist",
        "obj", "pdb", "o", "class", "pyc", "pyo", "lock", "out",
        "iso", "img", "vmdk", "vdi", "qcow2",
        "sdf", "mdf", "ldf", "thm", "msi", "apk", "deb", "rpm", "map", "bin", "cat", "inf.0", "vp", "so", "mo", "pm", "pl"
    };

    // List of directories where only subdirectories should be recorded
    QStringList allowedDirectoryParents = {
        "C:/Program Files",
        "C:/Program Files (x86)",
        "C:/Drivers",
        "C:/MinGW",
        "C:/Qt"
    };

    QSqlQuery query;
    query.prepare("INSERT INTO files (path, file_name, size, modified, type) VALUES (?, ?, ?, ?, ?)");

    foreach (const QFileInfo &file, directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        QString extension = file.suffix().toLower();
        if (excludedExtensions.contains(extension, Qt::CaseInsensitive)) {
            continue;
        }

        qDebug() << "Indexing: " << file.fileName();
        query.addBindValue(file.absoluteFilePath());
        query.addBindValue(file.fileName()); // Store file name separately
        query.addBindValue(file.size());
        query.addBindValue(file.lastModified().toString(Qt::ISODate));
        query.addBindValue(extension);
        query.exec();
    }

    // Store subdirectory records
    query.prepare("INSERT INTO directories (path, size) VALUES (?, ?)");
    foreach (const QFileInfo &subDir, directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QDir subDir_for_selective(subDir.absoluteFilePath());
        if (excludedFolders.contains(subDir.fileName(), Qt::CaseInsensitive)) {
            continue;
        }
        qint64 folderSize = getDirectorySize(subDir.absoluteFilePath());
        if (allowedDirectoryParents.contains(subDir.absoluteFilePath(), Qt::CaseInsensitive)) {
            recurisveSelectiveFolderFunc(subDir.absoluteFilePath(),query, 2);
            continue;
        }

        query.addBindValue(subDir.absoluteFilePath());
        query.addBindValue(folderSize);
        query.exec();

        scanAndStoreFiles(subDir.absoluteFilePath());  // Recursive call
    }
}

qint64 indexinghandler::getDirectorySize(const QString &directoryPath) {
    QProcess process;
    process.setProgram("powershell");
    process.setArguments({
        "-Command",
        QString("(Get-ChildItem -Path '%1' -Recurse | Measure-Object -Property Length -Sum).Sum").arg(directoryPath)
    });

    process.start();
    process.waitForFinished();

    QString output = process.readAllStandardOutput().trimmed();
    QString errorOutput = process.readAllStandardError().trimmed();

    if (!errorOutput.isEmpty()) {
        qDebug() << "PowerShell Error:" << errorOutput;
        return -1;
    }

    bool ok;
    qint64 size = output.toLongLong(&ok);
    if (!ok) {
        qDebug() << "Failed to parse directory size";
        return -1;
    }
    qDebug() << size;
    return size;
}

void indexinghandler::recurisveSelectiveFolderFunc(const QString &directoryPath, QSqlQuery &query, int counter) {
    if (counter <= 0) return;

    qDebug() << "Recursing into:" << directoryPath << " | Depth left:" << counter;

    QStringList excludedFolders = {
        "node_modules", "venv", ".venv", "__pycache__", ".git", ".svn", ".hg",
        "build", "dist", "out", "target", "bin", "obj", ".gradle", ".idea", ".vs", ".vscode",
        "logs", "Windows", "System32", "SysWOW64", "Temp", "Library", "Application Support",
        "Trash", "Backup", "Old", "Cache"
    };

    QDir dir(directoryPath);

    qint64 currentFolderSize = getDirectorySize(directoryPath);
    query.prepare("INSERT INTO directories (path, size) VALUES (?, ?)");
    query.addBindValue(directoryPath);
    query.addBindValue(currentFolderSize);
    if (!query.exec()) {
        qWarning() << "Failed to insert parent directory:" << query.lastError().text();
    }

    foreach (const QFileInfo &subDir, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        if (excludedFolders.contains(subDir.fileName(), Qt::CaseInsensitive)) {
            continue;
        }

        recurisveSelectiveFolderFunc(subDir.absoluteFilePath(), query, counter - 1);
    }
}


