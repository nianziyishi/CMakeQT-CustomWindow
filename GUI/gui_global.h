#ifndef GUI_GLOBAL_H
#define GUI_GLOBAL_H

//#include <QtCore/qglobal.h>

#if defined(_WIN32) && defined(SHARED_LIB)
# if defined(GUI_LIB)
#  define GUI_EXPORT __declspec(dllexport)
# else
#  define GUI_EXPORT __declspec(dllimport)
# endif
#else
# define GUI_EXPORT
#endif

#endif // GUI_GLOBAL_H 
