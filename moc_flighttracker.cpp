/****************************************************************************
** Meta object code from reading C++ file 'flighttracker.h'
**
** Created: Mon Jul 14 09:32:52 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "flighttracker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flighttracker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FlightTracker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      39,   28,   14,   14, 0x09,
      65,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FlightTracker[] = {
    "FlightTracker\0\0refreshPic()\0dest,frame\0"
    "refreshRect(QImage*,Mat*)\0updateMovingLogic()\0"
};

void FlightTracker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FlightTracker *_t = static_cast<FlightTracker *>(_o);
        switch (_id) {
        case 0: _t->refreshPic(); break;
        case 1: _t->refreshRect((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< Mat*(*)>(_a[2]))); break;
        case 2: _t->updateMovingLogic(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FlightTracker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FlightTracker::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FlightTracker,
      qt_meta_data_FlightTracker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FlightTracker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FlightTracker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FlightTracker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FlightTracker))
        return static_cast<void*>(const_cast< FlightTracker*>(this));
    return QWidget::qt_metacast(_clname);
}

int FlightTracker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
