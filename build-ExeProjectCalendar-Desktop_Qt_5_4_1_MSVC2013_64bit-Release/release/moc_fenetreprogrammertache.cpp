/****************************************************************************
** Meta object code from reading C++ file 'fenetreprogrammertache.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ExeProjectCalendar/fenetreprogrammertache.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetreprogrammertache.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FenetreProgrammerTache_t {
    QByteArrayData data[7];
    char stringdata[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FenetreProgrammerTache_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FenetreProgrammerTache_t qt_meta_stringdata_FenetreProgrammerTache = {
    {
QT_MOC_LITERAL(0, 0, 22), // "FenetreProgrammerTache"
QT_MOC_LITERAL(1, 23, 21), // "on_inProjet_activated"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 4), // "arg1"
QT_MOC_LITERAL(4, 51, 20), // "on_inTache_activated"
QT_MOC_LITERAL(5, 72, 21), // "on_inTache2_activated"
QT_MOC_LITERAL(6, 94, 15) // "on_bOK_accepted"

    },
    "FenetreProgrammerTache\0on_inProjet_activated\0"
    "\0arg1\0on_inTache_activated\0"
    "on_inTache2_activated\0on_bOK_accepted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenetreProgrammerTache[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    1,   40,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void FenetreProgrammerTache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FenetreProgrammerTache *_t = static_cast<FenetreProgrammerTache *>(_o);
        switch (_id) {
        case 0: _t->on_inProjet_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_inTache_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_inTache2_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_bOK_accepted(); break;
        default: ;
        }
    }
}

const QMetaObject FenetreProgrammerTache::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FenetreProgrammerTache.data,
      qt_meta_data_FenetreProgrammerTache,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FenetreProgrammerTache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FenetreProgrammerTache::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FenetreProgrammerTache.stringdata))
        return static_cast<void*>(const_cast< FenetreProgrammerTache*>(this));
    return QDialog::qt_metacast(_clname);
}

int FenetreProgrammerTache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE