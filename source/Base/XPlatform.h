/******************************************************************************
**
**  https://github.com/xfxdev/XEngine
**  
**  Copyright 2014, xfx.dev <xfx.dev@gmail.com>
**
**  License: The MIT License (http://www.opensource.org/licenses/mit-license.php)
**
**  Permission is hereby granted, free of charge, to any person obtaining a copy
**  of this software and associated documentation files (the "Software"), to deal
**  in the Software without restriction, including without limitation the rights
**  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
**  copies of the Software, and to permit persons to whom the Software is
**  furnished to do so, subject to the following conditions:
**
**  The above copyright notice and this permission notice shall be included in all
**  copies or substantial portions of the Software.
**
**  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
**  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
**  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
**  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
**  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
**  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
**  SOFTWARE.
**
******************************************************************************/

#ifndef __XPLATFORM_H__
#define __XPLATFORM_H__

/* platform definition.
*
* Operating system:
*   X_OS_WIN (Windows)
*   X_OS_MAC (MacOSX)
*   X_OS_LINUX (Linux)
*   X_OS_IOS (iOS)
*	X_OS_ANDROID ( android )
*
* Architecture:
*   X_ARCH_IX86 (Intel x86)
*   X_ARCH_AMD64 (AMD64)
*   X_ARCH_ARM (Advanced RISC Machine)
*
* Processor:
*   X_CPU_32 (32bit processor)
*   X_CPU_64 (64bit processor)
*
* Compiler:
*   X_COMPILER_MSC (Microsoft Compiler)
*   X_COMPILER_GNU (GNU Compiler)
*   X_COMPILER_INTEL (Intel Compiler)
*   X_COMPILER_CLANG (Clang Compiler)
*
* These definitions are based on the information found here:
* http://predef.sourceforge.net/index.php
*
*/


/* find os: ---------------------------------------------- */
#if defined( _WIN32 ) || defined( _WIN64 )
#	define X_OS_WIN 1
#elif defined( __APPLE__ ) || defined( __MACH__ )
#	include "TargetConditionals.h"
#	if TARGET_IPHONE_SIMULATOR	// iOS Simulator
#	elif TARGET_OS_IPHONE		// iOS device
#		define X_OS_IOS 1
#	elif TARGET_OS_MAC
#		define X_OS_MAC 1
#	else
#		error Unknown platform.
#	endif
#elif defined( linux ) || defined( __linux ) || defined( __linux__ )
#	define X_OS_LINUX 1
#elif defined( __ANDROID__ )
#	define X_OS_ANDROID 1
#else
#	error Unknown platform!!!
#endif


/* find architecture: ---------------------------------------------- */
#if defined(__x86_64__) || defined(_M_X64)
/* x86 64-bit ----------------------------------------------- */

#elif defined(__i386) || defined(_M_IX86)
/* x86 32-bit ----------------------------------------------- */

#endif


/* find compiler: ---------------------------------------------- */
#if defined( _MSC_VER )
#	define X_COMPILER_MSC 1
#elif defined(__GNUC__) || defined(__GNUG__)
#	define X_COMPILER_GNU 1
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#	define X_COMPILER_INTEL 1
#elif defined(__clang__)
#	define X_COMPILER_CLANG 1
#else
#	error Unknown compiler!!!
#endif


// define export and import.
#if defined( X_COMPILER_MSC )
#   define X_API_EXPORT __declspec( dllexport )
#   define X_API_IMPORT __declspec( dllimport )
#else
#   define X_API_EXPORT
#   define X_API_IMPORT
#endif


#if defined( X_SHARED )
#   if defined( X_EXPORTS )
#       define X_API X_API_EXPORT
#   else
#       define X_API X_API_IMPORT
#   endif
#else
#   define X_API
#endif



// define force inline.
#if defined( X_COMPILER_MSC )
#   define X_FORCEINLINE __forceinline
#elif defined( X_COMPILER_GNU ) || defined( X_COMPILER_CLANG )
#   define X_FORCEINLINE inline __attribute__( ( always_inline ) )
#endif


#endif // __XPLATFORM_H__