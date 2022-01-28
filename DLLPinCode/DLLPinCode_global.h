#ifndef DLLPINCODE_GLOBAL_H
#define DLLPINCODE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLPINCODE_LIBRARY)
#  define DLLPINCODE_EXPORT Q_DECL_EXPORT
#else
#  define DLLPINCODE_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLPINCODE_GLOBAL_H
