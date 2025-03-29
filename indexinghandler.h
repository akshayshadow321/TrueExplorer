#ifndef INDEXINGHANDLER_H
#define INDEXINGHANDLER_H

#include <QString>
#include <qdir.h>
#include <qsqlquery.h>

class indexinghandler
{
// private:
//     QDir dir;
public:
    indexinghandler();
    static void checkAndInitializeIndexing();
    static void performIndexing();
    static void scanAndStoreFiles(const QString &directoryPath);
    static qint64 getDirectorySize(const QString &directoryPath);
    static void recurisveSelectiveFolderFunc(const QString &directoryPath, QSqlQuery &query,int counter);
};

#endif // INDEXINGHANDLER_H
