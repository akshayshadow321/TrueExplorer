/****************************************************************************
** Meta object code from reading C++ file 'trueexplorer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../trueexplorer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trueexplorer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12TrueExplorerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12TrueExplorerE = QtMocHelpers::stringData(
    "TrueExplorer",
    "IconSetup",
    "",
    "updateBreadcrumbs",
    "path",
    "reloadDirectory",
    "on_reloadButton_clicked",
    "loadDirectory",
    "on_newFileButton_clicked",
    "on_newFolderButton_clicked",
    "renameSelectedItem",
    "deleteSelectedItem",
    "on_prevDirectoryButton_clicked",
    "on_treeWidget_itemDoubleClicked",
    "QTreeWidgetItem*",
    "item",
    "column",
    "on_treeWidget_customContextMenuRequested",
    "pos",
    "testFunction",
    "on_prevFolderButton_clicked",
    "on_nextFolderButton_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12TrueExplorerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    1,  105,    2, 0x08,    2 /* Private */,
       5,    0,  108,    2, 0x08,    4 /* Private */,
       6,    0,  109,    2, 0x08,    5 /* Private */,
       7,    1,  110,    2, 0x08,    6 /* Private */,
       8,    0,  113,    2, 0x08,    8 /* Private */,
       9,    0,  114,    2, 0x08,    9 /* Private */,
      10,    0,  115,    2, 0x08,   10 /* Private */,
      11,    0,  116,    2, 0x08,   11 /* Private */,
      12,    0,  117,    2, 0x08,   12 /* Private */,
      13,    2,  118,    2, 0x08,   13 /* Private */,
      17,    1,  123,    2, 0x08,   16 /* Private */,
      19,    0,  126,    2, 0x08,   18 /* Private */,
      20,    0,  127,    2, 0x08,   19 /* Private */,
      21,    0,  128,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::QPoint,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TrueExplorer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN12TrueExplorerE.offsetsAndSizes,
    qt_meta_data_ZN12TrueExplorerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12TrueExplorerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TrueExplorer, std::true_type>,
        // method 'IconSetup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateBreadcrumbs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'reloadDirectory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_reloadButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadDirectory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_newFileButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_newFolderButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'renameSelectedItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteSelectedItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_prevDirectoryButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_treeWidget_itemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_treeWidget_customContextMenuRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'testFunction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_prevFolderButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_nextFolderButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TrueExplorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TrueExplorer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->IconSetup(); break;
        case 1: _t->updateBreadcrumbs((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->reloadDirectory(); break;
        case 3: _t->on_reloadButton_clicked(); break;
        case 4: _t->loadDirectory((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_newFileButton_clicked(); break;
        case 6: _t->on_newFolderButton_clicked(); break;
        case 7: _t->renameSelectedItem(); break;
        case 8: _t->deleteSelectedItem(); break;
        case 9: _t->on_prevDirectoryButton_clicked(); break;
        case 10: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->on_treeWidget_customContextMenuRequested((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 12: _t->testFunction(); break;
        case 13: _t->on_prevFolderButton_clicked(); break;
        case 14: _t->on_nextFolderButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *TrueExplorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrueExplorer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12TrueExplorerE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TrueExplorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
