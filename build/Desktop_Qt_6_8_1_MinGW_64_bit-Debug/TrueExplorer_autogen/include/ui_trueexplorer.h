/********************************************************************************
** Form generated from reading UI file 'trueexplorer.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUEEXPLORER_H
#define UI_TRUEEXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrueExplorer
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *optionsBar;
    QHBoxLayout *horizontalLayout;
    QWidget *addItemLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *newFileButton;
    QFrame *line;
    QToolButton *newFolderButton;
    QFrame *line_3;
    QWidget *sortLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QRadioButton *nameSortRadioButton;
    QRadioButton *extensionSortRadioButton;
    QRadioButton *sizeSortRadioButton;
    QRadioButton *timeSortRadioButton;
    QLabel *label;
    QFrame *line_2;
    QWidget *searchOptionsLayout_2;
    QVBoxLayout *searchOptionsLayout;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *currentDirRadioButton;
    QRadioButton *filebaseRadioButton;
    QFrame *line_4;
    QWidget *graphicsLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *barGraphRadioButton;
    QSpacerItem *horizontalSpacer;
    QFrame *line_5;
    QWidget *optionsLayout;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *viewIndexToolButton;
    QFrame *line_6;
    QWidget *navbar;
    QHBoxLayout *horizontalLayout_6;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *prevFolderButton;
    QPushButton *nextFolderButton;
    QPushButton *prevDirectoryButton;
    QWidget *breadcrumbsLayout_2;
    QHBoxLayout *breadcrumbsLayout;
    QPushButton *reloadButton;
    QWidget *breadcrumbWidget;
    QHBoxLayout *horizontalLayout_9;
    QTextEdit *searchLineEdit;
    QPushButton *searchButton;
    QFrame *line_7;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_9;
    QPushButton *recentFilesButton;
    QPushButton *favoritesButton;
    QTableWidget *driveTable;
    QWidget *verticalWidget_3;
    QVBoxLayout *verticalLayout_8;
    QTreeWidget *treeWidget_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TrueExplorer)
    {
        if (TrueExplorer->objectName().isEmpty())
            TrueExplorer->setObjectName("TrueExplorer");
        TrueExplorer->resize(1054, 625);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TrueExplorer->sizePolicy().hasHeightForWidth());
        TrueExplorer->setSizePolicy(sizePolicy);
        TrueExplorer->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        TrueExplorer->setStyleSheet(QString::fromUtf8("background-color:#2C2C2C\n"
""));
        centralwidget = new QWidget(TrueExplorer);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        optionsBar = new QWidget(centralwidget);
        optionsBar->setObjectName("optionsBar");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(8);
        sizePolicy1.setHeightForWidth(optionsBar->sizePolicy().hasHeightForWidth());
        optionsBar->setSizePolicy(sizePolicy1);
        optionsBar->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 53, 53);"));
        horizontalLayout = new QHBoxLayout(optionsBar);
        horizontalLayout->setObjectName("horizontalLayout");
        addItemLayout = new QWidget(optionsBar);
        addItemLayout->setObjectName("addItemLayout");
        sizePolicy.setHeightForWidth(addItemLayout->sizePolicy().hasHeightForWidth());
        addItemLayout->setSizePolicy(sizePolicy);
        addItemLayout->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border: 0px 1px 0px 0px;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(addItemLayout);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newFileButton = new QToolButton(addItemLayout);
        newFileButton->setObjectName("newFileButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(newFileButton->sizePolicy().hasHeightForWidth());
        newFileButton->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(newFileButton);

        line = new QFrame(addItemLayout);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line);

        newFolderButton = new QToolButton(addItemLayout);
        newFolderButton->setObjectName("newFolderButton");
        newFolderButton->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        newFolderButton->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

        horizontalLayout_2->addWidget(newFolderButton);


        horizontalLayout->addWidget(addItemLayout);

        line_3 = new QFrame(optionsBar);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_3);

        sortLayout = new QWidget(optionsBar);
        sortLayout->setObjectName("sortLayout");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sortLayout->sizePolicy().hasHeightForWidth());
        sortLayout->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(sortLayout);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        nameSortRadioButton = new QRadioButton(sortLayout);
        nameSortRadioButton->setObjectName("nameSortRadioButton");

        gridLayout_2->addWidget(nameSortRadioButton, 1, 0, 1, 1);

        extensionSortRadioButton = new QRadioButton(sortLayout);
        extensionSortRadioButton->setObjectName("extensionSortRadioButton");

        gridLayout_2->addWidget(extensionSortRadioButton, 2, 1, 1, 1);

        sizeSortRadioButton = new QRadioButton(sortLayout);
        sizeSortRadioButton->setObjectName("sizeSortRadioButton");

        gridLayout_2->addWidget(sizeSortRadioButton, 2, 0, 1, 1);

        timeSortRadioButton = new QRadioButton(sortLayout);
        timeSortRadioButton->setObjectName("timeSortRadioButton");
        timeSortRadioButton->setEnabled(true);

        gridLayout_2->addWidget(timeSortRadioButton, 1, 1, 1, 1);

        label = new QLabel(sortLayout);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        horizontalLayout->addWidget(sortLayout);

        line_2 = new QFrame(optionsBar);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_2);

        searchOptionsLayout_2 = new QWidget(optionsBar);
        searchOptionsLayout_2->setObjectName("searchOptionsLayout_2");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(searchOptionsLayout_2->sizePolicy().hasHeightForWidth());
        searchOptionsLayout_2->setSizePolicy(sizePolicy4);
        searchOptionsLayout = new QVBoxLayout(searchOptionsLayout_2);
        searchOptionsLayout->setObjectName("searchOptionsLayout");
        label_2 = new QLabel(searchOptionsLayout_2);
        label_2->setObjectName("label_2");
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);

        searchOptionsLayout->addWidget(label_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        currentDirRadioButton = new QRadioButton(searchOptionsLayout_2);
        currentDirRadioButton->setObjectName("currentDirRadioButton");

        verticalLayout_3->addWidget(currentDirRadioButton);

        filebaseRadioButton = new QRadioButton(searchOptionsLayout_2);
        filebaseRadioButton->setObjectName("filebaseRadioButton");
        filebaseRadioButton->setChecked(true);

        verticalLayout_3->addWidget(filebaseRadioButton);


        searchOptionsLayout->addLayout(verticalLayout_3);


        horizontalLayout->addWidget(searchOptionsLayout_2);

        line_4 = new QFrame(optionsBar);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_4);

        graphicsLayout = new QWidget(optionsBar);
        graphicsLayout->setObjectName("graphicsLayout");
        sizePolicy3.setHeightForWidth(graphicsLayout->sizePolicy().hasHeightForWidth());
        graphicsLayout->setSizePolicy(sizePolicy3);
        verticalLayout_4 = new QVBoxLayout(graphicsLayout);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_3 = new QLabel(graphicsLayout);
        label_3->setObjectName("label_3");

        verticalLayout_4->addWidget(label_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        barGraphRadioButton = new QRadioButton(graphicsLayout);
        barGraphRadioButton->setObjectName("barGraphRadioButton");

        verticalLayout_6->addWidget(barGraphRadioButton);


        verticalLayout_4->addLayout(verticalLayout_6);


        horizontalLayout->addWidget(graphicsLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        line_5 = new QFrame(optionsBar);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::VLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_5);

        optionsLayout = new QWidget(optionsBar);
        optionsLayout->setObjectName("optionsLayout");
        optionsLayout->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border:0px;\n"
"}"));
        horizontalLayout_5 = new QHBoxLayout(optionsLayout);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        viewIndexToolButton = new QToolButton(optionsLayout);
        viewIndexToolButton->setObjectName("viewIndexToolButton");

        horizontalLayout_5->addWidget(viewIndexToolButton);

        line_6 = new QFrame(optionsLayout);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::VLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_5->addWidget(line_6);


        horizontalLayout->addWidget(optionsLayout);


        gridLayout->addWidget(optionsBar, 0, 0, 1, 1);

        navbar = new QWidget(centralwidget);
        navbar->setObjectName("navbar");
        sizePolicy3.setHeightForWidth(navbar->sizePolicy().hasHeightForWidth());
        navbar->setSizePolicy(sizePolicy3);
        navbar->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 53, 53);"));
        horizontalLayout_6 = new QHBoxLayout(navbar);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalWidget = new QWidget(navbar);
        horizontalWidget->setObjectName("horizontalWidget");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(horizontalWidget->sizePolicy().hasHeightForWidth());
        horizontalWidget->setSizePolicy(sizePolicy5);
        horizontalWidget->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border:0px;\n"
"}"));
        horizontalLayout_7 = new QHBoxLayout(horizontalWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        prevFolderButton = new QPushButton(horizontalWidget);
        prevFolderButton->setObjectName("prevFolderButton");

        horizontalLayout_7->addWidget(prevFolderButton);

        nextFolderButton = new QPushButton(horizontalWidget);
        nextFolderButton->setObjectName("nextFolderButton");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(nextFolderButton->sizePolicy().hasHeightForWidth());
        nextFolderButton->setSizePolicy(sizePolicy6);

        horizontalLayout_7->addWidget(nextFolderButton);

        prevDirectoryButton = new QPushButton(horizontalWidget);
        prevDirectoryButton->setObjectName("prevDirectoryButton");

        horizontalLayout_7->addWidget(prevDirectoryButton);


        horizontalLayout_6->addWidget(horizontalWidget);

        breadcrumbsLayout_2 = new QWidget(navbar);
        breadcrumbsLayout_2->setObjectName("breadcrumbsLayout_2");
        breadcrumbsLayout_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border:0;\n"
"}"));
        breadcrumbsLayout = new QHBoxLayout(breadcrumbsLayout_2);
        breadcrumbsLayout->setObjectName("breadcrumbsLayout");
        reloadButton = new QPushButton(breadcrumbsLayout_2);
        reloadButton->setObjectName("reloadButton");
        sizePolicy2.setHeightForWidth(reloadButton->sizePolicy().hasHeightForWidth());
        reloadButton->setSizePolicy(sizePolicy2);

        breadcrumbsLayout->addWidget(reloadButton);

        breadcrumbWidget = new QWidget(breadcrumbsLayout_2);
        breadcrumbWidget->setObjectName("breadcrumbWidget");
        breadcrumbWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(75, 75, 75);\n"
"border-radius:10px"));
        horizontalLayout_9 = new QHBoxLayout(breadcrumbWidget);
        horizontalLayout_9->setObjectName("horizontalLayout_9");

        breadcrumbsLayout->addWidget(breadcrumbWidget);

        searchLineEdit = new QTextEdit(breadcrumbsLayout_2);
        searchLineEdit->setObjectName("searchLineEdit");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Ignored);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(searchLineEdit->sizePolicy().hasHeightForWidth());
        searchLineEdit->setSizePolicy(sizePolicy7);

        breadcrumbsLayout->addWidget(searchLineEdit);

        searchButton = new QPushButton(breadcrumbsLayout_2);
        searchButton->setObjectName("searchButton");
        sizePolicy2.setHeightForWidth(searchButton->sizePolicy().hasHeightForWidth());
        searchButton->setSizePolicy(sizePolicy2);

        breadcrumbsLayout->addWidget(searchButton);


        horizontalLayout_6->addWidget(breadcrumbsLayout_2);

        line_7 = new QFrame(navbar);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::VLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_6->addWidget(line_7);


        gridLayout->addWidget(navbar, 1, 0, 1, 1);

        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName("verticalWidget");
        verticalLayout_2 = new QVBoxLayout(verticalWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(verticalWidget);
        widget->setObjectName("widget");
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalWidget_2 = new QWidget(widget);
        verticalWidget_2->setObjectName("verticalWidget_2");
        sizePolicy5.setHeightForWidth(verticalWidget_2->sizePolicy().hasHeightForWidth());
        verticalWidget_2->setSizePolicy(sizePolicy5);
        verticalWidget_2->setMinimumSize(QSize(150, 0));
        verticalWidget_2->setBaseSize(QSize(200, 0));
        verticalWidget_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalWidget_2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_9 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_9->setSpacing(11);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        recentFilesButton = new QPushButton(verticalWidget_2);
        recentFilesButton->setObjectName("recentFilesButton");
        recentFilesButton->setStyleSheet(QString::fromUtf8("padding: 10px;\n"
"text-align: left"));

        verticalLayout_9->addWidget(recentFilesButton);

        favoritesButton = new QPushButton(verticalWidget_2);
        favoritesButton->setObjectName("favoritesButton");
        favoritesButton->setStyleSheet(QString::fromUtf8("padding:10px;\n"
"text-align:left"));

        verticalLayout_9->addWidget(favoritesButton);

        driveTable = new QTableWidget(verticalWidget_2);
        if (driveTable->columnCount() < 1)
            driveTable->setColumnCount(1);
        driveTable->setObjectName("driveTable");
        driveTable->setColumnCount(1);

        verticalLayout_9->addWidget(driveTable);


        horizontalLayout_3->addWidget(verticalWidget_2, 0, Qt::AlignmentFlag::AlignTop);

        verticalWidget_3 = new QWidget(widget);
        verticalWidget_3->setObjectName("verticalWidget_3");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(verticalWidget_3->sizePolicy().hasHeightForWidth());
        verticalWidget_3->setSizePolicy(sizePolicy8);
        verticalLayout_8 = new QVBoxLayout(verticalWidget_3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        treeWidget_2 = new QTreeWidget(verticalWidget_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem);
        treeWidget_2->setObjectName("treeWidget_2");
        sizePolicy8.setHeightForWidth(treeWidget_2->sizePolicy().hasHeightForWidth());
        treeWidget_2->setSizePolicy(sizePolicy8);
        treeWidget_2->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        treeWidget_2->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

        verticalLayout_8->addWidget(treeWidget_2);


        horizontalLayout_3->addWidget(verticalWidget_3);


        verticalLayout_2->addWidget(widget);


        gridLayout->addWidget(verticalWidget, 2, 0, 1, 1);

        TrueExplorer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TrueExplorer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1054, 25));
        TrueExplorer->setMenuBar(menubar);
        statusbar = new QStatusBar(TrueExplorer);
        statusbar->setObjectName("statusbar");
        TrueExplorer->setStatusBar(statusbar);

        retranslateUi(TrueExplorer);

        QMetaObject::connectSlotsByName(TrueExplorer);
    } // setupUi

    void retranslateUi(QMainWindow *TrueExplorer)
    {
        TrueExplorer->setWindowTitle(QCoreApplication::translate("TrueExplorer", "TrueExplorer", nullptr));
        newFileButton->setText(QCoreApplication::translate("TrueExplorer", "Add File", nullptr));
        newFolderButton->setText(QCoreApplication::translate("TrueExplorer", "Add Folder", nullptr));
        nameSortRadioButton->setText(QCoreApplication::translate("TrueExplorer", "By name", nullptr));
        extensionSortRadioButton->setText(QCoreApplication::translate("TrueExplorer", "By extension", nullptr));
        sizeSortRadioButton->setText(QCoreApplication::translate("TrueExplorer", "By size", nullptr));
        timeSortRadioButton->setText(QCoreApplication::translate("TrueExplorer", "By time of creation", nullptr));
        label->setText(QCoreApplication::translate("TrueExplorer", "Sort : ", nullptr));
        label_2->setText(QCoreApplication::translate("TrueExplorer", "Search in : ", nullptr));
        currentDirRadioButton->setText(QCoreApplication::translate("TrueExplorer", "In current directory", nullptr));
        filebaseRadioButton->setText(QCoreApplication::translate("TrueExplorer", "In entire filebase", nullptr));
        label_3->setText(QCoreApplication::translate("TrueExplorer", "Graphics :", nullptr));
        barGraphRadioButton->setText(QCoreApplication::translate("TrueExplorer", "Bar Graph", nullptr));
        viewIndexToolButton->setText(QCoreApplication::translate("TrueExplorer", "View Index", nullptr));
        prevFolderButton->setText(QString());
        nextFolderButton->setText(QString());
        prevDirectoryButton->setText(QString());
        reloadButton->setText(QString());
        searchButton->setText(QCoreApplication::translate("TrueExplorer", "Search", nullptr));
        recentFilesButton->setText(QCoreApplication::translate("TrueExplorer", "Recent Files", nullptr));
        favoritesButton->setText(QCoreApplication::translate("TrueExplorer", "Favorites", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrueExplorer: public Ui_TrueExplorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUEEXPLORER_H
