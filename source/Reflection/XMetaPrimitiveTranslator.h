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


template < typename T, XMetaPrimitiveType PT >
class XMetaPrimitiveTranslator_T
	: public XMetaPrimitiveTranslator
{
    
public:
    
	virtual XMetaPrimitiveType         getPrimitiveType() const override {
		return PT;
	}
    
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
: public XMetaPointerTranslator
{
public:
    
    virtual const XMetaTranslator*      getTargetTranslator() const
    {
        return XMetaTranslatorHelper< typename std::remove_pointer<T>::type >::getTranslator();
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
class XMetaTranslatorHelper<T*>
{
public:
    static const XMetaTranslator*    getTranslator()
    {
        static TPointerTranslator<T*> s_kIns;
        return &s_kIns;
    }
};

//------------------------------------------------------------------------------
#define X_DECLARE_PRIMITIVE_TRANSLATOR( t, st )  \
template <> \
class XTranslatorHelper< t >    \
{   \
public: \
    static XMetaTranslator*    getTranslator() \
    {   \
        static XMetaPrimitiveTranslator_T<t, st> s_kIns;    \
        return &s_kIns; \
    }   \
};

X_DECLARE_PRIMITIVE_TRANSLATOR( XBool, XMetaPrimitiveType::BOOL );

X_DECLARE_PRIMITIVE_TRANSLATOR( XFloat, XMetaPrimitiveType::FLOAT );
X_DECLARE_PRIMITIVE_TRANSLATOR( XDouble, XMetaPrimitiveType::DOUBLE );


X_DECLARE_PRIMITIVE_TRANSLATOR( XLong, XMetaPrimitiveType::LONG );
X_DECLARE_PRIMITIVE_TRANSLATOR( XULong, XMetaPrimitiveType::ULONG );

X_DECLARE_PRIMITIVE_TRANSLATOR( XInt8, XMetaPrimitiveType::I8 );
X_DECLARE_PRIMITIVE_TRANSLATOR( XInt16, XMetaPrimitiveType::I16 );
X_DECLARE_PRIMITIVE_TRANSLATOR( XInt32, XMetaPrimitiveType::I32 );
X_DECLARE_PRIMITIVE_TRANSLATOR( XInt64, XMetaPrimitiveType::I64 );

X_DECLARE_PRIMITIVE_TRANSLATOR( XUInt8, XMetaPrimitiveType::UI8 );
X_DECLARE_PRIMITIVE_TRANSLATOR( XUInt16, XMetaPrimitiveType::UI16 );
X_DECLARE_PRIMITIVE_TRANSLATOR( XUInt32, XMetaPrimitiveType::UI32 );
X_DECLARE_PRIMITIVE_TRANSLATOR( XUInt64, XMetaPrimitiveType::UI64 );

X_DECLARE_PRIMITIVE_TRANSLATOR( XString, XMetaPrimitiveType::STRING );
X_DECLARE_PRIMITIVE_TRANSLATOR( XWString, XMetaPrimitiveType::WSTRING );

X_NS_END

#endif // __XMETASCALARTRANSLATOR_H__