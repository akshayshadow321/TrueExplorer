/********************************************************************************
** Form generated from reading UI file 'databaseviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEVIEWER_H
#define UI_DATABASEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_databaseviewer
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;

    void setupUi(QDialog *databaseviewer)
    {
        if (databaseviewer->objectName().isEmpty())
            databaseviewer->setObjectName("databaseviewer");
        databaseviewer->resize(400, 300);
        verticalLayout = new QVBoxLayout(databaseviewer);
        verticalLayout->setObjectName("verticalLayout");
        tableView = new QTableView(databaseviewer);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);


        retranslateUi(databaseviewer);

        QMetaObject::connectSlotsByName(databaseviewer);
    } // setupUi

    void retranslateUi(QDialog *databaseviewer)
    {
        databaseviewer->setWindowTitle(QCoreApplication::translate("databaseviewer", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class databaseviewer: public Ui_databaseviewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEVIEWER_H
