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

#ifndef __XMETASCALARTRANSLATOR_H__
#define __XMETASCALARTRANSLATOR_H__

#include "XMetaTranslator.h"
#include "XMetaField.h"

X_NS_BEGIN


template < typename T, eScalarType ST >
class XScalarTranslator_T
: public XScalarTranslator
{
    
public:
    
    virtual eScalarType                 getScalarType() const { return ST; }
    
    virtual XBool                       equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        const T& src = kSrc.as<T>();
        const T& dest = kDest.as<T>();
        return src == dest;
    }
    
    virtual XVoid                       copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        const T& src = kSrc.as<T>();
        T& dest = kDest.as<T>();
        dest = src;
    }
};


//------------------------------------------------------------------------------
template < typename T >
class TPointerTranslator
: public XPointerTranslator
{
public:
    
    virtual const XMetaTranslator*      getTargetTranslator() const
    {
        return XTranslatorHelper< typename std::remove_pointer<T>::type >::getTranslator();
    }
    
    virtual XBool                       equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        const T& src = kSrc.as<T>();
        const T& dest = kDest.as<T>();
        //return *src == *dest;
    }
    
    virtual XVoid                       copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        const T& src = kSrc.as<T>();
        T& dest = kDest.as<T>();
        //*dest = *src;
    }
};



//------------------------------------------------------------------------------
template < typename T >
class XTranslatorHelper<T*>
{
public:
    static const XMetaTranslator*    getTranslator()
    {
        static TPointerTranslator<T*> s_kIns;
        return &s_kIns;
    }
};

//------------------------------------------------------------------------------
#define DECLARE_SCALAR_TRANSLATOR( t, st )  \
template <> \
class XTranslatorHelper< t >    \
{   \
public: \
    static XMetaTranslator*    getTranslator() \
    {   \
        static XScalarTranslator_T<t, st> s_kIns;    \
        return &s_kIns; \
    }   \
};

DECLARE_SCALAR_TRANSLATOR( XBool, ST_BOOL );

DECLARE_SCALAR_TRANSLATOR( XFloat, ST_FLOAT );
DECLARE_SCALAR_TRANSLATOR( XDouble, ST_DOUBLE );


DECLARE_SCALAR_TRANSLATOR( XLong, ST_LONG );
DECLARE_SCALAR_TRANSLATOR( XULong, ST_ULONG );

DECLARE_SCALAR_TRANSLATOR( XInt8, ST_I8 );
DECLARE_SCALAR_TRANSLATOR( XInt16, ST_I16 );
DECLARE_SCALAR_TRANSLATOR( XInt32, ST_I32 );
DECLARE_SCALAR_TRANSLATOR( XInt64, ST_I64 );

DECLARE_SCALAR_TRANSLATOR( XUInt8, ST_UI8 );
DECLARE_SCALAR_TRANSLATOR( XUInt16, ST_UI16 );
DECLARE_SCALAR_TRANSLATOR( XUInt32, ST_UI32 );
DECLARE_SCALAR_TRANSLATOR( XUInt64, ST_UI64 );

DECLARE_SCALAR_TRANSLATOR( XString, ST_STRING );
DECLARE_SCALAR_TRANSLATOR( XWString, ST_WSTRING );

X_NS_END

#endif // __XMETASCALARTRANSLATOR_H__