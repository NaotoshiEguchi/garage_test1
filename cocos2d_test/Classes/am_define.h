#ifndef _AM_DEFINE_H_
#define _AM_DEFINE_H_

#ifndef NULL
#define NULL 0
#endif

#ifdef _WIN32
#define TARGET_WINDOWS
#else
#define TARGET_IPHONE
#endif

typedef signed char Sint8; 
typedef unsigned char Uint8; 
typedef signed short Sint16;
typedef unsigned short Uint16;
typedef signed int Sint32;
typedef unsigned int Uint32;

#define PI 3.1415926535

#if defined(TARGET_WINDOWS)
#include "crtdbg.h"
#define DEBUG_BREAK		_CrtDbgBreak();
#elif defined(TARGET_IPHONE)
#define DEBUG_BREAK		;
#endif

#define AsAssert(_a_) \
	do {\
		if ((_a_) == 0) DEBUG_BREAK \
	} while(0)


#define ARRAY_NUM(_name_)  (sizeof (_name_) / sizeof (_name_)[0])

#define DEG_TO_RAD(_deg_) ((_deg_) / 180.0f * PI)

#endif
