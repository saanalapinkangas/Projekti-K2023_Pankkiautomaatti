
#ifndef DLL_RFID_GLOBAL_H
#define DLL_RFID_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLL_RFID_LIBRARY)
#  define DLL_RFID_EXPORT Q_DECL_EXPORT
#else
#  define DLL_RFID_EXPORT Q_DECL_IMPORT
#endif

#endif // DLL_RFID_GLOBAL_H
