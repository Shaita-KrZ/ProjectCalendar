/****************************************************************************
** Meta object code from reading C++ file 'fenetreGestionProjet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ExeProjectCalendar/fenetreGestionProjet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetreGestionProjet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Gestionprojets_t {
    QByteArrayData data[15];
    char stringdata[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gestionprojets_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gestionprojets_t qt_meta_stringdata_Gestionprojets = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Gestionprojets"
QT_MOC_LITERAL(1, 15, 13), // "chargerProjet"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "ouvrirProjet"
QT_MOC_LITERAL(4, 43, 14), // "supprimeProjet"
QT_MOC_LITERAL(5, 58, 14), // "creationProjet"
QT_MOC_LITERAL(6, 73, 13), // "validerProjet"
QT_MOC_LITERAL(7, 87, 13), // "annulerProjet"
QT_MOC_LITERAL(8, 101, 19), // "modifierTitreProjet"
QT_MOC_LITERAL(9, 121, 18), // "validerTitreProjet"
QT_MOC_LITERAL(10, 140, 18), // "annulerTitreProjet"
QT_MOC_LITERAL(11, 159, 13), // "modifierTache"
QT_MOC_LITERAL(12, 173, 17), // "validermodifTache"
QT_MOC_LITERAL(13, 191, 17), // "annulermodifTache"
QT_MOC_LITERAL(14, 209, 12) // "ajouterTache"

    },
    "Gestionprojets\0chargerProjet\0\0"
    "ouvrirProjet\0supprimeProjet\0creationProjet\0"
    "validerProjet\0annulerProjet\0"
    "modifierTitreProjet\0validerTitreProjet\0"
    "annulerTitreProjet\0modifierTache\0"
    "validermodifTache\0annulermodifTache\0"
    "ajouterTache"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gestionprojets[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Gestionprojets::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Gestionprojets *_t = static_cast<Gestionprojets *>(_o);
        switch (_id) {
        case 0: _t->chargerProjet(); break;
        case 1: _t->ouvrirProjet(); break;
        case 2: _t->supprimeProjet(); break;
        case 3: _t->creationProjet(); break;
        case 4: _t->validerProjet(); break;
        case 5: _t->annulerProjet(); break;
        case 6: _t->modifierTitreProjet(); break;
        case 7: _t->validerTitreProjet(); break;
        case 8: _t->annulerTitreProjet(); break;
        case 9: _t->modifierTache(); break;
        case 10: _t->validermodifTache(); break;
        case 11: _t->annulermodifTache(); break;
        case 12: _t->ajouterTache(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Gestionprojets::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Gestionprojets.data,
      qt_meta_data_Gestionprojets,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Gestionprojets::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gestionprojets::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Gestionprojets.stringdata))
        return static_cast<void*>(const_cast< Gestionprojets*>(this));
    return QWidget::qt_metacast(_clname);
}

int Gestionprojets::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
