/****************************************************************************
** Meta object code from reading C++ file 'qhexedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qhexedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhexedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QHexEdit_t {
    QByteArrayData data[32];
    char stringdata0[365];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QHexEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QHexEdit_t qt_meta_stringdata_QHexEdit = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QHexEdit"
QT_MOC_LITERAL(1, 9, 21), // "currentAddressChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "address"
QT_MOC_LITERAL(4, 40, 18), // "currentSizeChanged"
QT_MOC_LITERAL(5, 59, 4), // "size"
QT_MOC_LITERAL(6, 64, 11), // "dataChanged"
QT_MOC_LITERAL(7, 76, 20), // "overwriteModeChanged"
QT_MOC_LITERAL(8, 97, 5), // "state"
QT_MOC_LITERAL(9, 103, 4), // "redo"
QT_MOC_LITERAL(10, 108, 4), // "undo"
QT_MOC_LITERAL(11, 113, 6), // "adjust"
QT_MOC_LITERAL(12, 120, 18), // "dataChangedPrivate"
QT_MOC_LITERAL(13, 139, 3), // "idx"
QT_MOC_LITERAL(14, 143, 7), // "refresh"
QT_MOC_LITERAL(15, 151, 12), // "updateCursor"
QT_MOC_LITERAL(16, 164, 11), // "addressArea"
QT_MOC_LITERAL(17, 176, 16), // "addressAreaColor"
QT_MOC_LITERAL(18, 193, 13), // "addressOffset"
QT_MOC_LITERAL(19, 207, 12), // "addressWidth"
QT_MOC_LITERAL(20, 220, 9), // "asciiArea"
QT_MOC_LITERAL(21, 230, 12), // "bytesPerLine"
QT_MOC_LITERAL(22, 243, 14), // "cursorPosition"
QT_MOC_LITERAL(23, 258, 4), // "data"
QT_MOC_LITERAL(24, 263, 7), // "hexCaps"
QT_MOC_LITERAL(25, 271, 19), // "dynamicBytesPerLine"
QT_MOC_LITERAL(26, 291, 12), // "highlighting"
QT_MOC_LITERAL(27, 304, 17), // "highlightingColor"
QT_MOC_LITERAL(28, 322, 13), // "overwriteMode"
QT_MOC_LITERAL(29, 336, 14), // "selectionColor"
QT_MOC_LITERAL(30, 351, 8), // "readOnly"
QT_MOC_LITERAL(31, 360, 4) // "font"

    },
    "QHexEdit\0currentAddressChanged\0\0address\0"
    "currentSizeChanged\0size\0dataChanged\0"
    "overwriteModeChanged\0state\0redo\0undo\0"
    "adjust\0dataChangedPrivate\0idx\0refresh\0"
    "updateCursor\0addressArea\0addressAreaColor\0"
    "addressOffset\0addressWidth\0asciiArea\0"
    "bytesPerLine\0cursorPosition\0data\0"
    "hexCaps\0dynamicBytesPerLine\0highlighting\0"
    "highlightingColor\0overwriteMode\0"
    "selectionColor\0readOnly\0font"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QHexEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
      16,   88, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    0,   75,    2, 0x06 /* Public */,
       7,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   79,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x08 /* Private */,
      12,    1,   82,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x28 /* Private | MethodCloned */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      16, QMetaType::Bool, 0x00095103,
      17, QMetaType::QColor, 0x00095103,
      18, QMetaType::LongLong, 0x00095103,
      19, QMetaType::Int, 0x00095103,
      20, QMetaType::Bool, 0x00095103,
      21, QMetaType::Int, 0x00095103,
      22, QMetaType::LongLong, 0x00095103,
      23, QMetaType::QByteArray, 0x00495103,
      24, QMetaType::Bool, 0x00095103,
      25, QMetaType::Bool, 0x00095103,
      26, QMetaType::Bool, 0x00095103,
      27, QMetaType::QColor, 0x00095103,
      28, QMetaType::Bool, 0x00095103,
      29, QMetaType::QColor, 0x00095103,
      30, QMetaType::Bool, 0x00095103,
      31, QMetaType::QFont, 0x00095103,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       2,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

void QHexEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QHexEdit *_t = static_cast<QHexEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentAddressChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->currentSizeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: _t->dataChanged(); break;
        case 3: _t->overwriteModeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->redo(); break;
        case 5: _t->undo(); break;
        case 6: _t->adjust(); break;
        case 7: _t->dataChangedPrivate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->dataChangedPrivate(); break;
        case 9: _t->refresh(); break;
        case 10: _t->updateCursor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QHexEdit::*)(qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHexEdit::currentAddressChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QHexEdit::*)(qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHexEdit::currentSizeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QHexEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHexEdit::dataChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QHexEdit::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHexEdit::overwriteModeChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QHexEdit *_t = static_cast<QHexEdit *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->addressArea(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->addressAreaColor(); break;
        case 2: *reinterpret_cast< qint64*>(_v) = _t->addressOffset(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->addressWidth(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->asciiArea(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->bytesPerLine(); break;
        case 6: *reinterpret_cast< qint64*>(_v) = _t->cursorPosition(); break;
        case 7: *reinterpret_cast< QByteArray*>(_v) = _t->data(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->hexCaps(); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->dynamicBytesPerLine(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->highlighting(); break;
        case 11: *reinterpret_cast< QColor*>(_v) = _t->highlightingColor(); break;
        case 12: *reinterpret_cast< bool*>(_v) = _t->overwriteMode(); break;
        case 13: *reinterpret_cast< QColor*>(_v) = _t->selectionColor(); break;
        case 14: *reinterpret_cast< bool*>(_v) = _t->isReadOnly(); break;
        case 15: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        QHexEdit *_t = static_cast<QHexEdit *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAddressArea(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setAddressAreaColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setAddressOffset(*reinterpret_cast< qint64*>(_v)); break;
        case 3: _t->setAddressWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setAsciiArea(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setBytesPerLine(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setCursorPosition(*reinterpret_cast< qint64*>(_v)); break;
        case 7: _t->setData(*reinterpret_cast< QByteArray*>(_v)); break;
        case 8: _t->setHexCaps(*reinterpret_cast< bool*>(_v)); break;
        case 9: _t->setDynamicBytesPerLine(*reinterpret_cast< bool*>(_v)); break;
        case 10: _t->setHighlighting(*reinterpret_cast< bool*>(_v)); break;
        case 11: _t->setHighlightingColor(*reinterpret_cast< QColor*>(_v)); break;
        case 12: _t->setOverwriteMode(*reinterpret_cast< bool*>(_v)); break;
        case 13: _t->setSelectionColor(*reinterpret_cast< QColor*>(_v)); break;
        case 14: _t->setReadOnly(*reinterpret_cast< bool*>(_v)); break;
        case 15: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QHexEdit::staticMetaObject = {
    { &QAbstractScrollArea::staticMetaObject, qt_meta_stringdata_QHexEdit.data,
      qt_meta_data_QHexEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QHexEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QHexEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QHexEdit.stringdata0))
        return static_cast<void*>(this);
    return QAbstractScrollArea::qt_metacast(_clname);
}

int QHexEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 16;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QHexEdit::currentAddressChanged(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QHexEdit::currentSizeChanged(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QHexEdit::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QHexEdit::overwriteModeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
