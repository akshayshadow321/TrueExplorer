#ifndef CONTEXTMENUACTIONS_H
#define CONTEXTMENUACTIONS_H

#include <QStringList>

class ContextMenuActions
{
public:
    ContextMenuActions();
    static void cutFiles(QStringList &clipboardPaths, bool &cutMode, const QStringList &filePaths);
    static void copyFiles(QStringList &clipboardPaths, bool &cutMode, const QStringList &filePaths);
    static void pasteFiles(QStringList &clipboardPaths, bool &cutMode, const QString &targetDir);
    static void deleteFiles(const QStringList &filePaths);
    static void addToFavourites(const QStringList &filePaths);
    static void viewProperties(const QStringList &filePaths);
};


#endif // CONTEXTMENUACTIONS_H
