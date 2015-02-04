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

#ifndef __XTYPES_H__
#define __XTYPES_H__

#include "XPreDef.h"

X_NS_BEGIN

typedef void			XVoid;
typedef bool			XBool;
typedef char			XChar;     // note: char != signed char.
typedef signed char     XSChar;
typedef unsigned char	XUChar;
typedef wchar_t         XWChar;
typedef long            XLong;
typedef unsigned long   XULong;
typedef float			XFloat;
typedef double			XDouble;
typedef long double		XLongDouble;

typedef int8_t			XInt8;
typedef int16_t			XInt16;
typedef int32_t			XInt32;
typedef int64_t			XInt64;

typedef uint8_t			XUInt8;
typedef uint16_t		XUInt16;
typedef uint32_t		XUInt32;
typedef uint64_t		XUInt64;

typedef intptr_t		XIntPtr;
typedef uintptr_t		XUIntPtr;

typedef char            XByte;
typedef size_t			XSize;

typedef std::string		XString;
typedef std::wstring	XWString;

typedef std::vector< XString >  XArrString;
typedef std::vector< XWString > XArrWString;

X_NS_END

#endif // __XTYPES_H__