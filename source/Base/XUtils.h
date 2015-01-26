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

#ifndef __XUTILS_H__
#define __XUTILS_H__

#include "XPlatform.h"
#include "XTypes.h"

/**
 * Joins two arguments together even if they are macros
 * themselves (see sec 16.3.1 in the C++ standard).
 */
#define X_MACRO_DO_JOIN2( X,Y ) X##Y
#define X_MACRO_DO_JOIN( X,Y )  X_MACRO_DO_JOIN2(X,Y)
#define X_MACRO_JOIN( X,Y )     X_MACRO_DO_JOIN(X,Y)



// macro to str.
#define X_MACRO_STR2( x )	#x
#define X_MACRO_STR( x )	X_MACRO_STR2( x )


#define X_BIT( b )	1 << (b)


#define X_RET_IF( exp ) if ( exp ) return
#define X_RET_VAL_IF( exp, val ) if ( exp ) return val


// ---------------------------------------------------------------------------
#define X_NEW new
#define X_SAFE_DEL( ptr )       if ( ptr ) { delete (ptr); (ptr) = 0; }
#define X_SAFE_DEL_ARR( ptr )   if ( ptr ) { delete [] (ptr); (ptr) = 0; }



// ---------------------------------------------------------------------------
// macro to define a class without copy ctor nor assignment operator.
#define X_NO_COPY_CLASS( classname )        \
    private:                                \
    classname(const classname&);            \
    classname& operator=(const classname&);





X_NS_BEGIN



// ---------------------------------------------------------------------------
// fourCC
template < XUInt8 a, XUInt8 b, XUInt8 c, XUInt8 d >
struct XFourCC
{
    static const XUInt8 value = ( d << 24 ) | ( c << 16 ) | ( b << 8 ) | a;
};



typedef XInt32  XRet;
#define X_SUCCESS    0
#define X_ERROR     -1

template < class T, class F >
X_FORCEINLINE XUInt32 getOffset( F T::* field )
{
    return (XUInt32) (XUIntPtr) &( ((T*)nullptr)->*field);
}

template < typename T >
struct TArrayHelper
{
    static XUInt32 getArrayCount() { return 1; }
};

template < typename T, XUInt32 N >
struct TArrayHelper< T[N] >
{
    static XUInt32 getArrayCount() { return N; }
};


X_NS_END

#endif // __XUTILS_H__