/****************************************************************************
** Meta object code from reading C++ file 'openglwidgetviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../UUEngine/EngineUI/openglwidgetviewmodel.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openglwidgetviewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OpenGLWidgetViewModel_t {
    const uint offsetsAndSize[28];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_OpenGLWidgetViewModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_OpenGLWidgetViewModel_t qt_meta_stringdata_OpenGLWidgetViewModel = {
    {
QT_MOC_LITERAL(0, 21), // "OpenGLWidgetViewModel"
QT_MOC_LITERAL(22, 12), // "updateWindow"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 12), // "createCamera"
QT_MOC_LITERAL(49, 14), // "createLighting"
QT_MOC_LITERAL(64, 10), // "createCube"
QT_MOC_LITERAL(75, 13), // "createPyramid"
QT_MOC_LITERAL(89, 12), // "createSphere"
QT_MOC_LITERAL(102, 11), // "createPrism"
QT_MOC_LITERAL(114, 14), // "createCylinder"
QT_MOC_LITERAL(129, 10), // "createCone"
QT_MOC_LITERAL(140, 18), // "createCustomObject"
QT_MOC_LITERAL(159, 15), // "setDisableState"
QT_MOC_LITERAL(175, 5) // "state"

    },
    "OpenGLWidgetViewModel\0updateWindow\0\0"
    "createCamera\0createLighting\0createCube\0"
    "createPyramid\0createSphere\0createPrism\0"
    "createCylinder\0createCone\0createCustomObject\0"
    "setDisableState\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGLWidgetViewModel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   81,    2, 0x0a,    2 /* Public */,
       4,    0,   82,    2, 0x0a,    3 /* Public */,
       5,    0,   83,    2, 0x0a,    4 /* Public */,
       6,    0,   84,    2, 0x0a,    5 /* Public */,
       7,    0,   85,    2, 0x0a,    6 /* Public */,
       8,    0,   86,    2, 0x0a,    7 /* Public */,
       9,    0,   87,    2, 0x0a,    8 /* Public */,
      10,    0,   88,    2, 0x0a,    9 /* Public */,
      11,    0,   89,    2, 0x0a,   10 /* Public */,
      12,    1,   90,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,

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
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void OpenGLWidgetViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OpenGLWidgetViewModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateWindow(); break;
        case 1: _t->createCamera(); break;
        case 2: _t->createLighting(); break;
        case 3: _t->createCube(); break;
        case 4: _t->createPyramid(); break;
        case 5: _t->createSphere(); break;
        case 6: _t->createPrism(); break;
        case 7: _t->createCylinder(); break;
        case 8: _t->createCone(); break;
        case 9: _t->createCustomObject(); break;
        case 10: _t->setDisableState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OpenGLWidgetViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidgetViewModel::updateWindow)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject OpenGLWidgetViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_OpenGLWidgetViewModel.offsetsAndSize,
    qt_meta_data_OpenGLWidgetViewModel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_OpenGLWidgetViewModel_t
, QtPrivate::TypeAndForceComplete<OpenGLWidgetViewModel, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *OpenGLWidgetViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLWidgetViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLWidgetViewModel.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int OpenGLWidgetViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void OpenGLWidgetViewModel::updateWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
