#ifndef BUSES_GLOBAL_H
#define BUSES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BUSES_LIBRARY)
#  define BUSES_EXPORT Q_DECL_EXPORT
#else
#  define BUSES_EXPORT Q_DECL_IMPORT
#endif

#endif // BUSES_GLOBAL_H
