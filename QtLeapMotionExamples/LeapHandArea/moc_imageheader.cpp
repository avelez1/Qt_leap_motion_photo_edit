/****************************************************************************
** Meta object code from reading C++ file 'imageheader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "imageheader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageheader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyObject_t {
    QByteArrayData data[19];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyObject_t qt_meta_stringdata_MyObject = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyObject"
QT_MOC_LITERAL(1, 9, 12), // "_brightness_"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "factor"
QT_MOC_LITERAL(4, 30, 10), // "_contrast_"
QT_MOC_LITERAL(5, 41, 8), // "midpoint"
QT_MOC_LITERAL(6, 50, 10), // "_saturate_"
QT_MOC_LITERAL(7, 61, 1), // "k"
QT_MOC_LITERAL(8, 63, 12), // "_color2gray_"
QT_MOC_LITERAL(9, 76, 17), // "_gaussianBlur_2D_"
QT_MOC_LITERAL(10, 94, 5), // "sigma"
QT_MOC_LITERAL(11, 100, 8), // "truncate"
QT_MOC_LITERAL(12, 109, 9), // "_boxBlur_"
QT_MOC_LITERAL(13, 119, 13), // "_unsharpMask_"
QT_MOC_LITERAL(14, 133, 8), // "strength"
QT_MOC_LITERAL(15, 142, 15), // "_median_filter_"
QT_MOC_LITERAL(16, 158, 10), // "_scaleLin_"
QT_MOC_LITERAL(17, 169, 21), // "create_working_folder"
QT_MOC_LITERAL(18, 191, 20) // "save_working_to_file"

    },
    "MyObject\0_brightness_\0\0factor\0_contrast_\0"
    "midpoint\0_saturate_\0k\0_color2gray_\0"
    "_gaussianBlur_2D_\0sigma\0truncate\0"
    "_boxBlur_\0_unsharpMask_\0strength\0"
    "_median_filter_\0_scaleLin_\0"
    "create_working_folder\0save_working_to_file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x02 /* Public */,
       4,    2,   72,    2, 0x02 /* Public */,
       6,    1,   77,    2, 0x02 /* Public */,
       8,    0,   80,    2, 0x02 /* Public */,
       9,    2,   81,    2, 0x02 /* Public */,
      12,    1,   86,    2, 0x02 /* Public */,
      13,    3,   89,    2, 0x02 /* Public */,
      15,    1,   96,    2, 0x02 /* Public */,
      16,    1,   99,    2, 0x02 /* Public */,
      17,    0,  102,    2, 0x02 /* Public */,
      18,    0,  103,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, QMetaType::Float,    3,
    QMetaType::Int, QMetaType::Float, QMetaType::Float,    3,    5,
    QMetaType::Int, QMetaType::Float,    7,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Float, QMetaType::Float,   10,   11,
    QMetaType::Int, QMetaType::Int,    7,
    QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,   14,
    QMetaType::Int, QMetaType::Int,    7,
    QMetaType::Int, QMetaType::Float,    7,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void MyObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->_brightness_((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->_contrast_((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->_saturate_((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->_color2gray_();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->_gaussianBlur_2D_((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->_boxBlur_((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->_unsharpMask_((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->_median_filter_((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->_scaleLin_((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: { int _r = _t->create_working_folder();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->save_working_to_file();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyObject::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MyObject.data,
    qt_meta_data_MyObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyObject.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
