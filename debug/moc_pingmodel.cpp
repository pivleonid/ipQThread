/****************************************************************************
** Meta object code from reading C++ file 'pingmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pingmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pingmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PingModel_t {
    QByteArrayData data[12];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PingModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PingModel_t qt_meta_stringdata_PingModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PingModel"
QT_MOC_LITERAL(1, 10, 10), // "signalData"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "data"
QT_MOC_LITERAL(4, 27, 15), // "signalStartData"
QT_MOC_LITERAL(5, 43, 9), // "endThread"
QT_MOC_LITERAL(6, 53, 11), // "signalError"
QT_MOC_LITERAL(7, 65, 12), // "verifyStatus"
QT_MOC_LITERAL(8, 78, 10), // "readResult"
QT_MOC_LITERAL(9, 89, 10), // "disconPing"
QT_MOC_LITERAL(10, 100, 3), // "run"
QT_MOC_LITERAL(11, 104, 5) // "error"

    },
    "PingModel\0signalData\0\0data\0signalStartData\0"
    "endThread\0signalError\0verifyStatus\0"
    "readResult\0disconPing\0run\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PingModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    0,   63,    2, 0x06 /* Public */,
       6,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   65,    2, 0x0a /* Public */,
       8,    0,   66,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,
      10,    0,   68,    2, 0x0a /* Public */,
      11,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PingModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PingModel *_t = static_cast<PingModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalStartData(); break;
        case 2: _t->endThread(); break;
        case 3: _t->signalError(); break;
        case 4: _t->verifyStatus(); break;
        case 5: _t->readResult(); break;
        case 6: _t->disconPing(); break;
        case 7: _t->run(); break;
        case 8: _t->error(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PingModel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PingModel::signalData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PingModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PingModel::signalStartData)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PingModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PingModel::endThread)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PingModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PingModel::signalError)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject PingModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PingModel.data,
      qt_meta_data_PingModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PingModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PingModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PingModel.stringdata0))
        return static_cast<void*>(const_cast< PingModel*>(this));
    return QObject::qt_metacast(_clname);
}

int PingModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PingModel::signalData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PingModel::signalStartData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PingModel::endThread()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PingModel::signalError()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
