#ifndef PINOUT_GLOBAL_H
#define PINOUT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PINOUT_LIBRARY)
#  define PINOUT_EXPORT Q_DECL_EXPORT
#else
#  define PINOUT_EXPORT Q_DECL_IMPORT
#endif

#endif // PINOUT_GLOBAL_H
