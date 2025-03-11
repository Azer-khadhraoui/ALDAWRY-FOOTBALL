/****************************************************************************
** Meta object code from reading C++ file 'qcustomplot.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qcustomplot.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcustomplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
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
struct qt_meta_tag_ZN10QCPPainterE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10QCPPainterE = QtMocHelpers::stringData(
    "QCPPainter",
    "PainterMode",
    "pmDefault",
    "pmVectorized",
    "pmNoCaching",
    "pmNonCosmetic",
    "PainterModes"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10QCPPainterE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   24,
       6,    1, 0x1,    4,   32,

 // enum data: key, value
       2, uint(QCPPainter::pmDefault),
       3, uint(QCPPainter::pmVectorized),
       4, uint(QCPPainter::pmNoCaching),
       5, uint(QCPPainter::pmNonCosmetic),
       2, uint(QCPPainter::pmDefault),
       3, uint(QCPPainter::pmVectorized),
       4, uint(QCPPainter::pmNoCaching),
       5, uint(QCPPainter::pmNonCosmetic),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPainter::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QPainter>::value,
    qt_meta_stringdata_ZN10QCPPainterE.offsetsAndSizes,
    qt_meta_data_ZN10QCPPainterE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10QCPPainterE_t,
        // enum 'PainterMode'
        QtPrivate::TypeAndForceComplete<QCPPainter::PainterMode, std::true_type>,
        // enum 'PainterModes'
        QtPrivate::TypeAndForceComplete<QCPPainter::PainterModes, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPainter, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN8QCPLayerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN8QCPLayerE = QtMocHelpers::stringData(
    "QCPLayer",
    "parentPlot",
    "QCustomPlot*",
    "name",
    "index",
    "children",
    "QList<QCPLayerable*>",
    "visible",
    "mode",
    "LayerMode",
    "lmLogical",
    "lmBuffered"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN8QCPLayerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       1,   44, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x00015009, uint(-1), 0,
       3, QMetaType::QString, 0x00015001, uint(-1), 0,
       4, QMetaType::Int, 0x00015001, uint(-1), 0,
       5, 0x80000000 | 6, 0x00015009, uint(-1), 0,
       7, QMetaType::Bool, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    2,   49,

 // enum data: key, value
      10, uint(QCPLayer::lmLogical),
      11, uint(QCPLayer::lmBuffered),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN8QCPLayerE.offsetsAndSizes,
    qt_meta_data_ZN8QCPLayerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN8QCPLayerE_t,
        // property 'parentPlot'
        QtPrivate::TypeAndForceComplete<QCustomPlot*, std::true_type>,
        // property 'name'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'index'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'children'
        QtPrivate::TypeAndForceComplete<QList<QCPLayerable*>, std::true_type>,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'mode'
        QtPrivate::TypeAndForceComplete<LayerMode, std::true_type>,
        // enum 'LayerMode'
        QtPrivate::TypeAndForceComplete<QCPLayer::LayerMode, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayer, std::true_type>
    >,
    nullptr
} };

void QCPLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLayer *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QCPLayerable*> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCustomPlot**>(_v) = _t->parentPlot(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->index(); break;
        case 3: *reinterpret_cast< QList<QCPLayerable*>*>(_v) = _t->children(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->visible(); break;
        case 5: *reinterpret_cast< LayerMode*>(_v) = _t->mode(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setMode(*reinterpret_cast< LayerMode*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN8QCPLayerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN12QCPLayerableE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12QCPLayerableE = QtMocHelpers::stringData(
    "QCPLayerable",
    "layerChanged",
    "",
    "QCPLayer*",
    "newLayer",
    "setLayer",
    "layer",
    "visible",
    "parentPlot",
    "QCustomPlot*",
    "parentLayerable",
    "QCPLayerable*",
    "antialiased"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12QCPLayerableE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       5,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   29,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 3,    6,

 // properties: name, type, flags, notifyId, revision
       7, QMetaType::Bool, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x00015009, uint(-1), 0,
      10, 0x80000000 | 11, 0x00015009, uint(-1), 0,
       6, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      12, QMetaType::Bool, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayerable::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN12QCPLayerableE.offsetsAndSizes,
    qt_meta_data_ZN12QCPLayerableE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12QCPLayerableE_t,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'parentPlot'
        QtPrivate::TypeAndForceComplete<QCustomPlot*, std::true_type>,
        // property 'parentLayerable'
        QtPrivate::TypeAndForceComplete<QCPLayerable*, std::true_type>,
        // property 'layer'
        QtPrivate::TypeAndForceComplete<QCPLayer*, std::true_type>,
        // property 'antialiased'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayerable, std::true_type>,
        // method 'layerChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLayer *, std::false_type>,
        // method 'setLayer'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLayer *, std::false_type>
    >,
    nullptr
} };

void QCPLayerable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLayerable *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->layerChanged((*reinterpret_cast< std::add_pointer_t<QCPLayer*>>(_a[1]))); break;
        case 1: { bool _r = _t->setLayer((*reinterpret_cast< std::add_pointer_t<QCPLayer*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLayer* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLayer* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPLayerable::*)(QCPLayer * );
            if (_q_method_type _q_method = &QCPLayerable::layerChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayer* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayerable* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->visible(); break;
        case 1: *reinterpret_cast< QCustomPlot**>(_v) = _t->parentPlot(); break;
        case 2: *reinterpret_cast< QCPLayerable**>(_v) = _t->parentLayerable(); break;
        case 3: *reinterpret_cast< QCPLayer**>(_v) = _t->layer(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->antialiased(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setLayer(*reinterpret_cast< QCPLayer**>(_v)); break;
        case 4: _t->setAntialiased(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPLayerable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayerable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12QCPLayerableE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPLayerable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QCPLayerable::layerChanged(QCPLayer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
namespace {
struct qt_meta_tag_ZN16QCPSelectionRectE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16QCPSelectionRectE = QtMocHelpers::stringData(
    "QCPSelectionRect",
    "started",
    "",
    "QMouseEvent*",
    "event",
    "changed",
    "rect",
    "canceled",
    "QInputEvent*",
    "accepted",
    "cancel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16QCPSelectionRectE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    2,   47,    2, 0x06,    3 /* Public */,
       7,    2,   52,    2, 0x06,    6 /* Public */,
       9,    2,   57,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   62,    2, 0x0a,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,    6,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 8,    6,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,    6,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPSelectionRect::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN16QCPSelectionRectE.offsetsAndSizes,
    qt_meta_data_ZN16QCPSelectionRectE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16QCPSelectionRectE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPSelectionRect, std::true_type>,
        // method 'started'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'canceled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QInputEvent *, std::false_type>,
        // method 'accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'cancel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCPSelectionRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPSelectionRect *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->started((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 1: _t->changed((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 2: _t->canceled((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QInputEvent*>>(_a[2]))); break;
        case 3: _t->accepted((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 4: _t->cancel(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPSelectionRect::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCPSelectionRect::started; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPSelectionRect::*)(const QRect & , QMouseEvent * );
            if (_q_method_type _q_method = &QCPSelectionRect::changed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPSelectionRect::*)(const QRect & , QInputEvent * );
            if (_q_method_type _q_method = &QCPSelectionRect::canceled; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCPSelectionRect::*)(const QRect & , QMouseEvent * );
            if (_q_method_type _q_method = &QCPSelectionRect::accepted; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *QCPSelectionRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPSelectionRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16QCPSelectionRectE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPSelectionRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QCPSelectionRect::started(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPSelectionRect::changed(const QRect & _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPSelectionRect::canceled(const QRect & _t1, QInputEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPSelectionRect::accepted(const QRect & _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN14QCPMarginGroupE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QCPMarginGroupE = QtMocHelpers::stringData(
    "QCPMarginGroup"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QCPMarginGroupE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPMarginGroup::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN14QCPMarginGroupE.offsetsAndSizes,
    qt_meta_data_ZN14QCPMarginGroupE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QCPMarginGroupE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPMarginGroup, std::true_type>
    >,
    nullptr
} };

void QCPMarginGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPMarginGroup *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *QCPMarginGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPMarginGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QCPMarginGroupE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPMarginGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN16QCPLayoutElementE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16QCPLayoutElementE = QtMocHelpers::stringData(
    "QCPLayoutElement",
    "layout",
    "QCPLayout*",
    "rect",
    "outerRect",
    "margins",
    "QMargins",
    "minimumMargins",
    "minimumSize",
    "maximumSize",
    "sizeConstraintRect",
    "SizeConstraintRect",
    "UpdatePhase",
    "upPreparation",
    "upMargins",
    "upLayout",
    "scrInnerRect",
    "scrOuterRect"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16QCPLayoutElementE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       2,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x00015009, uint(-1), 0,
       3, QMetaType::QRect, 0x00015001, uint(-1), 0,
       4, QMetaType::QRect, 0x00015103, uint(-1), 0,
       5, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       7, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       8, QMetaType::QSize, 0x00015103, uint(-1), 0,
       9, QMetaType::QSize, 0x00015103, uint(-1), 0,
      10, 0x80000000 | 11, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
      12,   12, 0x0,    3,   64,
      11,   11, 0x0,    2,   70,

 // enum data: key, value
      13, uint(QCPLayoutElement::upPreparation),
      14, uint(QCPLayoutElement::upMargins),
      15, uint(QCPLayoutElement::upLayout),
      16, uint(QCPLayoutElement::scrInnerRect),
      17, uint(QCPLayoutElement::scrOuterRect),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayoutElement::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN16QCPLayoutElementE.offsetsAndSizes,
    qt_meta_data_ZN16QCPLayoutElementE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16QCPLayoutElementE_t,
        // property 'layout'
        QtPrivate::TypeAndForceComplete<QCPLayout*, std::true_type>,
        // property 'rect'
        QtPrivate::TypeAndForceComplete<QRect, std::true_type>,
        // property 'outerRect'
        QtPrivate::TypeAndForceComplete<QRect, std::true_type>,
        // property 'margins'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // property 'minimumMargins'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // property 'minimumSize'
        QtPrivate::TypeAndForceComplete<QSize, std::true_type>,
        // property 'maximumSize'
        QtPrivate::TypeAndForceComplete<QSize, std::true_type>,
        // property 'sizeConstraintRect'
        QtPrivate::TypeAndForceComplete<SizeConstraintRect, std::true_type>,
        // enum 'UpdatePhase'
        QtPrivate::TypeAndForceComplete<QCPLayoutElement::UpdatePhase, std::true_type>,
        // enum 'SizeConstraintRect'
        QtPrivate::TypeAndForceComplete<QCPLayoutElement::SizeConstraintRect, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayoutElement, std::true_type>
    >,
    nullptr
} };

void QCPLayoutElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLayoutElement *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayout* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPLayout**>(_v) = _t->layout(); break;
        case 1: *reinterpret_cast< QRect*>(_v) = _t->rect(); break;
        case 2: *reinterpret_cast< QRect*>(_v) = _t->outerRect(); break;
        case 3: *reinterpret_cast< QMargins*>(_v) = _t->margins(); break;
        case 4: *reinterpret_cast< QMargins*>(_v) = _t->minimumMargins(); break;
        case 5: *reinterpret_cast< QSize*>(_v) = _t->minimumSize(); break;
        case 6: *reinterpret_cast< QSize*>(_v) = _t->maximumSize(); break;
        case 7: *reinterpret_cast< SizeConstraintRect*>(_v) = _t->sizeConstraintRect(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setOuterRect(*reinterpret_cast< QRect*>(_v)); break;
        case 3: _t->setMargins(*reinterpret_cast< QMargins*>(_v)); break;
        case 4: _t->setMinimumMargins(*reinterpret_cast< QMargins*>(_v)); break;
        case 5: _t->setMinimumSize(*reinterpret_cast< QSize*>(_v)); break;
        case 6: _t->setMaximumSize(*reinterpret_cast< QSize*>(_v)); break;
        case 7: _t->setSizeConstraintRect(*reinterpret_cast< SizeConstraintRect*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPLayoutElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayoutElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16QCPLayoutElementE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPLayoutElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN9QCPLayoutE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN9QCPLayoutE = QtMocHelpers::stringData(
    "QCPLayout"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN9QCPLayoutE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayout::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_ZN9QCPLayoutE.offsetsAndSizes,
    qt_meta_data_ZN9QCPLayoutE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN9QCPLayoutE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayout, std::true_type>
    >,
    nullptr
} };

void QCPLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLayout *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *QCPLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN9QCPLayoutE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN13QCPLayoutGridE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPLayoutGridE = QtMocHelpers::stringData(
    "QCPLayoutGrid",
    "rowCount",
    "columnCount",
    "columnStretchFactors",
    "QList<double>",
    "rowStretchFactors",
    "columnSpacing",
    "rowSpacing",
    "fillOrder",
    "FillOrder",
    "wrap",
    "foRowsFirst",
    "foColumnsFirst"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPLayoutGridE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       1,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::Int, 0x00015001, uint(-1), 0,
       2, QMetaType::Int, 0x00015001, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       6, QMetaType::Int, 0x00015103, uint(-1), 0,
       7, QMetaType::Int, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x0001510b, uint(-1), 0,
      10, QMetaType::Int, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    2,   59,

 // enum data: key, value
      11, uint(QCPLayoutGrid::foRowsFirst),
      12, uint(QCPLayoutGrid::foColumnsFirst),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayoutGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayout::staticMetaObject>(),
    qt_meta_stringdata_ZN13QCPLayoutGridE.offsetsAndSizes,
    qt_meta_data_ZN13QCPLayoutGridE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPLayoutGridE_t,
        // property 'rowCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'columnCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'columnStretchFactors'
        QtPrivate::TypeAndForceComplete<QList<double>, std::true_type>,
        // property 'rowStretchFactors'
        QtPrivate::TypeAndForceComplete<QList<double>, std::true_type>,
        // property 'columnSpacing'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'rowSpacing'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'fillOrder'
        QtPrivate::TypeAndForceComplete<FillOrder, std::true_type>,
        // property 'wrap'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // enum 'FillOrder'
        QtPrivate::TypeAndForceComplete<QCPLayoutGrid::FillOrder, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayoutGrid, std::true_type>
    >,
    nullptr
} };

void QCPLayoutGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLayoutGrid *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->rowCount(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->columnCount(); break;
        case 2: *reinterpret_cast< QList<double>*>(_v) = _t->columnStretchFactors(); break;
        case 3: *reinterpret_cast< QList<double>*>(_v) = _t->rowStretchFactors(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->columnSpacing(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->rowSpacing(); break;
        case 6: *reinterpret_cast< FillOrder*>(_v) = _t->fillOrder(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->wrap(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setColumnStretchFactors(*reinterpret_cast< QList<double>*>(_v)); break;
        case 3: _t->setRowStretchFactors(*reinterpret_cast< QList<double>*>(_v)); break;
        case 4: _t->setColumnSpacing(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setRowSpacing(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setFillOrder(*reinterpret_cast< FillOrder*>(_v)); break;
        case 7: _t->setWrap(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPLayoutGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayoutGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QCPLayoutGridE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayout::qt_metacast(_clname);
}

int QCPLayoutGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN14QCPLayoutInsetE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QCPLayoutInsetE = QtMocHelpers::stringData(
    "QCPLayoutInset",
    "InsetPlacement",
    "ipFree",
    "ipBorderAligned"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QCPLayoutInsetE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   19,

 // enum data: key, value
       2, uint(QCPLayoutInset::ipFree),
       3, uint(QCPLayoutInset::ipBorderAligned),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayoutInset::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayout::staticMetaObject>(),
    qt_meta_stringdata_ZN14QCPLayoutInsetE.offsetsAndSizes,
    qt_meta_data_ZN14QCPLayoutInsetE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QCPLayoutInsetE_t,
        // enum 'InsetPlacement'
        QtPrivate::TypeAndForceComplete<QCPLayoutInset::InsetPlacement, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayoutInset, std::true_type>
    >,
    nullptr
} };

void QCPLayoutInset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLayoutInset *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *QCPLayoutInset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayoutInset::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QCPLayoutInsetE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayout::qt_metacast(_clname);
}

int QCPLayoutInset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayout::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN13QCPLineEndingE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPLineEndingE = QtMocHelpers::stringData(
    "QCPLineEnding",
    "EndingStyle",
    "esNone",
    "esFlatArrow",
    "esSpikeArrow",
    "esLineArrow",
    "esDisc",
    "esSquare",
    "esDiamond",
    "esBar",
    "esHalfBar",
    "esSkewedBar"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPLineEndingE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,   10,   19,

 // enum data: key, value
       2, uint(QCPLineEnding::esNone),
       3, uint(QCPLineEnding::esFlatArrow),
       4, uint(QCPLineEnding::esSpikeArrow),
       5, uint(QCPLineEnding::esLineArrow),
       6, uint(QCPLineEnding::esDisc),
       7, uint(QCPLineEnding::esSquare),
       8, uint(QCPLineEnding::esDiamond),
       9, uint(QCPLineEnding::esBar),
      10, uint(QCPLineEnding::esHalfBar),
      11, uint(QCPLineEnding::esSkewedBar),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLineEnding::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN13QCPLineEndingE.offsetsAndSizes,
    qt_meta_data_ZN13QCPLineEndingE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPLineEndingE_t,
        // enum 'EndingStyle'
        QtPrivate::TypeAndForceComplete<QCPLineEnding::EndingStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN22QCPLabelPainterPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN22QCPLabelPainterPrivateE = QtMocHelpers::stringData(
    "QCPLabelPainterPrivate",
    "AnchorMode",
    "amRectangular",
    "amSkewedUpright",
    "amSkewedRotated",
    "AnchorReferenceType",
    "artNormal",
    "artTangent",
    "AnchorSide",
    "asLeft",
    "asRight",
    "asTop",
    "asBottom",
    "asTopLeft",
    "asTopRight",
    "asBottomRight",
    "asBottomLeft"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN22QCPLabelPainterPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   29,
       5,    5, 0x0,    2,   35,
       8,    8, 0x0,    8,   39,

 // enum data: key, value
       2, uint(QCPLabelPainterPrivate::amRectangular),
       3, uint(QCPLabelPainterPrivate::amSkewedUpright),
       4, uint(QCPLabelPainterPrivate::amSkewedRotated),
       6, uint(QCPLabelPainterPrivate::artNormal),
       7, uint(QCPLabelPainterPrivate::artTangent),
       9, uint(QCPLabelPainterPrivate::asLeft),
      10, uint(QCPLabelPainterPrivate::asRight),
      11, uint(QCPLabelPainterPrivate::asTop),
      12, uint(QCPLabelPainterPrivate::asBottom),
      13, uint(QCPLabelPainterPrivate::asTopLeft),
      14, uint(QCPLabelPainterPrivate::asTopRight),
      15, uint(QCPLabelPainterPrivate::asBottomRight),
      16, uint(QCPLabelPainterPrivate::asBottomLeft),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLabelPainterPrivate::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN22QCPLabelPainterPrivateE.offsetsAndSizes,
    qt_meta_data_ZN22QCPLabelPainterPrivateE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN22QCPLabelPainterPrivateE_t,
        // enum 'AnchorMode'
        QtPrivate::TypeAndForceComplete<QCPLabelPainterPrivate::AnchorMode, std::true_type>,
        // enum 'AnchorReferenceType'
        QtPrivate::TypeAndForceComplete<QCPLabelPainterPrivate::AnchorReferenceType, std::true_type>,
        // enum 'AnchorSide'
        QtPrivate::TypeAndForceComplete<QCPLabelPainterPrivate::AnchorSide, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLabelPainterPrivate, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN13QCPAxisTickerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPAxisTickerE = QtMocHelpers::stringData(
    "QCPAxisTicker",
    "TickStepStrategy",
    "tssReadability",
    "tssMeetTickCount"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPAxisTickerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   19,

 // enum data: key, value
       2, uint(QCPAxisTicker::tssReadability),
       3, uint(QCPAxisTicker::tssMeetTickCount),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTicker::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN13QCPAxisTickerE.offsetsAndSizes,
    qt_meta_data_ZN13QCPAxisTickerE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPAxisTickerE_t,
        // enum 'TickStepStrategy'
        QtPrivate::TypeAndForceComplete<QCPAxisTicker::TickStepStrategy, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTicker, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN17QCPAxisTickerTimeE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17QCPAxisTickerTimeE = QtMocHelpers::stringData(
    "QCPAxisTickerTime",
    "TimeUnit",
    "tuMilliseconds",
    "tuSeconds",
    "tuMinutes",
    "tuHours",
    "tuDays"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN17QCPAxisTickerTimeE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    5,   19,

 // enum data: key, value
       2, uint(QCPAxisTickerTime::tuMilliseconds),
       3, uint(QCPAxisTickerTime::tuSeconds),
       4, uint(QCPAxisTickerTime::tuMinutes),
       5, uint(QCPAxisTickerTime::tuHours),
       6, uint(QCPAxisTickerTime::tuDays),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTickerTime::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPAxisTicker>::value,
    qt_meta_stringdata_ZN17QCPAxisTickerTimeE.offsetsAndSizes,
    qt_meta_data_ZN17QCPAxisTickerTimeE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN17QCPAxisTickerTimeE_t,
        // enum 'TimeUnit'
        QtPrivate::TypeAndForceComplete<QCPAxisTickerTime::TimeUnit, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTickerTime, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN18QCPAxisTickerFixedE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18QCPAxisTickerFixedE = QtMocHelpers::stringData(
    "QCPAxisTickerFixed",
    "ScaleStrategy",
    "ssNone",
    "ssMultiples",
    "ssPowers"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18QCPAxisTickerFixedE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   19,

 // enum data: key, value
       2, uint(QCPAxisTickerFixed::ssNone),
       3, uint(QCPAxisTickerFixed::ssMultiples),
       4, uint(QCPAxisTickerFixed::ssPowers),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTickerFixed::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPAxisTicker>::value,
    qt_meta_stringdata_ZN18QCPAxisTickerFixedE.offsetsAndSizes,
    qt_meta_data_ZN18QCPAxisTickerFixedE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18QCPAxisTickerFixedE_t,
        // enum 'ScaleStrategy'
        QtPrivate::TypeAndForceComplete<QCPAxisTickerFixed::ScaleStrategy, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTickerFixed, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN15QCPAxisTickerPiE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15QCPAxisTickerPiE = QtMocHelpers::stringData(
    "QCPAxisTickerPi",
    "FractionStyle",
    "fsFloatingPoint",
    "fsAsciiFractions",
    "fsUnicodeFractions"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15QCPAxisTickerPiE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   19,

 // enum data: key, value
       2, uint(QCPAxisTickerPi::fsFloatingPoint),
       3, uint(QCPAxisTickerPi::fsAsciiFractions),
       4, uint(QCPAxisTickerPi::fsUnicodeFractions),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTickerPi::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPAxisTicker>::value,
    qt_meta_stringdata_ZN15QCPAxisTickerPiE.offsetsAndSizes,
    qt_meta_data_ZN15QCPAxisTickerPiE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15QCPAxisTickerPiE_t,
        // enum 'FractionStyle'
        QtPrivate::TypeAndForceComplete<QCPAxisTickerPi::FractionStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTickerPi, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN7QCPGridE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN7QCPGridE = QtMocHelpers::stringData(
    "QCPGrid",
    "subGridVisible",
    "antialiasedSubGrid",
    "antialiasedZeroLine",
    "pen",
    "subGridPen",
    "zeroLinePen"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN7QCPGridE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::Bool, 0x00015103, uint(-1), 0,
       2, QMetaType::Bool, 0x00015103, uint(-1), 0,
       3, QMetaType::Bool, 0x00015103, uint(-1), 0,
       4, QMetaType::QPen, 0x00015103, uint(-1), 0,
       5, QMetaType::QPen, 0x00015103, uint(-1), 0,
       6, QMetaType::QPen, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN7QCPGridE.offsetsAndSizes,
    qt_meta_data_ZN7QCPGridE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN7QCPGridE_t,
        // property 'subGridVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'antialiasedSubGrid'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'antialiasedZeroLine'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'subGridPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'zeroLinePen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPGrid, std::true_type>
    >,
    nullptr
} };

void QCPGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPGrid *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->subGridVisible(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->antialiasedSubGrid(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->antialiasedZeroLine(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 4: *reinterpret_cast< QPen*>(_v) = _t->subGridPen(); break;
        case 5: *reinterpret_cast< QPen*>(_v) = _t->zeroLinePen(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSubGridVisible(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setAntialiasedSubGrid(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setAntialiasedZeroLine(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setSubGridPen(*reinterpret_cast< QPen*>(_v)); break;
        case 5: _t->setZeroLinePen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN7QCPGridE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN7QCPAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN7QCPAxisE = QtMocHelpers::stringData(
    "QCPAxis",
    "rangeChanged",
    "",
    "QCPRange",
    "newRange",
    "oldRange",
    "scaleTypeChanged",
    "QCPAxis::ScaleType",
    "scaleType",
    "selectionChanged",
    "QCPAxis::SelectableParts",
    "parts",
    "selectableChanged",
    "setScaleType",
    "type",
    "setRange",
    "range",
    "setSelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "axisType",
    "AxisType",
    "axisRect",
    "QCPAxisRect*",
    "ScaleType",
    "rangeReversed",
    "ticker",
    "QSharedPointer<QCPAxisTicker>",
    "ticks",
    "tickLabels",
    "tickLabelPadding",
    "tickLabelFont",
    "tickLabelColor",
    "tickLabelRotation",
    "tickLabelSide",
    "LabelSide",
    "numberFormat",
    "numberPrecision",
    "tickVector",
    "QList<double>",
    "tickVectorLabels",
    "tickLengthIn",
    "tickLengthOut",
    "subTicks",
    "subTickLengthIn",
    "subTickLengthOut",
    "basePen",
    "tickPen",
    "subTickPen",
    "labelFont",
    "labelColor",
    "label",
    "labelPadding",
    "padding",
    "offset",
    "SelectableParts",
    "selectedTickLabelFont",
    "selectedLabelFont",
    "selectedTickLabelColor",
    "selectedLabelColor",
    "selectedBasePen",
    "selectedTickPen",
    "selectedSubTickPen",
    "lowerEnding",
    "QCPLineEnding",
    "upperEnding",
    "grid",
    "QCPGrid*",
    "atLeft",
    "atRight",
    "atTop",
    "atBottom",
    "AxisTypes",
    "lsInside",
    "lsOutside",
    "stLinear",
    "stLogarithmic",
    "SelectablePart",
    "spNone",
    "spAxis",
    "spTickLabels",
    "spAxisLabel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN7QCPAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
      43,   97, // properties
       6,  312, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,   50 /* Public */,
       1,    2,   71,    2, 0x06,   52 /* Public */,
       6,    1,   76,    2, 0x06,   55 /* Public */,
       9,    1,   79,    2, 0x06,   57 /* Public */,
      12,    1,   82,    2, 0x06,   59 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    1,   85,    2, 0x0a,   61 /* Public */,
      15,    1,   88,    2, 0x0a,   63 /* Public */,
      17,    1,   91,    2, 0x0a,   65 /* Public */,
      19,    1,   94,    2, 0x0a,   67 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,   14,
    QMetaType::Void, 0x80000000 | 3,   16,
    QMetaType::Void, 0x80000000 | 10,   18,
    QMetaType::Void, 0x80000000 | 10,   20,

 // properties: name, type, flags, notifyId, revision
      21, 0x80000000 | 22, 0x00015009, uint(-1), 0,
      23, 0x80000000 | 24, 0x00015009, uint(-1), 0,
       8, 0x80000000 | 25, 0x0001510b, uint(2), 0,
      16, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      26, QMetaType::Bool, 0x00015103, uint(-1), 0,
      27, 0x80000000 | 28, 0x0001510b, uint(-1), 0,
      29, QMetaType::Bool, 0x00015103, uint(-1), 0,
      30, QMetaType::Bool, 0x00015103, uint(-1), 0,
      31, QMetaType::Int, 0x00015103, uint(-1), 0,
      32, QMetaType::QFont, 0x00015103, uint(-1), 0,
      33, QMetaType::QColor, 0x00015103, uint(-1), 0,
      34, QMetaType::Double, 0x00015103, uint(-1), 0,
      35, 0x80000000 | 36, 0x0001510b, uint(-1), 0,
      37, QMetaType::QString, 0x00015103, uint(-1), 0,
      38, QMetaType::Int, 0x00015103, uint(-1), 0,
      39, 0x80000000 | 40, 0x00015009, uint(-1), 0,
      41, QMetaType::QStringList, 0x00015001, uint(-1), 0,
      42, QMetaType::Int, 0x00015103, uint(-1), 0,
      43, QMetaType::Int, 0x00015103, uint(-1), 0,
      44, QMetaType::Bool, 0x00015103, uint(-1), 0,
      45, QMetaType::Int, 0x00015103, uint(-1), 0,
      46, QMetaType::Int, 0x00015103, uint(-1), 0,
      47, QMetaType::QPen, 0x00015103, uint(-1), 0,
      48, QMetaType::QPen, 0x00015103, uint(-1), 0,
      49, QMetaType::QPen, 0x00015103, uint(-1), 0,
      50, QMetaType::QFont, 0x00015103, uint(-1), 0,
      51, QMetaType::QColor, 0x00015103, uint(-1), 0,
      52, QMetaType::QString, 0x00015103, uint(-1), 0,
      53, QMetaType::Int, 0x00015103, uint(-1), 0,
      54, QMetaType::Int, 0x00015103, uint(-1), 0,
      55, QMetaType::Int, 0x00015103, uint(-1), 0,
      20, 0x80000000 | 56, 0x0001510b, uint(3), 0,
      18, 0x80000000 | 56, 0x0001510b, uint(4), 0,
      57, QMetaType::QFont, 0x00015103, uint(-1), 0,
      58, QMetaType::QFont, 0x00015103, uint(-1), 0,
      59, QMetaType::QColor, 0x00015103, uint(-1), 0,
      60, QMetaType::QColor, 0x00015103, uint(-1), 0,
      61, QMetaType::QPen, 0x00015103, uint(-1), 0,
      62, QMetaType::QPen, 0x00015103, uint(-1), 0,
      63, QMetaType::QPen, 0x00015103, uint(-1), 0,
      64, 0x80000000 | 65, 0x0001510b, uint(-1), 0,
      66, 0x80000000 | 65, 0x0001510b, uint(-1), 0,
      67, 0x80000000 | 68, 0x00015009, uint(-1), 0,

 // enums: name, alias, flags, count, data
      22,   22, 0x0,    4,  342,
      73,   22, 0x1,    4,  350,
      36,   36, 0x0,    2,  358,
      25,   25, 0x0,    2,  362,
      78,   78, 0x0,    4,  366,
      56,   78, 0x1,    4,  374,

 // enum data: key, value
      69, uint(QCPAxis::atLeft),
      70, uint(QCPAxis::atRight),
      71, uint(QCPAxis::atTop),
      72, uint(QCPAxis::atBottom),
      69, uint(QCPAxis::atLeft),
      70, uint(QCPAxis::atRight),
      71, uint(QCPAxis::atTop),
      72, uint(QCPAxis::atBottom),
      74, uint(QCPAxis::lsInside),
      75, uint(QCPAxis::lsOutside),
      76, uint(QCPAxis::stLinear),
      77, uint(QCPAxis::stLogarithmic),
      79, uint(QCPAxis::spNone),
      80, uint(QCPAxis::spAxis),
      81, uint(QCPAxis::spTickLabels),
      82, uint(QCPAxis::spAxisLabel),
      79, uint(QCPAxis::spNone),
      80, uint(QCPAxis::spAxis),
      81, uint(QCPAxis::spTickLabels),
      82, uint(QCPAxis::spAxisLabel),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN7QCPAxisE.offsetsAndSizes,
    qt_meta_data_ZN7QCPAxisE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN7QCPAxisE_t,
        // property 'axisType'
        QtPrivate::TypeAndForceComplete<AxisType, std::true_type>,
        // property 'axisRect'
        QtPrivate::TypeAndForceComplete<QCPAxisRect*, std::true_type>,
        // property 'scaleType'
        QtPrivate::TypeAndForceComplete<ScaleType, std::true_type>,
        // property 'range'
        QtPrivate::TypeAndForceComplete<QCPRange, std::true_type>,
        // property 'rangeReversed'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'ticker'
        QtPrivate::TypeAndForceComplete<QSharedPointer<QCPAxisTicker>, std::true_type>,
        // property 'ticks'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'tickLabels'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'tickLabelPadding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickLabelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'tickLabelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'tickLabelRotation'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'tickLabelSide'
        QtPrivate::TypeAndForceComplete<LabelSide, std::true_type>,
        // property 'numberFormat'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'numberPrecision'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickVector'
        QtPrivate::TypeAndForceComplete<QList<double>, std::true_type>,
        // property 'tickVectorLabels'
        QtPrivate::TypeAndForceComplete<QList<QString>, std::true_type>,
        // property 'tickLengthIn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickLengthOut'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'subTicks'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'subTickLengthIn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'subTickLengthOut'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'basePen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'tickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'subTickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'labelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'labelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'label'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'labelPadding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'padding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'offset'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'selectedParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectableParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectedTickLabelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedLabelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTickLabelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedLabelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedBasePen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedTickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedSubTickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'lowerEnding'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'upperEnding'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'grid'
        QtPrivate::TypeAndForceComplete<QCPGrid*, std::true_type>,
        // enum 'AxisType'
        QtPrivate::TypeAndForceComplete<QCPAxis::AxisType, std::true_type>,
        // enum 'AxisTypes'
        QtPrivate::TypeAndForceComplete<QCPAxis::AxisTypes, std::true_type>,
        // enum 'LabelSide'
        QtPrivate::TypeAndForceComplete<QCPAxis::LabelSide, std::true_type>,
        // enum 'ScaleType'
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::true_type>,
        // enum 'SelectablePart'
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectablePart, std::true_type>,
        // enum 'SelectableParts'
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectableParts, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxis, std::true_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'scaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>,
        // method 'setScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'setRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[2]))); break;
        case 2: _t->scaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 3: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 4: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 5: _t->setScaleType((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 6: _t->setRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 7: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 8: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPAxis::*)(const QCPRange & );
            if (_q_method_type _q_method = &QCPAxis::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAxis::*)(const QCPRange & , const QCPRange & );
            if (_q_method_type _q_method = &QCPAxis::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAxis::*)(QCPAxis::ScaleType );
            if (_q_method_type _q_method = &QCPAxis::scaleTypeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAxis::*)(const QCPAxis::SelectableParts & );
            if (_q_method_type _q_method = &QCPAxis::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAxis::*)(const QCPAxis::SelectableParts & );
            if (_q_method_type _q_method = &QCPAxis::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxisRect* >(); break;
        case 42:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPGrid* >(); break;
        case 15:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<QCPAxisTicker> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< AxisType*>(_v) = _t->axisType(); break;
        case 1: *reinterpret_cast< QCPAxisRect**>(_v) = _t->axisRect(); break;
        case 2: *reinterpret_cast< ScaleType*>(_v) = _t->scaleType(); break;
        case 3: *reinterpret_cast< QCPRange*>(_v) = _t->range(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->rangeReversed(); break;
        case 5: *reinterpret_cast< QSharedPointer<QCPAxisTicker>*>(_v) = _t->ticker(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->ticks(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->tickLabels(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->tickLabelPadding(); break;
        case 9: *reinterpret_cast< QFont*>(_v) = _t->tickLabelFont(); break;
        case 10: *reinterpret_cast< QColor*>(_v) = _t->tickLabelColor(); break;
        case 11: *reinterpret_cast< double*>(_v) = _t->tickLabelRotation(); break;
        case 12: *reinterpret_cast< LabelSide*>(_v) = _t->tickLabelSide(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->numberFormat(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->numberPrecision(); break;
        case 15: *reinterpret_cast< QList<double>*>(_v) = _t->tickVector(); break;
        case 16: *reinterpret_cast< QList<QString>*>(_v) = _t->tickVectorLabels(); break;
        case 17: *reinterpret_cast< int*>(_v) = _t->tickLengthIn(); break;
        case 18: *reinterpret_cast< int*>(_v) = _t->tickLengthOut(); break;
        case 19: *reinterpret_cast< bool*>(_v) = _t->subTicks(); break;
        case 20: *reinterpret_cast< int*>(_v) = _t->subTickLengthIn(); break;
        case 21: *reinterpret_cast< int*>(_v) = _t->subTickLengthOut(); break;
        case 22: *reinterpret_cast< QPen*>(_v) = _t->basePen(); break;
        case 23: *reinterpret_cast< QPen*>(_v) = _t->tickPen(); break;
        case 24: *reinterpret_cast< QPen*>(_v) = _t->subTickPen(); break;
        case 25: *reinterpret_cast< QFont*>(_v) = _t->labelFont(); break;
        case 26: *reinterpret_cast< QColor*>(_v) = _t->labelColor(); break;
        case 27: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        case 28: *reinterpret_cast< int*>(_v) = _t->labelPadding(); break;
        case 29: *reinterpret_cast< int*>(_v) = _t->padding(); break;
        case 30: *reinterpret_cast< int*>(_v) = _t->offset(); break;
        case 31: *reinterpret_cast<int*>(_v) = QFlag(_t->selectedParts()); break;
        case 32: *reinterpret_cast<int*>(_v) = QFlag(_t->selectableParts()); break;
        case 33: *reinterpret_cast< QFont*>(_v) = _t->selectedTickLabelFont(); break;
        case 34: *reinterpret_cast< QFont*>(_v) = _t->selectedLabelFont(); break;
        case 35: *reinterpret_cast< QColor*>(_v) = _t->selectedTickLabelColor(); break;
        case 36: *reinterpret_cast< QColor*>(_v) = _t->selectedLabelColor(); break;
        case 37: *reinterpret_cast< QPen*>(_v) = _t->selectedBasePen(); break;
        case 38: *reinterpret_cast< QPen*>(_v) = _t->selectedTickPen(); break;
        case 39: *reinterpret_cast< QPen*>(_v) = _t->selectedSubTickPen(); break;
        case 40: *reinterpret_cast< QCPLineEnding*>(_v) = _t->lowerEnding(); break;
        case 41: *reinterpret_cast< QCPLineEnding*>(_v) = _t->upperEnding(); break;
        case 42: *reinterpret_cast< QCPGrid**>(_v) = _t->grid(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setScaleType(*reinterpret_cast< ScaleType*>(_v)); break;
        case 3: _t->setRange(*reinterpret_cast< QCPRange*>(_v)); break;
        case 4: _t->setRangeReversed(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setTicker(*reinterpret_cast< QSharedPointer<QCPAxisTicker>*>(_v)); break;
        case 6: _t->setTicks(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->setTickLabels(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setTickLabelPadding(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setTickLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 10: _t->setTickLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 11: _t->setTickLabelRotation(*reinterpret_cast< double*>(_v)); break;
        case 12: _t->setTickLabelSide(*reinterpret_cast< LabelSide*>(_v)); break;
        case 13: _t->setNumberFormat(*reinterpret_cast< QString*>(_v)); break;
        case 14: _t->setNumberPrecision(*reinterpret_cast< int*>(_v)); break;
        case 17: _t->setTickLengthIn(*reinterpret_cast< int*>(_v)); break;
        case 18: _t->setTickLengthOut(*reinterpret_cast< int*>(_v)); break;
        case 19: _t->setSubTicks(*reinterpret_cast< bool*>(_v)); break;
        case 20: _t->setSubTickLengthIn(*reinterpret_cast< int*>(_v)); break;
        case 21: _t->setSubTickLengthOut(*reinterpret_cast< int*>(_v)); break;
        case 22: _t->setBasePen(*reinterpret_cast< QPen*>(_v)); break;
        case 23: _t->setTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 24: _t->setSubTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 25: _t->setLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 26: _t->setLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 27: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 28: _t->setLabelPadding(*reinterpret_cast< int*>(_v)); break;
        case 29: _t->setPadding(*reinterpret_cast< int*>(_v)); break;
        case 30: _t->setOffset(*reinterpret_cast< int*>(_v)); break;
        case 31: _t->setSelectedParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 32: _t->setSelectableParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 33: _t->setSelectedTickLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 34: _t->setSelectedLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 35: _t->setSelectedTickLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 36: _t->setSelectedLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 37: _t->setSelectedBasePen(*reinterpret_cast< QPen*>(_v)); break;
        case 38: _t->setSelectedTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 39: _t->setSelectedSubTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 40: _t->setLowerEnding(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        case 41: _t->setUpperEnding(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN7QCPAxisE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void QCPAxis::rangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAxis::rangeChanged(const QCPRange & _t1, const QCPRange & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPAxis::scaleTypeChanged(QCPAxis::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPAxis::selectionChanged(const QCPAxis::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCPAxis::selectableChanged(const QCPAxis::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
namespace {
struct qt_meta_tag_ZN15QCPScatterStyleE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15QCPScatterStyleE = QtMocHelpers::stringData(
    "QCPScatterStyle",
    "ScatterProperty",
    "spNone",
    "spPen",
    "spBrush",
    "spSize",
    "spShape",
    "spAll",
    "ScatterProperties",
    "ScatterShape",
    "ssNone",
    "ssDot",
    "ssCross",
    "ssPlus",
    "ssCircle",
    "ssDisc",
    "ssSquare",
    "ssDiamond",
    "ssStar",
    "ssTriangle",
    "ssTriangleInverted",
    "ssCrossSquare",
    "ssPlusSquare",
    "ssCrossCircle",
    "ssPlusCircle",
    "ssPeace",
    "ssPixmap",
    "ssCustom"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15QCPScatterStyleE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    6,   29,
       8,    1, 0x1,    6,   41,
       9,    9, 0x0,   18,   53,

 // enum data: key, value
       2, uint(QCPScatterStyle::spNone),
       3, uint(QCPScatterStyle::spPen),
       4, uint(QCPScatterStyle::spBrush),
       5, uint(QCPScatterStyle::spSize),
       6, uint(QCPScatterStyle::spShape),
       7, uint(QCPScatterStyle::spAll),
       2, uint(QCPScatterStyle::spNone),
       3, uint(QCPScatterStyle::spPen),
       4, uint(QCPScatterStyle::spBrush),
       5, uint(QCPScatterStyle::spSize),
       6, uint(QCPScatterStyle::spShape),
       7, uint(QCPScatterStyle::spAll),
      10, uint(QCPScatterStyle::ssNone),
      11, uint(QCPScatterStyle::ssDot),
      12, uint(QCPScatterStyle::ssCross),
      13, uint(QCPScatterStyle::ssPlus),
      14, uint(QCPScatterStyle::ssCircle),
      15, uint(QCPScatterStyle::ssDisc),
      16, uint(QCPScatterStyle::ssSquare),
      17, uint(QCPScatterStyle::ssDiamond),
      18, uint(QCPScatterStyle::ssStar),
      19, uint(QCPScatterStyle::ssTriangle),
      20, uint(QCPScatterStyle::ssTriangleInverted),
      21, uint(QCPScatterStyle::ssCrossSquare),
      22, uint(QCPScatterStyle::ssPlusSquare),
      23, uint(QCPScatterStyle::ssCrossCircle),
      24, uint(QCPScatterStyle::ssPlusCircle),
      25, uint(QCPScatterStyle::ssPeace),
      26, uint(QCPScatterStyle::ssPixmap),
      27, uint(QCPScatterStyle::ssCustom),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPScatterStyle::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN15QCPScatterStyleE.offsetsAndSizes,
    qt_meta_data_ZN15QCPScatterStyleE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15QCPScatterStyleE_t,
        // enum 'ScatterProperty'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle::ScatterProperty, std::true_type>,
        // enum 'ScatterProperties'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle::ScatterProperties, std::true_type>,
        // enum 'ScatterShape'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle::ScatterShape, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN21QCPSelectionDecoratorE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN21QCPSelectionDecoratorE = QtMocHelpers::stringData(
    "QCPSelectionDecorator"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN21QCPSelectionDecoratorE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPSelectionDecorator::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN21QCPSelectionDecoratorE.offsetsAndSizes,
    qt_meta_data_ZN21QCPSelectionDecoratorE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN21QCPSelectionDecoratorE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPSelectionDecorator, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN20QCPAbstractPlottableE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20QCPAbstractPlottableE = QtMocHelpers::stringData(
    "QCPAbstractPlottable",
    "selectionChanged",
    "",
    "selected",
    "QCPDataSelection",
    "selection",
    "selectableChanged",
    "QCP::SelectionType",
    "selectable",
    "setSelectable",
    "setSelection",
    "name",
    "antialiasedFill",
    "antialiasedScatters",
    "pen",
    "brush",
    "keyAxis",
    "QCPAxis*",
    "valueAxis",
    "selectionDecorator",
    "QCPSelectionDecorator*"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20QCPAbstractPlottableE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      10,   59, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,   11 /* Public */,
       1,    1,   47,    2, 0x06,   13 /* Public */,
       6,    1,   50,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   53,    2, 0x0a,   17 /* Public */,
      10,    1,   56,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 4,    5,

 // properties: name, type, flags, notifyId, revision
      11, QMetaType::QString, 0x00015103, uint(-1), 0,
      12, QMetaType::Bool, 0x00015103, uint(-1), 0,
      13, QMetaType::Bool, 0x00015103, uint(-1), 0,
      14, QMetaType::QPen, 0x00015103, uint(-1), 0,
      15, QMetaType::QBrush, 0x00015103, uint(-1), 0,
      16, 0x80000000 | 17, 0x0001510b, uint(-1), 0,
      18, 0x80000000 | 17, 0x0001510b, uint(-1), 0,
       8, 0x80000000 | 7, 0x0001510b, uint(2), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(0), 0,
      19, 0x80000000 | 20, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_ZN20QCPAbstractPlottableE[] = {
    QMetaObject::SuperData::link<QCP::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QCPAbstractPlottable::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN20QCPAbstractPlottableE.offsetsAndSizes,
    qt_meta_data_ZN20QCPAbstractPlottableE,
    qt_static_metacall,
    qt_meta_extradata_ZN20QCPAbstractPlottableE,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN20QCPAbstractPlottableE_t,
        // property 'name'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'antialiasedFill'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'antialiasedScatters'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'keyAxis'
        QtPrivate::TypeAndForceComplete<QCPAxis*, std::true_type>,
        // property 'valueAxis'
        QtPrivate::TypeAndForceComplete<QCPAxis*, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::true_type>,
        // property 'selection'
        QtPrivate::TypeAndForceComplete<QCPDataSelection, std::true_type>,
        // property 'selectionDecorator'
        QtPrivate::TypeAndForceComplete<QCPSelectionDecorator*, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPDataSelection &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPDataSelection, std::false_type>
    >,
    nullptr
} };

void QCPAbstractPlottable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPAbstractPlottable *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        case 2: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 3: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 4: _t->setSelection((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPAbstractPlottable::*)(bool );
            if (_q_method_type _q_method = &QCPAbstractPlottable::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAbstractPlottable::*)(const QCPDataSelection & );
            if (_q_method_type _q_method = &QCPAbstractPlottable::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAbstractPlottable::*)(QCP::SelectionType );
            if (_q_method_type _q_method = &QCPAbstractPlottable::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
        case 8:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPDataSelection >(); break;
        case 9:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPSelectionDecorator* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->antialiasedFill(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->antialiasedScatters(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 5: *reinterpret_cast< QCPAxis**>(_v) = _t->keyAxis(); break;
        case 6: *reinterpret_cast< QCPAxis**>(_v) = _t->valueAxis(); break;
        case 7: *reinterpret_cast< QCP::SelectionType*>(_v) = _t->selectable(); break;
        case 8: *reinterpret_cast< QCPDataSelection*>(_v) = _t->selection(); break;
        case 9: *reinterpret_cast< QCPSelectionDecorator**>(_v) = _t->selectionDecorator(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setAntialiasedFill(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setAntialiasedScatters(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setKeyAxis(*reinterpret_cast< QCPAxis**>(_v)); break;
        case 6: _t->setValueAxis(*reinterpret_cast< QCPAxis**>(_v)); break;
        case 7: _t->setSelectable(*reinterpret_cast< QCP::SelectionType*>(_v)); break;
        case 8: _t->setSelection(*reinterpret_cast< QCPDataSelection*>(_v)); break;
        case 9: _t->setSelectionDecorator(*reinterpret_cast< QCPSelectionDecorator**>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPAbstractPlottable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAbstractPlottable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20QCPAbstractPlottableE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPAbstractPlottable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QCPAbstractPlottable::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAbstractPlottable::selectionChanged(const QCPDataSelection & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPAbstractPlottable::selectableChanged(QCP::SelectionType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_tag_ZN13QCPItemAnchorE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPItemAnchorE = QtMocHelpers::stringData(
    "QCPItemAnchor"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPItemAnchorE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemAnchor::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN13QCPItemAnchorE.offsetsAndSizes,
    qt_meta_data_ZN13QCPItemAnchorE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPItemAnchorE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemAnchor, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN15QCPItemPositionE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15QCPItemPositionE = QtMocHelpers::stringData(
    "QCPItemPosition",
    "PositionType",
    "ptAbsolute",
    "ptViewportRatio",
    "ptAxisRectRatio",
    "ptPlotCoords"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15QCPItemPositionE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   19,

 // enum data: key, value
       2, uint(QCPItemPosition::ptAbsolute),
       3, uint(QCPItemPosition::ptViewportRatio),
       4, uint(QCPItemPosition::ptAxisRectRatio),
       5, uint(QCPItemPosition::ptPlotCoords),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemPosition::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPItemAnchor>::value,
    qt_meta_stringdata_ZN15QCPItemPositionE.offsetsAndSizes,
    qt_meta_data_ZN15QCPItemPositionE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15QCPItemPositionE_t,
        // enum 'PositionType'
        QtPrivate::TypeAndForceComplete<QCPItemPosition::PositionType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemPosition, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN15QCPAbstractItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15QCPAbstractItemE = QtMocHelpers::stringData(
    "QCPAbstractItem",
    "selectionChanged",
    "",
    "selected",
    "selectableChanged",
    "selectable",
    "setSelectable",
    "setSelected",
    "clipToAxisRect",
    "clipAxisRect",
    "QCPAxisRect*"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15QCPAbstractItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    5 /* Public */,
       4,    1,   41,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   44,    2, 0x0a,    9 /* Public */,
       7,    1,   47,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags, notifyId, revision
       8, QMetaType::Bool, 0x00015103, uint(-1), 0,
       9, 0x80000000 | 10, 0x0001510b, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(1), 0,
       3, QMetaType::Bool, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAbstractItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN15QCPAbstractItemE.offsetsAndSizes,
    qt_meta_data_ZN15QCPAbstractItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15QCPAbstractItemE_t,
        // property 'clipToAxisRect'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'clipAxisRect'
        QtPrivate::TypeAndForceComplete<QCPAxisRect*, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAbstractItem, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QCPAbstractItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPAbstractItem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->setSelected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPAbstractItem::*)(bool );
            if (_q_method_type _q_method = &QCPAbstractItem::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAbstractItem::*)(bool );
            if (_q_method_type _q_method = &QCPAbstractItem::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxisRect* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->clipToAxisRect(); break;
        case 1: *reinterpret_cast< QCPAxisRect**>(_v) = _t->clipAxisRect(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->selectable(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->selected(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setClipToAxisRect(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setClipAxisRect(*reinterpret_cast< QCPAxisRect**>(_v)); break;
        case 2: _t->setSelectable(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPAbstractItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAbstractItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN15QCPAbstractItemE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPAbstractItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QCPAbstractItem::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAbstractItem::selectableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_tag_ZN11QCustomPlotE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QCustomPlotE = QtMocHelpers::stringData(
    "QCustomPlot",
    "mouseDoubleClick",
    "",
    "QMouseEvent*",
    "event",
    "mousePress",
    "mouseMove",
    "mouseRelease",
    "mouseWheel",
    "QWheelEvent*",
    "plottableClick",
    "QCPAbstractPlottable*",
    "plottable",
    "dataIndex",
    "plottableDoubleClick",
    "itemClick",
    "QCPAbstractItem*",
    "item",
    "itemDoubleClick",
    "axisClick",
    "QCPAxis*",
    "axis",
    "QCPAxis::SelectablePart",
    "part",
    "axisDoubleClick",
    "legendClick",
    "QCPLegend*",
    "legend",
    "QCPAbstractLegendItem*",
    "legendDoubleClick",
    "selectionChangedByUser",
    "beforeReplot",
    "afterLayout",
    "afterReplot",
    "rescaleAxes",
    "onlyVisiblePlottables",
    "deselectAll",
    "replot",
    "QCustomPlot::RefreshPriority",
    "refreshPriority",
    "processRectSelection",
    "rect",
    "processRectZoom",
    "processPointSelection",
    "viewport",
    "background",
    "backgroundScaled",
    "backgroundScaledMode",
    "Qt::AspectRatioMode",
    "plotLayout",
    "QCPLayoutGrid*",
    "autoAddPlottableToLegend",
    "selectionTolerance",
    "noAntialiasingOnDrag",
    "multiSelectModifier",
    "Qt::KeyboardModifier",
    "openGl",
    "LayerInsertMode",
    "limBelow",
    "limAbove",
    "RefreshPriority",
    "rpImmediateRefresh",
    "rpQueuedRefresh",
    "rpRefreshHint",
    "rpQueuedReplot"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QCustomPlotE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
      10,  257, // properties
       2,  307, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  164,    2, 0x06,   13 /* Public */,
       5,    1,  167,    2, 0x06,   15 /* Public */,
       6,    1,  170,    2, 0x06,   17 /* Public */,
       7,    1,  173,    2, 0x06,   19 /* Public */,
       8,    1,  176,    2, 0x06,   21 /* Public */,
      10,    3,  179,    2, 0x06,   23 /* Public */,
      14,    3,  186,    2, 0x06,   27 /* Public */,
      15,    2,  193,    2, 0x06,   31 /* Public */,
      18,    2,  198,    2, 0x06,   34 /* Public */,
      19,    3,  203,    2, 0x06,   37 /* Public */,
      24,    3,  210,    2, 0x06,   41 /* Public */,
      25,    3,  217,    2, 0x06,   45 /* Public */,
      29,    3,  224,    2, 0x06,   49 /* Public */,
      30,    0,  231,    2, 0x06,   53 /* Public */,
      31,    0,  232,    2, 0x06,   54 /* Public */,
      32,    0,  233,    2, 0x06,   55 /* Public */,
      33,    0,  234,    2, 0x06,   56 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      34,    1,  235,    2, 0x0a,   57 /* Public */,
      34,    0,  238,    2, 0x2a,   59 /* Public | MethodCloned */,
      36,    0,  239,    2, 0x0a,   60 /* Public */,
      37,    1,  240,    2, 0x0a,   61 /* Public */,
      37,    0,  243,    2, 0x2a,   63 /* Public | MethodCloned */,
      40,    2,  244,    2, 0x09,   64 /* Protected */,
      42,    2,  249,    2, 0x09,   67 /* Protected */,
      43,    1,  254,    2, 0x09,   70 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, 0x80000000 | 3,   12,   13,    4,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, 0x80000000 | 3,   12,   13,    4,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 3,   17,    4,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 3,   17,    4,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 3,   21,   23,    4,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 3,   21,   23,    4,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 3,   27,   17,    4,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 3,   27,   17,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,   41,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,   41,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // properties: name, type, flags, notifyId, revision
      44, QMetaType::QRect, 0x00015103, uint(-1), 0,
      45, QMetaType::QPixmap, 0x00015103, uint(-1), 0,
      46, QMetaType::Bool, 0x00015103, uint(-1), 0,
      47, 0x80000000 | 48, 0x0001510b, uint(-1), 0,
      49, 0x80000000 | 50, 0x00015009, uint(-1), 0,
      51, QMetaType::Bool, 0x00015103, uint(-1), 0,
      52, QMetaType::Int, 0x00015103, uint(-1), 0,
      53, QMetaType::Bool, 0x00015103, uint(-1), 0,
      54, 0x80000000 | 55, 0x0001510b, uint(-1), 0,
      56, QMetaType::Bool, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
      57,   57, 0x0,    2,  317,
      60,   60, 0x0,    4,  321,

 // enum data: key, value
      58, uint(QCustomPlot::limBelow),
      59, uint(QCustomPlot::limAbove),
      61, uint(QCustomPlot::rpImmediateRefresh),
      62, uint(QCustomPlot::rpQueuedRefresh),
      63, uint(QCustomPlot::rpRefreshHint),
      64, uint(QCustomPlot::rpQueuedReplot),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCustomPlot::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN11QCustomPlotE.offsetsAndSizes,
    qt_meta_data_ZN11QCustomPlotE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QCustomPlotE_t,
        // property 'viewport'
        QtPrivate::TypeAndForceComplete<QRect, std::true_type>,
        // property 'background'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // property 'backgroundScaled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'backgroundScaledMode'
        QtPrivate::TypeAndForceComplete<Qt::AspectRatioMode, std::true_type>,
        // property 'plotLayout'
        QtPrivate::TypeAndForceComplete<QCPLayoutGrid*, std::true_type>,
        // property 'autoAddPlottableToLegend'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selectionTolerance'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'noAntialiasingOnDrag'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'multiSelectModifier'
        QtPrivate::TypeAndForceComplete<Qt::KeyboardModifier, std::true_type>,
        // property 'openGl'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // enum 'LayerInsertMode'
        QtPrivate::TypeAndForceComplete<QCustomPlot::LayerInsertMode, std::true_type>,
        // enum 'RefreshPriority'
        QtPrivate::TypeAndForceComplete<QCustomPlot::RefreshPriority, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCustomPlot, std::true_type>,
        // method 'mouseDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mousePress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseRelease'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseWheel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWheelEvent *, std::false_type>,
        // method 'plottableClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'plottableDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'itemClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'itemDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'axisClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectablePart, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'axisDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectablePart, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'legendClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'legendDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'selectionChangedByUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'beforeReplot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afterLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afterReplot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rescaleAxes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'rescaleAxes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deselectAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCustomPlot::RefreshPriority, std::false_type>,
        // method 'replot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processRectSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QRect, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'processRectZoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QRect, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'processPointSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>
    >,
    nullptr
} };

void QCustomPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCustomPlot *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->mouseDoubleClick((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 1: _t->mousePress((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 2: _t->mouseMove((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->mouseRelease((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->mouseWheel((*reinterpret_cast< std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 5: _t->plottableClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractPlottable*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 6: _t->plottableDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractPlottable*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 7: _t->itemClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 8: _t->itemDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 9: _t->axisClick((*reinterpret_cast< std::add_pointer_t<QCPAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectablePart>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 10: _t->axisDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectablePart>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 11: _t->legendClick((*reinterpret_cast< std::add_pointer_t<QCPLegend*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAbstractLegendItem*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 12: _t->legendDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPLegend*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAbstractLegendItem*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 13: _t->selectionChangedByUser(); break;
        case 14: _t->beforeReplot(); break;
        case 15: _t->afterLayout(); break;
        case 16: _t->afterReplot(); break;
        case 17: _t->rescaleAxes((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->rescaleAxes(); break;
        case 19: _t->deselectAll(); break;
        case 20: _t->replot((*reinterpret_cast< std::add_pointer_t<QCustomPlot::RefreshPriority>>(_a[1]))); break;
        case 21: _t->replot(); break;
        case 22: _t->processRectSelection((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 23: _t->processRectZoom((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 24: _t->processPointSelection((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractItem* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractItem* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLegend* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLegend* >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCustomPlot::RefreshPriority >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCustomPlot::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::mouseDoubleClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::mousePress; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::mouseMove; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::mouseRelease; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QWheelEvent * );
            if (_q_method_type _q_method = &QCustomPlot::mouseWheel; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPAbstractPlottable * , int , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::plottableClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPAbstractPlottable * , int , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::plottableDoubleClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPAbstractItem * , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::itemClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPAbstractItem * , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::itemDoubleClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPAxis * , QCPAxis::SelectablePart , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::axisClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPAxis * , QCPAxis::SelectablePart , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::axisDoubleClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPLegend * , QCPAbstractLegendItem * , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::legendClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)(QCPLegend * , QCPAbstractLegendItem * , QMouseEvent * );
            if (_q_method_type _q_method = &QCustomPlot::legendDoubleClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)();
            if (_q_method_type _q_method = &QCustomPlot::selectionChangedByUser; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)();
            if (_q_method_type _q_method = &QCustomPlot::beforeReplot; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)();
            if (_q_method_type _q_method = &QCustomPlot::afterLayout; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _q_method_type = void (QCustomPlot::*)();
            if (_q_method_type _q_method = &QCustomPlot::afterReplot; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayoutGrid* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QRect*>(_v) = _t->viewport(); break;
        case 1: *reinterpret_cast< QPixmap*>(_v) = _t->background(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->backgroundScaled(); break;
        case 3: *reinterpret_cast< Qt::AspectRatioMode*>(_v) = _t->backgroundScaledMode(); break;
        case 4: *reinterpret_cast< QCPLayoutGrid**>(_v) = _t->plotLayout(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->autoAddPlottableToLegend(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->selectionTolerance(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->noAntialiasingOnDrag(); break;
        case 8: *reinterpret_cast< Qt::KeyboardModifier*>(_v) = _t->multiSelectModifier(); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->openGl(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setViewport(*reinterpret_cast< QRect*>(_v)); break;
        case 1: _t->setBackground(*reinterpret_cast< QPixmap*>(_v)); break;
        case 2: _t->setBackgroundScaled(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setBackgroundScaledMode(*reinterpret_cast< Qt::AspectRatioMode*>(_v)); break;
        case 5: _t->setAutoAddPlottableToLegend(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setSelectionTolerance(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setNoAntialiasingOnDrag(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setMultiSelectModifier(*reinterpret_cast< Qt::KeyboardModifier*>(_v)); break;
        case 9: _t->setOpenGl(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCustomPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCustomPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QCustomPlotE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QCustomPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QCustomPlot::mouseDoubleClick(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCustomPlot::mousePress(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCustomPlot::mouseMove(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCustomPlot::mouseRelease(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCustomPlot::mouseWheel(QWheelEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCustomPlot::plottableClick(QCPAbstractPlottable * _t1, int _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QCustomPlot::plottableDoubleClick(QCPAbstractPlottable * _t1, int _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QCustomPlot::itemClick(QCPAbstractItem * _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QCustomPlot::itemDoubleClick(QCPAbstractItem * _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QCustomPlot::axisClick(QCPAxis * _t1, QCPAxis::SelectablePart _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QCustomPlot::axisDoubleClick(QCPAxis * _t1, QCPAxis::SelectablePart _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QCustomPlot::legendClick(QCPLegend * _t1, QCPAbstractLegendItem * _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QCustomPlot::legendDoubleClick(QCPLegend * _t1, QCPAbstractLegendItem * _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QCustomPlot::selectionChangedByUser()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void QCustomPlot::beforeReplot()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void QCustomPlot::afterLayout()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void QCustomPlot::afterReplot()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}
namespace {
struct qt_meta_tag_ZN16QCPColorGradientE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16QCPColorGradientE = QtMocHelpers::stringData(
    "QCPColorGradient",
    "ColorInterpolation",
    "ciRGB",
    "ciHSV",
    "NanHandling",
    "nhNone",
    "nhLowestColor",
    "nhHighestColor",
    "nhTransparent",
    "nhNanColor",
    "GradientPreset",
    "gpGrayscale",
    "gpHot",
    "gpCold",
    "gpNight",
    "gpCandy",
    "gpGeography",
    "gpIon",
    "gpThermal",
    "gpPolar",
    "gpSpectrum",
    "gpJet",
    "gpHues"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16QCPColorGradientE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   29,
       4,    4, 0x0,    5,   33,
      10,   10, 0x0,   12,   43,

 // enum data: key, value
       2, uint(QCPColorGradient::ciRGB),
       3, uint(QCPColorGradient::ciHSV),
       5, uint(QCPColorGradient::nhNone),
       6, uint(QCPColorGradient::nhLowestColor),
       7, uint(QCPColorGradient::nhHighestColor),
       8, uint(QCPColorGradient::nhTransparent),
       9, uint(QCPColorGradient::nhNanColor),
      11, uint(QCPColorGradient::gpGrayscale),
      12, uint(QCPColorGradient::gpHot),
      13, uint(QCPColorGradient::gpCold),
      14, uint(QCPColorGradient::gpNight),
      15, uint(QCPColorGradient::gpCandy),
      16, uint(QCPColorGradient::gpGeography),
      17, uint(QCPColorGradient::gpIon),
      18, uint(QCPColorGradient::gpThermal),
      19, uint(QCPColorGradient::gpPolar),
      20, uint(QCPColorGradient::gpSpectrum),
      21, uint(QCPColorGradient::gpJet),
      22, uint(QCPColorGradient::gpHues),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPColorGradient::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN16QCPColorGradientE.offsetsAndSizes,
    qt_meta_data_ZN16QCPColorGradientE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16QCPColorGradientE_t,
        // enum 'ColorInterpolation'
        QtPrivate::TypeAndForceComplete<QCPColorGradient::ColorInterpolation, std::true_type>,
        // enum 'NanHandling'
        QtPrivate::TypeAndForceComplete<QCPColorGradient::NanHandling, std::true_type>,
        // enum 'GradientPreset'
        QtPrivate::TypeAndForceComplete<QCPColorGradient::GradientPreset, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorGradient, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN28QCPSelectionDecoratorBracketE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN28QCPSelectionDecoratorBracketE = QtMocHelpers::stringData(
    "QCPSelectionDecoratorBracket",
    "BracketStyle",
    "bsSquareBracket",
    "bsHalfEllipse",
    "bsEllipse",
    "bsPlus",
    "bsUserStyle"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN28QCPSelectionDecoratorBracketE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    5,   19,

 // enum data: key, value
       2, uint(QCPSelectionDecoratorBracket::bsSquareBracket),
       3, uint(QCPSelectionDecoratorBracket::bsHalfEllipse),
       4, uint(QCPSelectionDecoratorBracket::bsEllipse),
       5, uint(QCPSelectionDecoratorBracket::bsPlus),
       6, uint(QCPSelectionDecoratorBracket::bsUserStyle),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPSelectionDecoratorBracket::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPSelectionDecorator>::value,
    qt_meta_stringdata_ZN28QCPSelectionDecoratorBracketE.offsetsAndSizes,
    qt_meta_data_ZN28QCPSelectionDecoratorBracketE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN28QCPSelectionDecoratorBracketE_t,
        // enum 'BracketStyle'
        QtPrivate::TypeAndForceComplete<QCPSelectionDecoratorBracket::BracketStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPSelectionDecoratorBracket, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN11QCPAxisRectE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QCPAxisRectE = QtMocHelpers::stringData(
    "QCPAxisRect",
    "background",
    "backgroundScaled",
    "backgroundScaledMode",
    "Qt::AspectRatioMode",
    "rangeDrag",
    "Qt::Orientations",
    "rangeZoom"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QCPAxisRectE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPixmap, 0x00015103, uint(-1), 0,
       2, QMetaType::Bool, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       7, 0x80000000 | 6, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisRect::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_ZN11QCPAxisRectE.offsetsAndSizes,
    qt_meta_data_ZN11QCPAxisRectE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QCPAxisRectE_t,
        // property 'background'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // property 'backgroundScaled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'backgroundScaledMode'
        QtPrivate::TypeAndForceComplete<Qt::AspectRatioMode, std::true_type>,
        // property 'rangeDrag'
        QtPrivate::TypeAndForceComplete<Qt::Orientations, std::true_type>,
        // property 'rangeZoom'
        QtPrivate::TypeAndForceComplete<Qt::Orientations, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisRect, std::true_type>
    >,
    nullptr
} };

void QCPAxisRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPAxisRect *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPixmap*>(_v) = _t->background(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->backgroundScaled(); break;
        case 2: *reinterpret_cast< Qt::AspectRatioMode*>(_v) = _t->backgroundScaledMode(); break;
        case 3: *reinterpret_cast< Qt::Orientations*>(_v) = _t->rangeDrag(); break;
        case 4: *reinterpret_cast< Qt::Orientations*>(_v) = _t->rangeZoom(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackground(*reinterpret_cast< QPixmap*>(_v)); break;
        case 1: _t->setBackgroundScaled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setBackgroundScaledMode(*reinterpret_cast< Qt::AspectRatioMode*>(_v)); break;
        case 3: _t->setRangeDrag(*reinterpret_cast< Qt::Orientations*>(_v)); break;
        case 4: _t->setRangeZoom(*reinterpret_cast< Qt::Orientations*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPAxisRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAxisRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QCPAxisRectE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPAxisRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN21QCPAbstractLegendItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN21QCPAbstractLegendItemE = QtMocHelpers::stringData(
    "QCPAbstractLegendItem",
    "selectionChanged",
    "",
    "selected",
    "selectableChanged",
    "selectable",
    "setSelectable",
    "setSelected",
    "parentLegend",
    "QCPLegend*",
    "font",
    "textColor",
    "selectedFont",
    "selectedTextColor"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN21QCPAbstractLegendItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       7,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    8 /* Public */,
       4,    1,   41,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   44,    2, 0x0a,   12 /* Public */,
       7,    1,   47,    2, 0x0a,   14 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags, notifyId, revision
       8, 0x80000000 | 9, 0x00015009, uint(-1), 0,
      10, QMetaType::QFont, 0x00015103, uint(-1), 0,
      11, QMetaType::QColor, 0x00015103, uint(-1), 0,
      12, QMetaType::QFont, 0x00015103, uint(-1), 0,
      13, QMetaType::QColor, 0x00015103, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(0), 0,
       3, QMetaType::Bool, 0x00015103, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAbstractLegendItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_ZN21QCPAbstractLegendItemE.offsetsAndSizes,
    qt_meta_data_ZN21QCPAbstractLegendItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN21QCPAbstractLegendItemE_t,
        // property 'parentLegend'
        QtPrivate::TypeAndForceComplete<QCPLegend*, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'textColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTextColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QCPAbstractLegendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPAbstractLegendItem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->setSelected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPAbstractLegendItem::*)(bool );
            if (_q_method_type _q_method = &QCPAbstractLegendItem::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPAbstractLegendItem::*)(bool );
            if (_q_method_type _q_method = &QCPAbstractLegendItem::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPLegend**>(_v) = _t->parentLegend(); break;
        case 1: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->selectedTextColor(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->selectable(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->selected(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 2: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 4: _t->setSelectedTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setSelectable(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPAbstractLegendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAbstractLegendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN21QCPAbstractLegendItemE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPAbstractLegendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCPAbstractLegendItem::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAbstractLegendItem::selectableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_tag_ZN22QCPPlottableLegendItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN22QCPPlottableLegendItemE = QtMocHelpers::stringData(
    "QCPPlottableLegendItem"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN22QCPPlottableLegendItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPlottableLegendItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractLegendItem::staticMetaObject>(),
    qt_meta_stringdata_ZN22QCPPlottableLegendItemE.offsetsAndSizes,
    qt_meta_data_ZN22QCPPlottableLegendItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN22QCPPlottableLegendItemE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPlottableLegendItem, std::true_type>
    >,
    nullptr
} };

void QCPPlottableLegendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPPlottableLegendItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *QCPPlottableLegendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPlottableLegendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN22QCPPlottableLegendItemE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractLegendItem::qt_metacast(_clname);
}

int QCPPlottableLegendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractLegendItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN9QCPLegendE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN9QCPLegendE = QtMocHelpers::stringData(
    "QCPLegend",
    "selectionChanged",
    "",
    "QCPLegend::SelectableParts",
    "parts",
    "selectableChanged",
    "setSelectableParts",
    "SelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "borderPen",
    "brush",
    "font",
    "textColor",
    "iconSize",
    "iconTextPadding",
    "iconBorderPen",
    "selectedBorderPen",
    "selectedIconBorderPen",
    "selectedBrush",
    "selectedFont",
    "selectedTextColor",
    "SelectablePart",
    "spNone",
    "spLegendBox",
    "spItems"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN9QCPLegendE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
      14,   50, // properties
       2,  120, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,   17 /* Public */,
       5,    1,   41,    2, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   44,    2, 0x0a,   21 /* Public */,
       9,    1,   47,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,   10,

 // properties: name, type, flags, notifyId, revision
      11, QMetaType::QPen, 0x00015103, uint(-1), 0,
      12, QMetaType::QBrush, 0x00015103, uint(-1), 0,
      13, QMetaType::QFont, 0x00015103, uint(-1), 0,
      14, QMetaType::QColor, 0x00015103, uint(-1), 0,
      15, QMetaType::QSize, 0x00015103, uint(-1), 0,
      16, QMetaType::Int, 0x00015103, uint(-1), 0,
      17, QMetaType::QPen, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 7, 0x0001510b, uint(0), 0,
      10, 0x80000000 | 7, 0x0001510b, uint(1), 0,
      18, QMetaType::QPen, 0x00015103, uint(-1), 0,
      19, QMetaType::QPen, 0x00015103, uint(-1), 0,
      20, QMetaType::QBrush, 0x00015103, uint(-1), 0,
      21, QMetaType::QFont, 0x00015103, uint(-1), 0,
      22, QMetaType::QColor, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
      23,   23, 0x0,    3,  130,
       7,   23, 0x1,    3,  136,

 // enum data: key, value
      24, uint(QCPLegend::spNone),
      25, uint(QCPLegend::spLegendBox),
      26, uint(QCPLegend::spItems),
      24, uint(QCPLegend::spNone),
      25, uint(QCPLegend::spLegendBox),
      26, uint(QCPLegend::spItems),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLegend::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutGrid::staticMetaObject>(),
    qt_meta_stringdata_ZN9QCPLegendE.offsetsAndSizes,
    qt_meta_data_ZN9QCPLegendE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN9QCPLegendE_t,
        // property 'borderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'textColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'iconSize'
        QtPrivate::TypeAndForceComplete<QSize, std::true_type>,
        // property 'iconTextPadding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'iconBorderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectableParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectedParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectedBorderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedIconBorderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTextColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // enum 'SelectablePart'
        QtPrivate::TypeAndForceComplete<QCPLegend::SelectablePart, std::true_type>,
        // enum 'SelectableParts'
        QtPrivate::TypeAndForceComplete<QCPLegend::SelectableParts, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLegend, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend::SelectableParts, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend::SelectableParts, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPLegend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPLegend *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPLegend::SelectableParts>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPLegend::SelectableParts>>(_a[1]))); break;
        case 2: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<SelectableParts>>(_a[1]))); break;
        case 3: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<SelectableParts>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPLegend::*)(QCPLegend::SelectableParts );
            if (_q_method_type _q_method = &QCPLegend::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPLegend::*)(QCPLegend::SelectableParts );
            if (_q_method_type _q_method = &QCPLegend::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->borderPen(); break;
        case 1: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 2: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 4: *reinterpret_cast< QSize*>(_v) = _t->iconSize(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->iconTextPadding(); break;
        case 6: *reinterpret_cast< QPen*>(_v) = _t->iconBorderPen(); break;
        case 7: *reinterpret_cast<int*>(_v) = QFlag(_t->selectableParts()); break;
        case 8: *reinterpret_cast<int*>(_v) = QFlag(_t->selectedParts()); break;
        case 9: *reinterpret_cast< QPen*>(_v) = _t->selectedBorderPen(); break;
        case 10: *reinterpret_cast< QPen*>(_v) = _t->selectedIconBorderPen(); break;
        case 11: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        case 12: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 13: *reinterpret_cast< QColor*>(_v) = _t->selectedTextColor(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 2: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 3: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setIconSize(*reinterpret_cast< QSize*>(_v)); break;
        case 5: _t->setIconTextPadding(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setIconBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 7: _t->setSelectableParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 8: _t->setSelectedParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 9: _t->setSelectedBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 10: _t->setSelectedIconBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 11: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 12: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 13: _t->setSelectedTextColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPLegend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLegend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN9QCPLegendE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutGrid::qt_metacast(_clname);
}

int QCPLegend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutGrid::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QCPLegend::selectionChanged(QCPLegend::SelectableParts _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPLegend::selectableChanged(QCPLegend::SelectableParts _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_tag_ZN14QCPTextElementE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QCPTextElementE = QtMocHelpers::stringData(
    "QCPTextElement",
    "selectionChanged",
    "",
    "selected",
    "selectableChanged",
    "selectable",
    "clicked",
    "QMouseEvent*",
    "event",
    "doubleClicked",
    "setSelectable",
    "setSelected",
    "text",
    "font",
    "textColor",
    "selectedFont",
    "selectedTextColor"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QCPTextElementE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       7,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    8 /* Public */,
       4,    1,   53,    2, 0x06,   10 /* Public */,
       6,    1,   56,    2, 0x06,   12 /* Public */,
       9,    1,   59,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   62,    2, 0x0a,   16 /* Public */,
      11,    1,   65,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags, notifyId, revision
      12, QMetaType::QString, 0x00015103, uint(-1), 0,
      13, QMetaType::QFont, 0x00015103, uint(-1), 0,
      14, QMetaType::QColor, 0x00015103, uint(-1), 0,
      15, QMetaType::QFont, 0x00015103, uint(-1), 0,
      16, QMetaType::QColor, 0x00015103, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(1), 0,
       3, QMetaType::Bool, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPTextElement::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_ZN14QCPTextElementE.offsetsAndSizes,
    qt_meta_data_ZN14QCPTextElementE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QCPTextElementE_t,
        // property 'text'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'textColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTextColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPTextElement, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QCPTextElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPTextElement *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->clicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->setSelected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPTextElement::*)(bool );
            if (_q_method_type _q_method = &QCPTextElement::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPTextElement::*)(bool );
            if (_q_method_type _q_method = &QCPTextElement::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPTextElement::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCPTextElement::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCPTextElement::*)(QMouseEvent * );
            if (_q_method_type _q_method = &QCPTextElement::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->selectedTextColor(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->selectable(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->selected(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 2: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 4: _t->setSelectedTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setSelectable(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPTextElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPTextElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QCPTextElementE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPTextElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCPTextElement::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPTextElement::selectableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPTextElement::clicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPTextElement::doubleClicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN28QCPColorScaleAxisRectPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN28QCPColorScaleAxisRectPrivateE = QtMocHelpers::stringData(
    "QCPColorScaleAxisRectPrivate",
    "axisSelectionChanged",
    "",
    "QCPAxis::SelectableParts",
    "selectedParts",
    "axisSelectableChanged",
    "selectableParts"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN28QCPColorScaleAxisRectPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x09,    1 /* Protected */,
       5,    1,   29,    2, 0x09,    3 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPColorScaleAxisRectPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAxisRect::staticMetaObject>(),
    qt_meta_stringdata_ZN28QCPColorScaleAxisRectPrivateE.offsetsAndSizes,
    qt_meta_data_ZN28QCPColorScaleAxisRectPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN28QCPColorScaleAxisRectPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorScaleAxisRectPrivate, std::true_type>,
        // method 'axisSelectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectableParts, std::false_type>,
        // method 'axisSelectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectableParts, std::false_type>
    >,
    nullptr
} };

void QCPColorScaleAxisRectPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPColorScaleAxisRectPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisSelectionChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 1: _t->axisSelectableChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *QCPColorScaleAxisRectPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPColorScaleAxisRectPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN28QCPColorScaleAxisRectPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QCPAxisRect::qt_metacast(_clname);
}

int QCPColorScaleAxisRectPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAxisRect::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13QCPColorScaleE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPColorScaleE = QtMocHelpers::stringData(
    "QCPColorScale",
    "dataRangeChanged",
    "",
    "QCPRange",
    "newRange",
    "dataScaleTypeChanged",
    "QCPAxis::ScaleType",
    "scaleType",
    "gradientChanged",
    "QCPColorGradient",
    "newGradient",
    "setDataRange",
    "dataRange",
    "setDataScaleType",
    "setGradient",
    "gradient",
    "type",
    "QCPAxis::AxisType",
    "dataScaleType",
    "label",
    "barWidth",
    "rangeDrag",
    "rangeZoom"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPColorScaleE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       8,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    9 /* Public */,
       5,    1,   53,    2, 0x06,   11 /* Public */,
       8,    1,   56,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   59,    2, 0x0a,   15 /* Public */,
      13,    1,   62,    2, 0x0a,   17 /* Public */,
      14,    1,   65,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   15,

 // properties: name, type, flags, notifyId, revision
      16, 0x80000000 | 17, 0x0001510b, uint(-1), 0,
      12, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      18, 0x80000000 | 6, 0x0001510b, uint(1), 0,
      15, 0x80000000 | 9, 0x0001510b, uint(2), 0,
      19, QMetaType::QString, 0x00015103, uint(-1), 0,
      20, QMetaType::Int, 0x00015103, uint(-1), 0,
      21, QMetaType::Bool, 0x00015103, uint(-1), 0,
      22, QMetaType::Bool, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_ZN13QCPColorScaleE[] = {
    QMetaObject::SuperData::link<QCPAxis::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QCPColorScale::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_ZN13QCPColorScaleE.offsetsAndSizes,
    qt_meta_data_ZN13QCPColorScaleE,
    qt_static_metacall,
    qt_meta_extradata_ZN13QCPColorScaleE,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPColorScaleE_t,
        // property 'type'
        QtPrivate::TypeAndForceComplete<QCPAxis::AxisType, std::true_type>,
        // property 'dataRange'
        QtPrivate::TypeAndForceComplete<QCPRange, std::true_type>,
        // property 'dataScaleType'
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::true_type>,
        // property 'gradient'
        QtPrivate::TypeAndForceComplete<QCPColorGradient, std::true_type>,
        // property 'label'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'barWidth'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'rangeDrag'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'rangeZoom'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorScale, std::true_type>,
        // method 'dataRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'dataScaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'gradientChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>,
        // method 'setDataRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setDataScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'setGradient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>
    >,
    nullptr
} };

void QCPColorScale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPColorScale *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dataRangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->dataScaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 2: _t->gradientChanged((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        case 3: _t->setDataRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 4: _t->setDataScaleType((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 5: _t->setGradient((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPColorScale::*)(const QCPRange & );
            if (_q_method_type _q_method = &QCPColorScale::dataRangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPColorScale::*)(QCPAxis::ScaleType );
            if (_q_method_type _q_method = &QCPColorScale::dataScaleTypeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPColorScale::*)(const QCPColorGradient & );
            if (_q_method_type _q_method = &QCPColorScale::gradientChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::AxisType >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::ScaleType >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPAxis::AxisType*>(_v) = _t->type(); break;
        case 1: *reinterpret_cast< QCPRange*>(_v) = _t->dataRange(); break;
        case 2: *reinterpret_cast< QCPAxis::ScaleType*>(_v) = _t->dataScaleType(); break;
        case 3: *reinterpret_cast< QCPColorGradient*>(_v) = _t->gradient(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->barWidth(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->rangeDrag(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->rangeZoom(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setType(*reinterpret_cast< QCPAxis::AxisType*>(_v)); break;
        case 1: _t->setDataRange(*reinterpret_cast< QCPRange*>(_v)); break;
        case 2: _t->setDataScaleType(*reinterpret_cast< QCPAxis::ScaleType*>(_v)); break;
        case 3: _t->setGradient(*reinterpret_cast< QCPColorGradient*>(_v)); break;
        case 4: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setBarWidth(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setRangeDrag(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->setRangeZoom(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPColorScale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPColorScale::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QCPColorScaleE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPColorScale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QCPColorScale::dataRangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPColorScale::dataScaleTypeChanged(QCPAxis::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPColorScale::gradientChanged(const QCPColorGradient & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_tag_ZN8QCPGraphE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN8QCPGraphE = QtMocHelpers::stringData(
    "QCPGraph",
    "lineStyle",
    "LineStyle",
    "scatterStyle",
    "QCPScatterStyle",
    "scatterSkip",
    "channelFillGraph",
    "QCPGraph*",
    "adaptiveSampling",
    "lsNone",
    "lsLine",
    "lsStepLeft",
    "lsStepRight",
    "lsStepCenter",
    "lsImpulse"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN8QCPGraphE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       1,   39, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, QMetaType::Int, 0x00015103, uint(-1), 0,
       6, 0x80000000 | 7, 0x0001510b, uint(-1), 0,
       8, QMetaType::Bool, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       2,    2, 0x0,    6,   44,

 // enum data: key, value
       9, uint(QCPGraph::lsNone),
      10, uint(QCPGraph::lsLine),
      11, uint(QCPGraph::lsStepLeft),
      12, uint(QCPGraph::lsStepRight),
      13, uint(QCPGraph::lsStepCenter),
      14, uint(QCPGraph::lsImpulse),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPGraphData>::staticMetaObject>(),
    qt_meta_stringdata_ZN8QCPGraphE.offsetsAndSizes,
    qt_meta_data_ZN8QCPGraphE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN8QCPGraphE_t,
        // property 'lineStyle'
        QtPrivate::TypeAndForceComplete<LineStyle, std::true_type>,
        // property 'scatterStyle'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>,
        // property 'scatterSkip'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'channelFillGraph'
        QtPrivate::TypeAndForceComplete<QCPGraph*, std::true_type>,
        // property 'adaptiveSampling'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // enum 'LineStyle'
        QtPrivate::TypeAndForceComplete<QCPGraph::LineStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPGraph, std::true_type>
    >,
    nullptr
} };

void QCPGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPGraph *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPGraph* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< LineStyle*>(_v) = _t->lineStyle(); break;
        case 1: *reinterpret_cast< QCPScatterStyle*>(_v) = _t->scatterStyle(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->scatterSkip(); break;
        case 3: *reinterpret_cast< QCPGraph**>(_v) = _t->channelFillGraph(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->adaptiveSampling(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLineStyle(*reinterpret_cast< LineStyle*>(_v)); break;
        case 1: _t->setScatterStyle(*reinterpret_cast< QCPScatterStyle*>(_v)); break;
        case 2: _t->setScatterSkip(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setChannelFillGraph(*reinterpret_cast< QCPGraph**>(_v)); break;
        case 4: _t->setAdaptiveSampling(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN8QCPGraphE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPGraphData>::qt_metacast(_clname);
}

int QCPGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPGraphData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN8QCPCurveE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN8QCPCurveE = QtMocHelpers::stringData(
    "QCPCurve",
    "scatterStyle",
    "QCPScatterStyle",
    "scatterSkip",
    "lineStyle",
    "LineStyle",
    "lsNone",
    "lsLine"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN8QCPCurveE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       1,   29, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, QMetaType::Int, 0x00015103, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    2,   34,

 // enum data: key, value
       6, uint(QCPCurve::lsNone),
       7, uint(QCPCurve::lsLine),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPCurve::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPCurveData>::staticMetaObject>(),
    qt_meta_stringdata_ZN8QCPCurveE.offsetsAndSizes,
    qt_meta_data_ZN8QCPCurveE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN8QCPCurveE_t,
        // property 'scatterStyle'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>,
        // property 'scatterSkip'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lineStyle'
        QtPrivate::TypeAndForceComplete<LineStyle, std::true_type>,
        // enum 'LineStyle'
        QtPrivate::TypeAndForceComplete<QCPCurve::LineStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPCurve, std::true_type>
    >,
    nullptr
} };

void QCPCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPCurve *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPScatterStyle*>(_v) = _t->scatterStyle(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->scatterSkip(); break;
        case 2: *reinterpret_cast< LineStyle*>(_v) = _t->lineStyle(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setScatterStyle(*reinterpret_cast< QCPScatterStyle*>(_v)); break;
        case 1: _t->setScatterSkip(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setLineStyle(*reinterpret_cast< LineStyle*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN8QCPCurveE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPCurveData>::qt_metacast(_clname);
}

int QCPCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPCurveData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN12QCPBarsGroupE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12QCPBarsGroupE = QtMocHelpers::stringData(
    "QCPBarsGroup",
    "spacingType",
    "SpacingType",
    "spacing",
    "stAbsolute",
    "stAxisRectRatio",
    "stPlotCoords"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12QCPBarsGroupE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       1,   24, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, QMetaType::Double, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       2,    2, 0x0,    3,   29,

 // enum data: key, value
       4, uint(QCPBarsGroup::stAbsolute),
       5, uint(QCPBarsGroup::stAxisRectRatio),
       6, uint(QCPBarsGroup::stPlotCoords),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPBarsGroup::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN12QCPBarsGroupE.offsetsAndSizes,
    qt_meta_data_ZN12QCPBarsGroupE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12QCPBarsGroupE_t,
        // property 'spacingType'
        QtPrivate::TypeAndForceComplete<SpacingType, std::true_type>,
        // property 'spacing'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // enum 'SpacingType'
        QtPrivate::TypeAndForceComplete<QCPBarsGroup::SpacingType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPBarsGroup, std::true_type>
    >,
    nullptr
} };

void QCPBarsGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPBarsGroup *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< SpacingType*>(_v) = _t->spacingType(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->spacing(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSpacingType(*reinterpret_cast< SpacingType*>(_v)); break;
        case 1: _t->setSpacing(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPBarsGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPBarsGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12QCPBarsGroupE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPBarsGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN7QCPBarsE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN7QCPBarsE = QtMocHelpers::stringData(
    "QCPBars",
    "width",
    "widthType",
    "WidthType",
    "barsGroup",
    "QCPBarsGroup*",
    "baseValue",
    "stackingGap",
    "barBelow",
    "QCPBars*",
    "barAbove",
    "wtAbsolute",
    "wtAxisRectRatio",
    "wtPlotCoords"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN7QCPBarsE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       1,   49, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::Double, 0x00015103, uint(-1), 0,
       2, 0x80000000 | 3, 0x0001510b, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,
       6, QMetaType::Double, 0x00015103, uint(-1), 0,
       7, QMetaType::Double, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x00015009, uint(-1), 0,
      10, 0x80000000 | 9, 0x00015009, uint(-1), 0,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    3,   54,

 // enum data: key, value
      11, uint(QCPBars::wtAbsolute),
      12, uint(QCPBars::wtAxisRectRatio),
      13, uint(QCPBars::wtPlotCoords),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPBars::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPBarsData>::staticMetaObject>(),
    qt_meta_stringdata_ZN7QCPBarsE.offsetsAndSizes,
    qt_meta_data_ZN7QCPBarsE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN7QCPBarsE_t,
        // property 'width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'widthType'
        QtPrivate::TypeAndForceComplete<WidthType, std::true_type>,
        // property 'barsGroup'
        QtPrivate::TypeAndForceComplete<QCPBarsGroup*, std::true_type>,
        // property 'baseValue'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'stackingGap'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'barBelow'
        QtPrivate::TypeAndForceComplete<QCPBars*, std::true_type>,
        // property 'barAbove'
        QtPrivate::TypeAndForceComplete<QCPBars*, std::true_type>,
        // enum 'WidthType'
        QtPrivate::TypeAndForceComplete<QCPBars::WidthType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPBars, std::true_type>
    >,
    nullptr
} };

void QCPBars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPBars *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPBars* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPBarsGroup* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< WidthType*>(_v) = _t->widthType(); break;
        case 2: *reinterpret_cast< QCPBarsGroup**>(_v) = _t->barsGroup(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->baseValue(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->stackingGap(); break;
        case 5: *reinterpret_cast< QCPBars**>(_v) = _t->barBelow(); break;
        case 6: *reinterpret_cast< QCPBars**>(_v) = _t->barAbove(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setWidthType(*reinterpret_cast< WidthType*>(_v)); break;
        case 2: _t->setBarsGroup(*reinterpret_cast< QCPBarsGroup**>(_v)); break;
        case 3: _t->setBaseValue(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setStackingGap(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPBars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPBars::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN7QCPBarsE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPBarsData>::qt_metacast(_clname);
}

int QCPBars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPBarsData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN17QCPStatisticalBoxE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17QCPStatisticalBoxE = QtMocHelpers::stringData(
    "QCPStatisticalBox",
    "width",
    "whiskerWidth",
    "whiskerPen",
    "whiskerBarPen",
    "whiskerAntialiased",
    "medianPen",
    "outlierStyle",
    "QCPScatterStyle"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN17QCPStatisticalBoxE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::Double, 0x00015103, uint(-1), 0,
       2, QMetaType::Double, 0x00015103, uint(-1), 0,
       3, QMetaType::QPen, 0x00015103, uint(-1), 0,
       4, QMetaType::QPen, 0x00015103, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(-1), 0,
       6, QMetaType::QPen, 0x00015103, uint(-1), 0,
       7, 0x80000000 | 8, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPStatisticalBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPStatisticalBoxData>::staticMetaObject>(),
    qt_meta_stringdata_ZN17QCPStatisticalBoxE.offsetsAndSizes,
    qt_meta_data_ZN17QCPStatisticalBoxE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN17QCPStatisticalBoxE_t,
        // property 'width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'whiskerWidth'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'whiskerPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'whiskerBarPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'whiskerAntialiased'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'medianPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'outlierStyle'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPStatisticalBox, std::true_type>
    >,
    nullptr
} };

void QCPStatisticalBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPStatisticalBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->whiskerWidth(); break;
        case 2: *reinterpret_cast< QPen*>(_v) = _t->whiskerPen(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->whiskerBarPen(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->whiskerAntialiased(); break;
        case 5: *reinterpret_cast< QPen*>(_v) = _t->medianPen(); break;
        case 6: *reinterpret_cast< QCPScatterStyle*>(_v) = _t->outlierStyle(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setWhiskerWidth(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setWhiskerPen(*reinterpret_cast< QPen*>(_v)); break;
        case 3: _t->setWhiskerBarPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setWhiskerAntialiased(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setMedianPen(*reinterpret_cast< QPen*>(_v)); break;
        case 6: _t->setOutlierStyle(*reinterpret_cast< QCPScatterStyle*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPStatisticalBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPStatisticalBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN17QCPStatisticalBoxE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPStatisticalBoxData>::qt_metacast(_clname);
}

int QCPStatisticalBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPStatisticalBoxData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN11QCPColorMapE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QCPColorMapE = QtMocHelpers::stringData(
    "QCPColorMap",
    "dataRangeChanged",
    "",
    "QCPRange",
    "newRange",
    "dataScaleTypeChanged",
    "QCPAxis::ScaleType",
    "scaleType",
    "gradientChanged",
    "QCPColorGradient",
    "newGradient",
    "setDataRange",
    "dataRange",
    "setDataScaleType",
    "setGradient",
    "gradient",
    "updateLegendIcon",
    "Qt::TransformationMode",
    "transformMode",
    "thumbSize",
    "dataScaleType",
    "interpolate",
    "tightBoundary",
    "colorScale",
    "QCPColorScale*"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QCPColorMapE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       6,   95, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    7 /* Public */,
       5,    1,   71,    2, 0x06,    9 /* Public */,
       8,    1,   74,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   77,    2, 0x0a,   13 /* Public */,
      13,    1,   80,    2, 0x0a,   15 /* Public */,
      14,    1,   83,    2, 0x0a,   17 /* Public */,
      16,    2,   86,    2, 0x0a,   19 /* Public */,
      16,    1,   91,    2, 0x2a,   22 /* Public | MethodCloned */,
      16,    0,   94,    2, 0x2a,   24 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QSize,   18,   19,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      12, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      20, 0x80000000 | 6, 0x0001510b, uint(1), 0,
      15, 0x80000000 | 9, 0x0001510b, uint(2), 0,
      21, QMetaType::Bool, 0x00015103, uint(-1), 0,
      22, QMetaType::Bool, 0x00015103, uint(-1), 0,
      23, 0x80000000 | 24, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_ZN11QCPColorMapE[] = {
    QMetaObject::SuperData::link<QCPAxis::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QCPColorMap::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable::staticMetaObject>(),
    qt_meta_stringdata_ZN11QCPColorMapE.offsetsAndSizes,
    qt_meta_data_ZN11QCPColorMapE,
    qt_static_metacall,
    qt_meta_extradata_ZN11QCPColorMapE,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QCPColorMapE_t,
        // property 'dataRange'
        QtPrivate::TypeAndForceComplete<QCPRange, std::true_type>,
        // property 'dataScaleType'
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::true_type>,
        // property 'gradient'
        QtPrivate::TypeAndForceComplete<QCPColorGradient, std::true_type>,
        // property 'interpolate'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'tightBoundary'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'colorScale'
        QtPrivate::TypeAndForceComplete<QCPColorScale*, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorMap, std::true_type>,
        // method 'dataRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'dataScaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'gradientChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>,
        // method 'setDataRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setDataScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'setGradient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>,
        // method 'updateLegendIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::TransformationMode, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSize &, std::false_type>,
        // method 'updateLegendIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::TransformationMode, std::false_type>,
        // method 'updateLegendIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCPColorMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPColorMap *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dataRangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->dataScaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 2: _t->gradientChanged((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        case 3: _t->setDataRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 4: _t->setDataScaleType((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 5: _t->setGradient((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        case 6: _t->updateLegendIcon((*reinterpret_cast< std::add_pointer_t<Qt::TransformationMode>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QSize>>(_a[2]))); break;
        case 7: _t->updateLegendIcon((*reinterpret_cast< std::add_pointer_t<Qt::TransformationMode>>(_a[1]))); break;
        case 8: _t->updateLegendIcon(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPColorMap::*)(const QCPRange & );
            if (_q_method_type _q_method = &QCPColorMap::dataRangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPColorMap::*)(QCPAxis::ScaleType );
            if (_q_method_type _q_method = &QCPColorMap::dataScaleTypeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPColorMap::*)(const QCPColorGradient & );
            if (_q_method_type _q_method = &QCPColorMap::gradientChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::ScaleType >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPColorScale* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPRange*>(_v) = _t->dataRange(); break;
        case 1: *reinterpret_cast< QCPAxis::ScaleType*>(_v) = _t->dataScaleType(); break;
        case 2: *reinterpret_cast< QCPColorGradient*>(_v) = _t->gradient(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->interpolate(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->tightBoundary(); break;
        case 5: *reinterpret_cast< QCPColorScale**>(_v) = _t->colorScale(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDataRange(*reinterpret_cast< QCPRange*>(_v)); break;
        case 1: _t->setDataScaleType(*reinterpret_cast< QCPAxis::ScaleType*>(_v)); break;
        case 2: _t->setGradient(*reinterpret_cast< QCPColorGradient*>(_v)); break;
        case 3: _t->setInterpolate(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setTightBoundary(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setColorScale(*reinterpret_cast< QCPColorScale**>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPColorMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPColorMap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QCPColorMapE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable::qt_metacast(_clname);
}

int QCPColorMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QCPColorMap::dataRangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPColorMap::dataScaleTypeChanged(QCPAxis::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPColorMap::gradientChanged(const QCPColorGradient & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_tag_ZN12QCPFinancialE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12QCPFinancialE = QtMocHelpers::stringData(
    "QCPFinancial",
    "chartStyle",
    "ChartStyle",
    "width",
    "widthType",
    "WidthType",
    "twoColored",
    "brushPositive",
    "brushNegative",
    "penPositive",
    "penNegative",
    "wtAbsolute",
    "wtAxisRectRatio",
    "wtPlotCoords",
    "csOhlc",
    "csCandlestick"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12QCPFinancialE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       2,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, QMetaType::Double, 0x00015103, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,
       6, QMetaType::Bool, 0x00015103, uint(-1), 0,
       7, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       8, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       9, QMetaType::QPen, 0x00015103, uint(-1), 0,
      10, QMetaType::QPen, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    3,   64,
       2,    2, 0x0,    2,   70,

 // enum data: key, value
      11, uint(QCPFinancial::wtAbsolute),
      12, uint(QCPFinancial::wtAxisRectRatio),
      13, uint(QCPFinancial::wtPlotCoords),
      14, uint(QCPFinancial::csOhlc),
      15, uint(QCPFinancial::csCandlestick),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPFinancial::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPFinancialData>::staticMetaObject>(),
    qt_meta_stringdata_ZN12QCPFinancialE.offsetsAndSizes,
    qt_meta_data_ZN12QCPFinancialE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12QCPFinancialE_t,
        // property 'chartStyle'
        QtPrivate::TypeAndForceComplete<ChartStyle, std::true_type>,
        // property 'width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'widthType'
        QtPrivate::TypeAndForceComplete<WidthType, std::true_type>,
        // property 'twoColored'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'brushPositive'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'brushNegative'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'penPositive'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'penNegative'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // enum 'WidthType'
        QtPrivate::TypeAndForceComplete<QCPFinancial::WidthType, std::true_type>,
        // enum 'ChartStyle'
        QtPrivate::TypeAndForceComplete<QCPFinancial::ChartStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPFinancial, std::true_type>
    >,
    nullptr
} };

void QCPFinancial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPFinancial *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< ChartStyle*>(_v) = _t->chartStyle(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->width(); break;
        case 2: *reinterpret_cast< WidthType*>(_v) = _t->widthType(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->twoColored(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brushPositive(); break;
        case 5: *reinterpret_cast< QBrush*>(_v) = _t->brushNegative(); break;
        case 6: *reinterpret_cast< QPen*>(_v) = _t->penPositive(); break;
        case 7: *reinterpret_cast< QPen*>(_v) = _t->penNegative(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setChartStyle(*reinterpret_cast< ChartStyle*>(_v)); break;
        case 1: _t->setWidth(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setWidthType(*reinterpret_cast< WidthType*>(_v)); break;
        case 3: _t->setTwoColored(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setBrushPositive(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setBrushNegative(*reinterpret_cast< QBrush*>(_v)); break;
        case 6: _t->setPenPositive(*reinterpret_cast< QPen*>(_v)); break;
        case 7: _t->setPenNegative(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPFinancial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPFinancial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12QCPFinancialE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPFinancialData>::qt_metacast(_clname);
}

int QCPFinancial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPFinancialData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN12QCPErrorBarsE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12QCPErrorBarsE = QtMocHelpers::stringData(
    "QCPErrorBars",
    "data",
    "QSharedPointer<QCPErrorBarsDataContainer>",
    "dataPlottable",
    "QCPAbstractPlottable*",
    "errorType",
    "ErrorType",
    "whiskerWidth",
    "symbolGap",
    "etKeyError",
    "etValueError"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12QCPErrorBarsE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       1,   39, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       7, QMetaType::Double, 0x00015103, uint(-1), 0,
       8, QMetaType::Double, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       6,    6, 0x0,    2,   44,

 // enum data: key, value
       9, uint(QCPErrorBars::etKeyError),
      10, uint(QCPErrorBars::etValueError),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPErrorBars::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable::staticMetaObject>(),
    qt_meta_stringdata_ZN12QCPErrorBarsE.offsetsAndSizes,
    qt_meta_data_ZN12QCPErrorBarsE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12QCPErrorBarsE_t,
        // property 'data'
        QtPrivate::TypeAndForceComplete<QSharedPointer<QCPErrorBarsDataContainer>, std::true_type>,
        // property 'dataPlottable'
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable*, std::true_type>,
        // property 'errorType'
        QtPrivate::TypeAndForceComplete<ErrorType, std::true_type>,
        // property 'whiskerWidth'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'symbolGap'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // enum 'ErrorType'
        QtPrivate::TypeAndForceComplete<QCPErrorBars::ErrorType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPErrorBars, std::true_type>
    >,
    nullptr
} };

void QCPErrorBars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPErrorBars *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QSharedPointer<QCPErrorBarsDataContainer>*>(_v) = _t->data(); break;
        case 1: *reinterpret_cast< QCPAbstractPlottable**>(_v) = _t->dataPlottable(); break;
        case 2: *reinterpret_cast< ErrorType*>(_v) = _t->errorType(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->whiskerWidth(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->symbolGap(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setData(*reinterpret_cast< QSharedPointer<QCPErrorBarsDataContainer>*>(_v)); break;
        case 1: _t->setDataPlottable(*reinterpret_cast< QCPAbstractPlottable**>(_v)); break;
        case 2: _t->setErrorType(*reinterpret_cast< ErrorType*>(_v)); break;
        case 3: _t->setWhiskerWidth(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setSymbolGap(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPErrorBars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPErrorBars::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12QCPErrorBarsE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QCPPlottableInterface1D"))
        return static_cast< QCPPlottableInterface1D*>(this);
    return QCPAbstractPlottable::qt_metacast(_clname);
}

int QCPErrorBars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN19QCPItemStraightLineE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN19QCPItemStraightLineE = QtMocHelpers::stringData(
    "QCPItemStraightLine",
    "pen",
    "selectedPen"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN19QCPItemStraightLineE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemStraightLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN19QCPItemStraightLineE.offsetsAndSizes,
    qt_meta_data_ZN19QCPItemStraightLineE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN19QCPItemStraightLineE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemStraightLine, std::true_type>
    >,
    nullptr
} };

void QCPItemStraightLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemStraightLine *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemStraightLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemStraightLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN19QCPItemStraightLineE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemStraightLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN11QCPItemLineE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QCPItemLineE = QtMocHelpers::stringData(
    "QCPItemLine",
    "pen",
    "selectedPen",
    "head",
    "QCPLineEnding",
    "tail"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QCPItemLineE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN11QCPItemLineE.offsetsAndSizes,
    qt_meta_data_ZN11QCPItemLineE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QCPItemLineE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'head'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'tail'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemLine, std::true_type>
    >,
    nullptr
} };

void QCPItemLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemLine *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QCPLineEnding*>(_v) = _t->head(); break;
        case 3: *reinterpret_cast< QCPLineEnding*>(_v) = _t->tail(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setHead(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        case 3: _t->setTail(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QCPItemLineE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN12QCPItemCurveE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12QCPItemCurveE = QtMocHelpers::stringData(
    "QCPItemCurve",
    "pen",
    "selectedPen",
    "head",
    "QCPLineEnding",
    "tail"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12QCPItemCurveE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemCurve::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN12QCPItemCurveE.offsetsAndSizes,
    qt_meta_data_ZN12QCPItemCurveE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12QCPItemCurveE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'head'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'tail'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemCurve, std::true_type>
    >,
    nullptr
} };

void QCPItemCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemCurve *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QCPLineEnding*>(_v) = _t->head(); break;
        case 3: *reinterpret_cast< QCPLineEnding*>(_v) = _t->tail(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setHead(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        case 3: _t->setTail(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12QCPItemCurveE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN11QCPItemRectE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QCPItemRectE = QtMocHelpers::stringData(
    "QCPItemRect",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QCPItemRectE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       4, QMetaType::QBrush, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemRect::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN11QCPItemRectE.offsetsAndSizes,
    qt_meta_data_ZN11QCPItemRectE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QCPItemRectE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemRect, std::true_type>
    >,
    nullptr
} };

void QCPItemRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemRect *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QCPItemRectE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN11QCPItemTextE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QCPItemTextE = QtMocHelpers::stringData(
    "QCPItemText",
    "color",
    "selectedColor",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush",
    "font",
    "selectedFont",
    "text",
    "positionAlignment",
    "Qt::Alignment",
    "textAlignment",
    "rotation",
    "padding",
    "QMargins"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QCPItemTextE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      13,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QColor, 0x00015103, uint(-1), 0,
       2, QMetaType::QColor, 0x00015103, uint(-1), 0,
       3, QMetaType::QPen, 0x00015103, uint(-1), 0,
       4, QMetaType::QPen, 0x00015103, uint(-1), 0,
       5, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       6, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       7, QMetaType::QFont, 0x00015103, uint(-1), 0,
       8, QMetaType::QFont, 0x00015103, uint(-1), 0,
       9, QMetaType::QString, 0x00015103, uint(-1), 0,
      10, 0x80000000 | 11, 0x0001510b, uint(-1), 0,
      12, 0x80000000 | 11, 0x0001510b, uint(-1), 0,
      13, QMetaType::Double, 0x00015103, uint(-1), 0,
      14, 0x80000000 | 15, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemText::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN11QCPItemTextE.offsetsAndSizes,
    qt_meta_data_ZN11QCPItemTextE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QCPItemTextE_t,
        // property 'color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'text'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'positionAlignment'
        QtPrivate::TypeAndForceComplete<Qt::Alignment, std::true_type>,
        // property 'textAlignment'
        QtPrivate::TypeAndForceComplete<Qt::Alignment, std::true_type>,
        // property 'rotation'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'padding'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemText, std::true_type>
    >,
    nullptr
} };

void QCPItemText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemText *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->selectedColor(); break;
        case 2: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 5: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        case 6: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 7: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 9: *reinterpret_cast< Qt::Alignment*>(_v) = _t->positionAlignment(); break;
        case 10: *reinterpret_cast< Qt::Alignment*>(_v) = _t->textAlignment(); break;
        case 11: *reinterpret_cast< double*>(_v) = _t->rotation(); break;
        case 12: *reinterpret_cast< QMargins*>(_v) = _t->padding(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setSelectedColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 3: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 6: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 7: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 8: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setPositionAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 10: _t->setTextAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 11: _t->setRotation(*reinterpret_cast< double*>(_v)); break;
        case 12: _t->setPadding(*reinterpret_cast< QMargins*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemText::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QCPItemTextE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN14QCPItemEllipseE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QCPItemEllipseE = QtMocHelpers::stringData(
    "QCPItemEllipse",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QCPItemEllipseE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       4, QMetaType::QBrush, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemEllipse::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN14QCPItemEllipseE.offsetsAndSizes,
    qt_meta_data_ZN14QCPItemEllipseE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QCPItemEllipseE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemEllipse, std::true_type>
    >,
    nullptr
} };

void QCPItemEllipse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemEllipse *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemEllipse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemEllipse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QCPItemEllipseE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemEllipse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13QCPItemPixmapE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPItemPixmapE = QtMocHelpers::stringData(
    "QCPItemPixmap",
    "pixmap",
    "scaled",
    "aspectRatioMode",
    "Qt::AspectRatioMode",
    "transformationMode",
    "Qt::TransformationMode",
    "pen",
    "selectedPen"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPItemPixmapE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPixmap, 0x00015103, uint(-1), 0,
       2, QMetaType::Bool, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x00015009, uint(-1), 0,
       5, 0x80000000 | 6, 0x00015009, uint(-1), 0,
       7, QMetaType::QPen, 0x00015103, uint(-1), 0,
       8, QMetaType::QPen, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemPixmap::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN13QCPItemPixmapE.offsetsAndSizes,
    qt_meta_data_ZN13QCPItemPixmapE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPItemPixmapE_t,
        // property 'pixmap'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // property 'scaled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'aspectRatioMode'
        QtPrivate::TypeAndForceComplete<Qt::AspectRatioMode, std::true_type>,
        // property 'transformationMode'
        QtPrivate::TypeAndForceComplete<Qt::TransformationMode, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemPixmap, std::true_type>
    >,
    nullptr
} };

void QCPItemPixmap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemPixmap *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPixmap*>(_v) = _t->pixmap(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->scaled(); break;
        case 2: *reinterpret_cast< Qt::AspectRatioMode*>(_v) = _t->aspectRatioMode(); break;
        case 3: *reinterpret_cast< Qt::TransformationMode*>(_v) = _t->transformationMode(); break;
        case 4: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 5: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPixmap(*reinterpret_cast< QPixmap*>(_v)); break;
        case 1: _t->setScaled(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 5: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemPixmap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemPixmap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QCPItemPixmapE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemPixmap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13QCPItemTracerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPItemTracerE = QtMocHelpers::stringData(
    "QCPItemTracer",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush",
    "size",
    "style",
    "TracerStyle",
    "graph",
    "QCPGraph*",
    "graphKey",
    "interpolating",
    "tsNone",
    "tsPlus",
    "tsCrosshair",
    "tsCircle",
    "tsSquare"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPItemTracerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       9,   14, // properties
       1,   59, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       4, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       5, QMetaType::Double, 0x00015103, uint(-1), 0,
       6, 0x80000000 | 7, 0x0001510b, uint(-1), 0,
       8, 0x80000000 | 9, 0x0001510b, uint(-1), 0,
      10, QMetaType::Double, 0x00015103, uint(-1), 0,
      11, QMetaType::Bool, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       7,    7, 0x0,    5,   64,

 // enum data: key, value
      12, uint(QCPItemTracer::tsNone),
      13, uint(QCPItemTracer::tsPlus),
      14, uint(QCPItemTracer::tsCrosshair),
      15, uint(QCPItemTracer::tsCircle),
      16, uint(QCPItemTracer::tsSquare),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemTracer::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN13QCPItemTracerE.offsetsAndSizes,
    qt_meta_data_ZN13QCPItemTracerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPItemTracerE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'size'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'style'
        QtPrivate::TypeAndForceComplete<TracerStyle, std::true_type>,
        // property 'graph'
        QtPrivate::TypeAndForceComplete<QCPGraph*, std::true_type>,
        // property 'graphKey'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'interpolating'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // enum 'TracerStyle'
        QtPrivate::TypeAndForceComplete<QCPItemTracer::TracerStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemTracer, std::true_type>
    >,
    nullptr
} };

void QCPItemTracer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemTracer *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPGraph* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->size(); break;
        case 5: *reinterpret_cast< TracerStyle*>(_v) = _t->style(); break;
        case 6: *reinterpret_cast< QCPGraph**>(_v) = _t->graph(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->graphKey(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->interpolating(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 4: _t->setSize(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setStyle(*reinterpret_cast< TracerStyle*>(_v)); break;
        case 6: _t->setGraph(*reinterpret_cast< QCPGraph**>(_v)); break;
        case 7: _t->setGraphKey(*reinterpret_cast< double*>(_v)); break;
        case 8: _t->setInterpolating(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemTracer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemTracer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QCPItemTracerE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemTracer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN14QCPItemBracketE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QCPItemBracketE = QtMocHelpers::stringData(
    "QCPItemBracket",
    "pen",
    "selectedPen",
    "length",
    "style",
    "BracketStyle",
    "bsSquare",
    "bsRound",
    "bsCurly",
    "bsCalligraphic"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QCPItemBracketE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       1,   34, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags, notifyId, revision
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::Double, 0x00015103, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    4,   39,

 // enum data: key, value
       6, uint(QCPItemBracket::bsSquare),
       7, uint(QCPItemBracket::bsRound),
       8, uint(QCPItemBracket::bsCurly),
       9, uint(QCPItemBracket::bsCalligraphic),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemBracket::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_ZN14QCPItemBracketE.offsetsAndSizes,
    qt_meta_data_ZN14QCPItemBracketE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QCPItemBracketE_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'length'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'style'
        QtPrivate::TypeAndForceComplete<BracketStyle, std::true_type>,
        // enum 'BracketStyle'
        QtPrivate::TypeAndForceComplete<QCPItemBracket::BracketStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemBracket, std::true_type>
    >,
    nullptr
} };

void QCPItemBracket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPItemBracket *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->length(); break;
        case 3: *reinterpret_cast< BracketStyle*>(_v) = _t->style(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setLength(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setStyle(*reinterpret_cast< BracketStyle*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCPItemBracket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemBracket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QCPItemBracketE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemBracket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN18QCPPolarAxisRadialE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18QCPPolarAxisRadialE = QtMocHelpers::stringData(
    "QCPPolarAxisRadial",
    "rangeChanged",
    "",
    "QCPRange",
    "newRange",
    "oldRange",
    "scaleTypeChanged",
    "QCPPolarAxisRadial::ScaleType",
    "scaleType",
    "selectionChanged",
    "QCPPolarAxisRadial::SelectableParts",
    "parts",
    "selectableChanged",
    "setScaleType",
    "type",
    "setRange",
    "range",
    "setSelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "AngleReference",
    "arAbsolute",
    "arAngularAxis",
    "ScaleType",
    "stLinear",
    "stLogarithmic",
    "SelectablePart",
    "spNone",
    "spAxis",
    "spTickLabels",
    "spAxisLabel",
    "SelectableParts",
    "LabelMode",
    "lmUpright",
    "lmRotated"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18QCPPolarAxisRadialE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       5,   97, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    6 /* Public */,
       1,    2,   71,    2, 0x06,    8 /* Public */,
       6,    1,   76,    2, 0x06,   11 /* Public */,
       9,    1,   79,    2, 0x06,   13 /* Public */,
      12,    1,   82,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    1,   85,    2, 0x0a,   17 /* Public */,
      15,    1,   88,    2, 0x0a,   19 /* Public */,
      17,    1,   91,    2, 0x0a,   21 /* Public */,
      19,    1,   94,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,   14,
    QMetaType::Void, 0x80000000 | 3,   16,
    QMetaType::Void, 0x80000000 | 10,   18,
    QMetaType::Void, 0x80000000 | 10,   20,

 // enums: name, alias, flags, count, data
      21,   21, 0x0,    2,  122,
      24,   24, 0x0,    2,  126,
      27,   27, 0x0,    4,  130,
      32,   27, 0x1,    4,  138,
      33,   33, 0x0,    2,  146,

 // enum data: key, value
      22, uint(QCPPolarAxisRadial::arAbsolute),
      23, uint(QCPPolarAxisRadial::arAngularAxis),
      25, uint(QCPPolarAxisRadial::stLinear),
      26, uint(QCPPolarAxisRadial::stLogarithmic),
      28, uint(QCPPolarAxisRadial::spNone),
      29, uint(QCPPolarAxisRadial::spAxis),
      30, uint(QCPPolarAxisRadial::spTickLabels),
      31, uint(QCPPolarAxisRadial::spAxisLabel),
      28, uint(QCPPolarAxisRadial::spNone),
      29, uint(QCPPolarAxisRadial::spAxis),
      30, uint(QCPPolarAxisRadial::spTickLabels),
      31, uint(QCPPolarAxisRadial::spAxisLabel),
      34, uint(QCPPolarAxisRadial::lmUpright),
      35, uint(QCPPolarAxisRadial::lmRotated),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarAxisRadial::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN18QCPPolarAxisRadialE.offsetsAndSizes,
    qt_meta_data_ZN18QCPPolarAxisRadialE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18QCPPolarAxisRadialE_t,
        // enum 'AngleReference'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::AngleReference, std::true_type>,
        // enum 'ScaleType'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::ScaleType, std::true_type>,
        // enum 'SelectablePart'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::SelectablePart, std::true_type>,
        // enum 'SelectableParts'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::SelectableParts, std::true_type>,
        // enum 'LabelMode'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::LabelMode, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial, std::true_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'scaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::ScaleType, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>,
        // method 'setScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::ScaleType, std::false_type>,
        // method 'setRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPPolarAxisRadial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPPolarAxisRadial *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[2]))); break;
        case 2: _t->scaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::ScaleType>>(_a[1]))); break;
        case 3: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        case 4: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        case 5: _t->setScaleType((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::ScaleType>>(_a[1]))); break;
        case 6: _t->setRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 7: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        case 8: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPPolarAxisRadial::ScaleType >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPPolarAxisRadial::ScaleType >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPPolarAxisRadial::*)(const QCPRange & );
            if (_q_method_type _q_method = &QCPPolarAxisRadial::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisRadial::*)(const QCPRange & , const QCPRange & );
            if (_q_method_type _q_method = &QCPPolarAxisRadial::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisRadial::*)(QCPPolarAxisRadial::ScaleType );
            if (_q_method_type _q_method = &QCPPolarAxisRadial::scaleTypeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisRadial::*)(const QCPPolarAxisRadial::SelectableParts & );
            if (_q_method_type _q_method = &QCPPolarAxisRadial::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisRadial::*)(const QCPPolarAxisRadial::SelectableParts & );
            if (_q_method_type _q_method = &QCPPolarAxisRadial::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *QCPPolarAxisRadial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarAxisRadial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18QCPPolarAxisRadialE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPPolarAxisRadial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QCPPolarAxisRadial::rangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPPolarAxisRadial::rangeChanged(const QCPRange & _t1, const QCPRange & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPPolarAxisRadial::scaleTypeChanged(QCPPolarAxisRadial::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPPolarAxisRadial::selectionChanged(const QCPPolarAxisRadial::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCPPolarAxisRadial::selectableChanged(const QCPPolarAxisRadial::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
namespace {
struct qt_meta_tag_ZN19QCPPolarAxisAngularE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN19QCPPolarAxisAngularE = QtMocHelpers::stringData(
    "QCPPolarAxisAngular",
    "rangeChanged",
    "",
    "QCPRange",
    "newRange",
    "oldRange",
    "selectionChanged",
    "QCPPolarAxisAngular::SelectableParts",
    "parts",
    "selectableChanged",
    "setRange",
    "range",
    "setSelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "SelectablePart",
    "spNone",
    "spAxis",
    "spTickLabels",
    "spAxisLabel",
    "SelectableParts",
    "LabelMode",
    "lmUpright",
    "lmRotated"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN19QCPPolarAxisAngularE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       3,   79, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    4 /* Public */,
       1,    2,   59,    2, 0x06,    6 /* Public */,
       6,    1,   64,    2, 0x06,    9 /* Public */,
       9,    1,   67,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   70,    2, 0x0a,   13 /* Public */,
      12,    1,   73,    2, 0x0a,   15 /* Public */,
      14,    1,   76,    2, 0x0a,   17 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 7,   13,
    QMetaType::Void, 0x80000000 | 7,   15,

 // enums: name, alias, flags, count, data
      16,   16, 0x0,    4,   94,
      21,   16, 0x1,    4,  102,
      22,   22, 0x0,    2,  110,

 // enum data: key, value
      17, uint(QCPPolarAxisAngular::spNone),
      18, uint(QCPPolarAxisAngular::spAxis),
      19, uint(QCPPolarAxisAngular::spTickLabels),
      20, uint(QCPPolarAxisAngular::spAxisLabel),
      17, uint(QCPPolarAxisAngular::spNone),
      18, uint(QCPPolarAxisAngular::spAxis),
      19, uint(QCPPolarAxisAngular::spTickLabels),
      20, uint(QCPPolarAxisAngular::spAxisLabel),
      23, uint(QCPPolarAxisAngular::lmUpright),
      24, uint(QCPPolarAxisAngular::lmRotated),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarAxisAngular::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_ZN19QCPPolarAxisAngularE.offsetsAndSizes,
    qt_meta_data_ZN19QCPPolarAxisAngularE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN19QCPPolarAxisAngularE_t,
        // enum 'SelectablePart'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisAngular::SelectablePart, std::true_type>,
        // enum 'SelectableParts'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisAngular::SelectableParts, std::true_type>,
        // enum 'LabelMode'
        QtPrivate::TypeAndForceComplete<QCPPolarAxisAngular::LabelMode, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarAxisAngular, std::true_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>,
        // method 'setRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPPolarAxisAngular::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPPolarAxisAngular *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[2]))); break;
        case 2: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        case 3: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        case 4: _t->setRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 5: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        case 6: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPPolarAxisAngular::*)(const QCPRange & );
            if (_q_method_type _q_method = &QCPPolarAxisAngular::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisAngular::*)(const QCPRange & , const QCPRange & );
            if (_q_method_type _q_method = &QCPPolarAxisAngular::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisAngular::*)(const QCPPolarAxisAngular::SelectableParts & );
            if (_q_method_type _q_method = &QCPPolarAxisAngular::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarAxisAngular::*)(const QCPPolarAxisAngular::SelectableParts & );
            if (_q_method_type _q_method = &QCPPolarAxisAngular::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *QCPPolarAxisAngular::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarAxisAngular::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN19QCPPolarAxisAngularE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPPolarAxisAngular::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCPPolarAxisAngular::rangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPPolarAxisAngular::rangeChanged(const QCPRange & _t1, const QCPRange & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPPolarAxisAngular::selectionChanged(const QCPPolarAxisAngular::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPPolarAxisAngular::selectableChanged(const QCPPolarAxisAngular::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN12QCPPolarGridE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12QCPPolarGridE = QtMocHelpers::stringData(
    "QCPPolarGrid",
    "GridType",
    "gtAngular",
    "gtRadial",
    "gtAll",
    "gtNone",
    "GridTypes"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12QCPPolarGridE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   24,
       6,    1, 0x1,    4,   32,

 // enum data: key, value
       2, uint(QCPPolarGrid::gtAngular),
       3, uint(QCPPolarGrid::gtRadial),
       4, uint(QCPPolarGrid::gtAll),
       5, uint(QCPPolarGrid::gtNone),
       2, uint(QCPPolarGrid::gtAngular),
       3, uint(QCPPolarGrid::gtRadial),
       4, uint(QCPPolarGrid::gtAll),
       5, uint(QCPPolarGrid::gtNone),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN12QCPPolarGridE.offsetsAndSizes,
    qt_meta_data_ZN12QCPPolarGridE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12QCPPolarGridE_t,
        // enum 'GridType'
        QtPrivate::TypeAndForceComplete<QCPPolarGrid::GridType, std::true_type>,
        // enum 'GridTypes'
        QtPrivate::TypeAndForceComplete<QCPPolarGrid::GridTypes, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarGrid, std::true_type>
    >,
    nullptr
} };

void QCPPolarGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPPolarGrid *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *QCPPolarGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12QCPPolarGridE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPPolarGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN18QCPPolarLegendItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18QCPPolarLegendItemE = QtMocHelpers::stringData(
    "QCPPolarLegendItem"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18QCPPolarLegendItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarLegendItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractLegendItem::staticMetaObject>(),
    qt_meta_stringdata_ZN18QCPPolarLegendItemE.offsetsAndSizes,
    qt_meta_data_ZN18QCPPolarLegendItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18QCPPolarLegendItemE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarLegendItem, std::true_type>
    >,
    nullptr
} };

void QCPPolarLegendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPPolarLegendItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *QCPPolarLegendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarLegendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18QCPPolarLegendItemE.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractLegendItem::qt_metacast(_clname);
}

int QCPPolarLegendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractLegendItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN13QCPPolarGraphE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QCPPolarGraphE = QtMocHelpers::stringData(
    "QCPPolarGraph",
    "selectionChanged",
    "",
    "selected",
    "QCPDataSelection",
    "selection",
    "selectableChanged",
    "QCP::SelectionType",
    "selectable",
    "setSelectable",
    "setSelection",
    "LineStyle",
    "lsNone",
    "lsLine"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QCPPolarGraphE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       1,   59, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    2 /* Public */,
       1,    1,   47,    2, 0x06,    4 /* Public */,
       6,    1,   50,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   53,    2, 0x0a,    8 /* Public */,
      10,    1,   56,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 4,    5,

 // enums: name, alias, flags, count, data
      11,   11, 0x0,    2,   64,

 // enum data: key, value
      12, uint(QCPPolarGraph::lsNone),
      13, uint(QCPPolarGraph::lsLine),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_ZN13QCPPolarGraphE.offsetsAndSizes,
    qt_meta_data_ZN13QCPPolarGraphE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QCPPolarGraphE_t,
        // enum 'LineStyle'
        QtPrivate::TypeAndForceComplete<QCPPolarGraph::LineStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarGraph, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPDataSelection &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPDataSelection, std::false_type>
    >,
    nullptr
} };

void QCPPolarGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCPPolarGraph *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        case 2: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 3: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 4: _t->setSelection((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCPPolarGraph::*)(bool );
            if (_q_method_type _q_method = &QCPPolarGraph::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarGraph::*)(const QCPDataSelection & );
            if (_q_method_type _q_method = &QCPPolarGraph::selectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCPPolarGraph::*)(QCP::SelectionType );
            if (_q_method_type _q_method = &QCPPolarGraph::selectableChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *QCPPolarGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QCPPolarGraphE.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPPolarGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QCPPolarGraph::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPPolarGraph::selectionChanged(const QCPDataSelection & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPPolarGraph::selectableChanged(QCP::SelectionType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_tag_ZN3QCPE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN3QCPE = QtMocHelpers::stringData(
    "QCP",
    "ResolutionUnit",
    "ruDotsPerMeter",
    "ruDotsPerCentimeter",
    "ruDotsPerInch",
    "ExportPen",
    "epNoCosmetic",
    "epAllowCosmetic",
    "SignDomain",
    "sdNegative",
    "sdBoth",
    "sdPositive",
    "MarginSide",
    "msLeft",
    "msRight",
    "msTop",
    "msBottom",
    "msAll",
    "msNone",
    "MarginSides",
    "AntialiasedElement",
    "aeAxes",
    "aeGrid",
    "aeSubGrid",
    "aeLegend",
    "aeLegendItems",
    "aePlottables",
    "aeItems",
    "aeScatters",
    "aeFills",
    "aeZeroLine",
    "aeOther",
    "aeAll",
    "aeNone",
    "AntialiasedElements",
    "PlottingHint",
    "phNone",
    "phFastPolylines",
    "phImmediateRefresh",
    "phCacheLabels",
    "PlottingHints",
    "Interaction",
    "iNone",
    "iRangeDrag",
    "iRangeZoom",
    "iMultiSelect",
    "iSelectPlottables",
    "iSelectAxes",
    "iSelectLegend",
    "iSelectItems",
    "iSelectOther",
    "iSelectPlottablesBeyondAxisRect",
    "Interactions",
    "SelectionRectMode",
    "srmNone",
    "srmZoom",
    "srmSelect",
    "srmCustom",
    "SelectionType",
    "stNone",
    "stWhole",
    "stSingleData",
    "stDataRange",
    "stMultipleDataRanges"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN3QCPE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
      13,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   79,
       5,    5, 0x0,    2,   85,
       8,    8, 0x0,    3,   89,
      12,   12, 0x0,    6,   95,
      19,   12, 0x1,    6,  107,
      20,   20, 0x0,   13,  119,
      34,   20, 0x1,   13,  145,
      35,   35, 0x0,    4,  171,
      40,   35, 0x1,    4,  179,
      41,   41, 0x0,   10,  187,
      52,   41, 0x1,   10,  207,
      53,   53, 0x0,    4,  227,
      58,   58, 0x0,    5,  235,

 // enum data: key, value
       2, uint(QCP::ruDotsPerMeter),
       3, uint(QCP::ruDotsPerCentimeter),
       4, uint(QCP::ruDotsPerInch),
       6, uint(QCP::epNoCosmetic),
       7, uint(QCP::epAllowCosmetic),
       9, uint(QCP::sdNegative),
      10, uint(QCP::sdBoth),
      11, uint(QCP::sdPositive),
      13, uint(QCP::msLeft),
      14, uint(QCP::msRight),
      15, uint(QCP::msTop),
      16, uint(QCP::msBottom),
      17, uint(QCP::msAll),
      18, uint(QCP::msNone),
      13, uint(QCP::msLeft),
      14, uint(QCP::msRight),
      15, uint(QCP::msTop),
      16, uint(QCP::msBottom),
      17, uint(QCP::msAll),
      18, uint(QCP::msNone),
      21, uint(QCP::aeAxes),
      22, uint(QCP::aeGrid),
      23, uint(QCP::aeSubGrid),
      24, uint(QCP::aeLegend),
      25, uint(QCP::aeLegendItems),
      26, uint(QCP::aePlottables),
      27, uint(QCP::aeItems),
      28, uint(QCP::aeScatters),
      29, uint(QCP::aeFills),
      30, uint(QCP::aeZeroLine),
      31, uint(QCP::aeOther),
      32, uint(QCP::aeAll),
      33, uint(QCP::aeNone),
      21, uint(QCP::aeAxes),
      22, uint(QCP::aeGrid),
      23, uint(QCP::aeSubGrid),
      24, uint(QCP::aeLegend),
      25, uint(QCP::aeLegendItems),
      26, uint(QCP::aePlottables),
      27, uint(QCP::aeItems),
      28, uint(QCP::aeScatters),
      29, uint(QCP::aeFills),
      30, uint(QCP::aeZeroLine),
      31, uint(QCP::aeOther),
      32, uint(QCP::aeAll),
      33, uint(QCP::aeNone),
      36, uint(QCP::phNone),
      37, uint(QCP::phFastPolylines),
      38, uint(QCP::phImmediateRefresh),
      39, uint(QCP::phCacheLabels),
      36, uint(QCP::phNone),
      37, uint(QCP::phFastPolylines),
      38, uint(QCP::phImmediateRefresh),
      39, uint(QCP::phCacheLabels),
      42, uint(QCP::iNone),
      43, uint(QCP::iRangeDrag),
      44, uint(QCP::iRangeZoom),
      45, uint(QCP::iMultiSelect),
      46, uint(QCP::iSelectPlottables),
      47, uint(QCP::iSelectAxes),
      48, uint(QCP::iSelectLegend),
      49, uint(QCP::iSelectItems),
      50, uint(QCP::iSelectOther),
      51, uint(QCP::iSelectPlottablesBeyondAxisRect),
      42, uint(QCP::iNone),
      43, uint(QCP::iRangeDrag),
      44, uint(QCP::iRangeZoom),
      45, uint(QCP::iMultiSelect),
      46, uint(QCP::iSelectPlottables),
      47, uint(QCP::iSelectAxes),
      48, uint(QCP::iSelectLegend),
      49, uint(QCP::iSelectItems),
      50, uint(QCP::iSelectOther),
      51, uint(QCP::iSelectPlottablesBeyondAxisRect),
      54, uint(QCP::srmNone),
      55, uint(QCP::srmZoom),
      56, uint(QCP::srmSelect),
      57, uint(QCP::srmCustom),
      59, uint(QCP::stNone),
      60, uint(QCP::stWhole),
      61, uint(QCP::stSingleData),
      62, uint(QCP::stDataRange),
      63, uint(QCP::stMultipleDataRanges),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCP::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN3QCPE.offsetsAndSizes,
    qt_meta_data_ZN3QCPE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN3QCPE_t,
        // enum 'ResolutionUnit'
        QtPrivate::TypeAndForceComplete<QCP::ResolutionUnit, std::true_type>,
        // enum 'ExportPen'
        QtPrivate::TypeAndForceComplete<QCP::ExportPen, std::true_type>,
        // enum 'SignDomain'
        QtPrivate::TypeAndForceComplete<QCP::SignDomain, std::true_type>,
        // enum 'MarginSide'
        QtPrivate::TypeAndForceComplete<QCP::MarginSide, std::true_type>,
        // enum 'MarginSides'
        QtPrivate::TypeAndForceComplete<QCP::MarginSides, std::true_type>,
        // enum 'AntialiasedElement'
        QtPrivate::TypeAndForceComplete<QCP::AntialiasedElement, std::true_type>,
        // enum 'AntialiasedElements'
        QtPrivate::TypeAndForceComplete<QCP::AntialiasedElements, std::true_type>,
        // enum 'PlottingHint'
        QtPrivate::TypeAndForceComplete<QCP::PlottingHint, std::true_type>,
        // enum 'PlottingHints'
        QtPrivate::TypeAndForceComplete<QCP::PlottingHints, std::true_type>,
        // enum 'Interaction'
        QtPrivate::TypeAndForceComplete<QCP::Interaction, std::true_type>,
        // enum 'Interactions'
        QtPrivate::TypeAndForceComplete<QCP::Interactions, std::true_type>,
        // enum 'SelectionRectMode'
        QtPrivate::TypeAndForceComplete<QCP::SelectionRectMode, std::true_type>,
        // enum 'SelectionType'
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<void, std::true_type>
    >,
    nullptr
} };

QT_WARNING_POP
