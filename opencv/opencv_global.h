#ifndef OPENCV_GLOBAL_H
#define OPENCV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OPENCV_LIBRARY)
#  define OPENCV_EXPORT Q_DECL_EXPORT
#else
#  define OPENCV_EXPORT Q_DECL_IMPORT
#endif

#endif // OPENCV_GLOBAL_H
