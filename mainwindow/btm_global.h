#ifndef BTM_GLOBAL_H
#define BTM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BTM_LIBRARY)
#  define BTMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BTMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BTM_GLOBAL_H
