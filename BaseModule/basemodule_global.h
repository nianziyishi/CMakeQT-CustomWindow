#ifndef BASEMODULE_GLOBAL_H
#define BASEMODULE_GLOBAL_H

//#include <QtCore/qglobal.h>

#if defined(_WIN32) && defined(SHARED_LIB)
# if defined(BASEMODULE_LIB)
#  define BASEMODULE_EXPORT __declspec(dllexport)
# else
#  define BASEMODULE_EXPORT __declspec(dllimport)
# endif
#else
# define BASEMODULE_EXPORT
#endif

#endif // BASEMODULE_GLOBAL_H 
