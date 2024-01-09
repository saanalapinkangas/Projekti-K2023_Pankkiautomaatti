#ifndef PINUIDLL_GLOBAL_H
#define PINUIDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PINUIDLL_LIBRARY)
#  define PINUIDLL_EXPORT Q_DECL_EXPORT
#else
#  define PINUIDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // PINUIDLL_GLOBAL_H
