/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Jan 13 11:05:29 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      50,   11,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     190,   11,   11,   11, 0x08,
     224,   11,   11,   11, 0x08,
     260,  254,   11,   11, 0x08,
     288,   11,   11,   11, 0x08,
     329,   11,   11,   11, 0x08,
     367,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionOuvrir_un_masque_triggered()\0"
    "on_actionEnregistrer_le_masque_triggered()\0"
    "on_toolButton_erase_clicked()\0"
    "on_toolButton_write_clicked()\0"
    "on_checkBox_masque_stateChanged(int)\0"
    "on_spinBox_size_valueChanged(int)\0"
    "on_pushButton_clear_clicked()\0value\0"
    "on_Slider_valueChanged(int)\0"
    "on_actionEnregistrer_l_image_triggered()\0"
    "on_actionOuvrir_une_image_triggered()\0"
    "on_actionQuitter_triggered()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionOuvrir_un_masque_triggered(); break;
        case 1: on_actionEnregistrer_le_masque_triggered(); break;
        case 2: on_toolButton_erase_clicked(); break;
        case 3: on_toolButton_write_clicked(); break;
        case 4: on_checkBox_masque_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_spinBox_size_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_pushButton_clear_clicked(); break;
        case 7: on_Slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: on_actionEnregistrer_l_image_triggered(); break;
        case 9: on_actionOuvrir_une_image_triggered(); break;
        case 10: on_actionQuitter_triggered(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
