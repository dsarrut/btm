#ifndef FORM2_GLOBAL_H
#define FORM2_GLOBAL_H

#include <QtGlobal>

#if defined(FORM2_LIBRARY)
#  define FORM2SHARED_EXPORT Q_DECL_EXPORT
#else
#  define FORM2SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FORM2_GLOBAL_H
