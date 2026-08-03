/****************************************************************************
** Meta object code from reading C++ file 'VehicleData.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/model/VehicleData.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VehicleData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VehicleData_t {
    QByteArrayData data[10];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VehicleData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VehicleData_t qt_meta_stringdata_VehicleData = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VehicleData"
QT_MOC_LITERAL(1, 12, 12), // "speedChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "rpmChanged"
QT_MOC_LITERAL(4, 37, 16), // "fuelLevelChanged"
QT_MOC_LITERAL(5, 54, 17), // "engineTempChanged"
QT_MOC_LITERAL(6, 72, 5), // "speed"
QT_MOC_LITERAL(7, 78, 3), // "rpm"
QT_MOC_LITERAL(8, 82, 9), // "fuelLevel"
QT_MOC_LITERAL(9, 92, 10) // "engineTemp"

    },
    "VehicleData\0speedChanged\0\0rpmChanged\0"
    "fuelLevelChanged\0engineTempChanged\0"
    "speed\0rpm\0fuelLevel\0engineTemp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VehicleData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::Double, 0x00495903,
       7, QMetaType::Double, 0x00495903,
       8, QMetaType::Double, 0x00495903,
       9, QMetaType::Double, 0x00495903,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void VehicleData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VehicleData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->speedChanged(); break;
        case 1: _t->rpmChanged(); break;
        case 2: _t->fuelLevelChanged(); break;
        case 3: _t->engineTempChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VehicleData::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VehicleData::speedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VehicleData::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VehicleData::rpmChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VehicleData::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VehicleData::fuelLevelChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VehicleData::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VehicleData::engineTempChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<VehicleData *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->speed(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->rpm(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->fuelLevel(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->engineTemp(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<VehicleData *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSpeed(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setRpm(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setFuelLevel(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setEngineTemp(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VehicleData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_VehicleData.data,
    qt_meta_data_VehicleData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VehicleData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VehicleData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VehicleData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VehicleData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VehicleData::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VehicleData::rpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VehicleData::fuelLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VehicleData::engineTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
