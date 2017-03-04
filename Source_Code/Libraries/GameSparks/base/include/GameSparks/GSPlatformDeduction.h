/****************************************************************************
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __GS_PLATFORM_DEDUCTION_H__
#define __GS_PLATFORM_DEDUCTION_H__

/**

This file is an adaptation of CCPlatformConfig.h of cocos2d-x.
The names have been adapted to conform with the naming convention of
GaeSparks and to avoid conficts.

original copyright header:

Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

http://www.cocos2d-x.org

*/

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which CC uses.
#define GS_PLATFORM_UNKNOWN            0
#define GS_PLATFORM_IOS                1
#define GS_PLATFORM_ANDROID            2
#define GS_PLATFORM_WIN32              3
#define GS_PLATFORM_MARMALADE          4
#define GS_PLATFORM_LINUX              5
#define GS_PLATFORM_BADA               6
#define GS_PLATFORM_BLACKBERRY         7
#define GS_PLATFORM_MAC                8
#define GS_PLATFORM_NACL               9
//#define GS_PLATFORM_EMSCRIPTEN        10
//#define GS_PLATFORM_TIZEN             11
//#define GS_PLATFORM_QT5               12
//#define GS_PLATFORM_WP8               13
//#define GS_PLATFORM_WINRT             14


// Determine target platform by compile environment macro.
#define GS_TARGET_PLATFORM             GS_PLATFORM_UNKNOWN


#if defined(_WIN32)
#	undef  GS_TARGET_PLATFORM
#	define GS_TARGET_PLATFORM GS_PLATFORM_WIN32
#	if defined(_WIN64)
#		undef  GS_TARGET_PLATFORM
#		define GS_TARGET_PLATFORM GS_PLATFORM_WIN32
#	endif
#elif __APPLE__ && !defined(IW_SDK)
#	include "TargetConditionals.h"
#	if TARGET_IPHONE_SIMULATOR
#		undef  GS_TARGET_PLATFORM
#		define GS_TARGET_PLATFORM GS_PLATFORM_IOS
#	elif TARGET_OS_IPHONE
#		undef  GS_TARGET_PLATFORM
#		define GS_TARGET_PLATFORM GS_PLATFORM_IOS
#	elif TARGET_OS_MAC
#		undef  GS_TARGET_PLATFORM
#		define GS_TARGET_PLATFORM GS_PLATFORM_MAC
#	else
#		error "unsupported apple platform"
#	endif
#elif __linux
#	undef  GS_TARGET_PLATFORM
#	define GS_TARGET_PLATFORM GS_PLATFORM_LINUX
#elif defined(__unix) // all unices not caught above
#	undef  GS_TARGET_PLATFORM
#	define GS_TARGET_PLATFORM GS_PLATFORM_LINUX
#elif __posix
#	undef  GS_TARGET_PLATFORM
#	define GS_TARGET_PLATFORM GS_PLATFORM_LINUX
#endif

// android
#if defined(__ANDROID_API__)
#undef  GS_TARGET_PLATFORM
#define GS_TARGET_PLATFORM         GS_PLATFORM_ANDROID
#endif

// marmalade
#if defined(IW_SDK)
#undef  GS_TARGET_PLATFORM
#define GS_TARGET_PLATFORM         GS_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  GS_TARGET_PLATFORM
#define GS_TARGET_PLATFORM         GS_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
#undef  GS_TARGET_PLATFORM
#define GS_TARGET_PLATFORM     GS_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
#undef  GS_TARGET_PLATFORM
#define GS_TARGET_PLATFORM     GS_PLATFORM_NACL
#endif


//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! GS_TARGET_PLATFORM
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

#if (GS_TARGET_PLATFORM == GS_PLATFORM_WIN32)
#ifndef __MINGW32__
#pragma warning (disable:4127) 
#endif 
#endif  // GS_PLATFORM_WIN32

#endif  // __GS_PLATFORM_DEDUCTION_H__

