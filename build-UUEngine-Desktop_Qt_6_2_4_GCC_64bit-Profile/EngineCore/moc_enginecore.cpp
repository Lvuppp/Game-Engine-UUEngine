/****************************************************************************
** Meta object code from reading C++ file 'enginecore.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../UUEngine/EngineCore/Cores/enginecore.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enginecore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EngineCore_t {
    const uint offsetsAndSize[50];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_EngineCore_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_EngineCore_t qt_meta_stringdata_EngineCore = {
    {
QT_MOC_LITERAL(0, 10), // "EngineCore"
QT_MOC_LITERAL(11, 14), // "updateGraphics"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 13), // "projectLoaded"
QT_MOC_LITERAL(41, 15), // "setDisableState"
QT_MOC_LITERAL(57, 5), // "state"
QT_MOC_LITERAL(63, 10), // "emitObject"
QT_MOC_LITERAL(74, 17), // "BaseEngineObject*"
QT_MOC_LITERAL(92, 6), // "object"
QT_MOC_LITERAL(99, 15), // "mousePressEvent"
QT_MOC_LITERAL(115, 12), // "QMouseEvent*"
QT_MOC_LITERAL(128, 5), // "event"
QT_MOC_LITERAL(134, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(149, 10), // "wheelEvent"
QT_MOC_LITERAL(160, 12), // "QWheelEvent*"
QT_MOC_LITERAL(173, 21), // "mouseDoubleClickEvent"
QT_MOC_LITERAL(195, 15), // "translateObject"
QT_MOC_LITERAL(211, 10), // "objectName"
QT_MOC_LITERAL(222, 13), // "createProject"
QT_MOC_LITERAL(236, 4), // "path"
QT_MOC_LITERAL(241, 4), // "name"
QT_MOC_LITERAL(246, 11), // "loadProject"
QT_MOC_LITERAL(258, 11), // "saveProject"
QT_MOC_LITERAL(270, 11), // "projectName"
QT_MOC_LITERAL(282, 12) // "closeProject"

    },
    "EngineCore\0updateGraphics\0\0projectLoaded\0"
    "setDisableState\0state\0emitObject\0"
    "BaseEngineObject*\0object\0mousePressEvent\0"
    "QMouseEvent*\0event\0mouseMoveEvent\0"
    "wheelEvent\0QWheelEvent*\0mouseDoubleClickEvent\0"
    "translateObject\0objectName\0createProject\0"
    "path\0name\0loadProject\0saveProject\0"
    "projectName\0closeProject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EngineCore[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x06,    1 /* Public */,
       3,    0,  105,    2, 0x06,    2 /* Public */,
       4,    1,  106,    2, 0x06,    3 /* Public */,
       6,    1,  109,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,  112,    2, 0x0a,    7 /* Public */,
      12,    1,  115,    2, 0x0a,    9 /* Public */,
      13,    1,  118,    2, 0x0a,   11 /* Public */,
      15,    1,  121,    2, 0x0a,   13 /* Public */,
      16,    1,  124,    2, 0x0a,   15 /* Public */,
      18,    2,  127,    2, 0x0a,   17 /* Public */,
      21,    1,  132,    2, 0x0a,   20 /* Public */,
      22,    2,  135,    2, 0x0a,   22 /* Public */,
      22,    1,  140,    2, 0x2a,   25 /* Public | MethodCloned */,
      22,    0,  143,    2, 0x2a,   27 /* Public | MethodCloned */,
      24,    0,  144,    2, 0x0a,   28 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 14,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   23,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EngineCore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EngineCore *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateGraphics(); break;
        case 1: _t->projectLoaded(); break;
        case 2: _t->setDisableState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->emitObject((*reinterpret_cast< std::add_pointer_t<BaseEngineObject*>>(_a[1]))); break;
        case 4: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 5: _t->mouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 6: _t->wheelEvent((*reinterpret_cast< std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 7: _t->mouseDoubleClickEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 8: _t->translateObject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->createProject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->loadProject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->saveProject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->saveProject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->saveProject(); break;
        case 14: _t->closeProject(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EngineCore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EngineCore::updateGraphics)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EngineCore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EngineCore::projectLoaded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EngineCore::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EngineCore::setDisableState)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EngineCore::*)(BaseEngineObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EngineCore::emitObject)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject EngineCore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_EngineCore.offsetsAndSize,
    qt_meta_data_EngineCore,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_EngineCore_t
, QtPrivate::TypeAndForceComplete<EngineCore, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<BaseEngineObject *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QWheelEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *EngineCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EngineCore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EngineCore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EngineCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void EngineCore::updateGraphics()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void EngineCore::projectLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void EngineCore::setDisableState(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void EngineCore::emitObject(BaseEngineObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
