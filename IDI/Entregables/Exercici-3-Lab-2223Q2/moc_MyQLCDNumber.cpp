/****************************************************************************
** Meta object code from reading C++ file 'MyQLCDNumber.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyQLCDNumber.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyQLCDNumber.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyQLCDNumber_t {
    QByteArrayData data[16];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQLCDNumber_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQLCDNumber_t qt_meta_stringdata_MyQLCDNumber = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyQLCDNumber"
QT_MOC_LITERAL(1, 13, 9), // "enviarsec"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "sec"
QT_MOC_LITERAL(4, 28, 9), // "enviarmin"
QT_MOC_LITERAL(5, 38, 3), // "min"
QT_MOC_LITERAL(6, 42, 10), // "enviarhora"
QT_MOC_LITERAL(7, 53, 4), // "hora"
QT_MOC_LITERAL(8, 58, 9), // "enviarRec"
QT_MOC_LITERAL(9, 68, 6), // "record"
QT_MOC_LITERAL(10, 75, 12), // "canviaColBot"
QT_MOC_LITERAL(11, 88, 3), // "col"
QT_MOC_LITERAL(12, 92, 12), // "canviaColLCD"
QT_MOC_LITERAL(13, 105, 11), // "tractaClick"
QT_MOC_LITERAL(14, 117, 13), // "tractaTimeout"
QT_MOC_LITERAL(15, 131, 13) // "tractaRestart"

    },
    "MyQLCDNumber\0enviarsec\0\0sec\0enviarmin\0"
    "min\0enviarhora\0hora\0enviarRec\0record\0"
    "canviaColBot\0col\0canviaColLCD\0tractaClick\0"
    "tractaTimeout\0tractaRestart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQLCDNumber[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,
      10,    1,   71,    2, 0x06 /* Public */,
      12,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   77,    2, 0x0a /* Public */,
      14,    0,   78,    2, 0x0a /* Public */,
      15,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyQLCDNumber::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyQLCDNumber *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->enviarsec((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->enviarmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->enviarhora((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->enviarRec((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->canviaColBot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->canviaColLCD((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->tractaClick(); break;
        case 7: _t->tractaTimeout(); break;
        case 8: _t->tractaRestart(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyQLCDNumber::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQLCDNumber::enviarsec)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyQLCDNumber::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQLCDNumber::enviarmin)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyQLCDNumber::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQLCDNumber::enviarhora)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyQLCDNumber::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQLCDNumber::enviarRec)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyQLCDNumber::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQLCDNumber::canviaColBot)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MyQLCDNumber::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQLCDNumber::canviaColLCD)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyQLCDNumber::staticMetaObject = { {
    QMetaObject::SuperData::link<QLCDNumber::staticMetaObject>(),
    qt_meta_stringdata_MyQLCDNumber.data,
    qt_meta_data_MyQLCDNumber,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyQLCDNumber::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQLCDNumber::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyQLCDNumber.stringdata0))
        return static_cast<void*>(this);
    return QLCDNumber::qt_metacast(_clname);
}

int MyQLCDNumber::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
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
void MyQLCDNumber::enviarsec(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyQLCDNumber::enviarmin(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyQLCDNumber::enviarhora(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyQLCDNumber::enviarRec(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyQLCDNumber::canviaColBot(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyQLCDNumber::canviaColLCD(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
