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
    
    virtual XVoid*                      newObj() const override { return XMetaTranslator::defaultNewObj<T>(); }
    virtual XVoid                       delObj( XVoid* pAddress ) const override { XMetaTranslator::defaultDelObj<T>( pAddress ); }
    virtual XSize                       getMemSize() const override { return XMetaTranslator::defaultGetMemSize<T>(); }
    virtual XVoid                       construct( XVoid* pAddress ) const override { XMetaTranslator::defaultConstruct<T>( pAddress ); }
    virtual XVoid                       destruct( XVoid* pAddress ) const override { XMetaTranslator::defaultDestruct<T>( pAddress ); }
    
	virtual XMetaPrimitiveType          getPrimitiveType() const override { return PT; }
    
    virtual XBool                       equals( const XVoid* pA, const XVoid* pB ) const override
    {
        X_RET_VAL_IF( pA == pB, true );
        const T& kA = *(T*)pA;
        const T& kB = *(T*)pB;
        return kA == kB;
    }
    virtual XVoid                       assign( XVoid* pDest, const XVoid* pSrc, XUInt32 uiFlag ) const override
    {
        X_RET_IF( pDest == pSrc );
        T& kDest = *(T*)pDest;
        const T& kSrc = *(const T*)pSrc;
        kDest = kSrc;
    }
};

#define X_META_PRIMITIVE_TYPE_TRAVERSAL( op )       \
    op( XMetaPrimitiveType::BOOL, XBool );          \
    op( XMetaPrimitiveType::FLOAT, XFloat );        \
    op( XMetaPrimitiveType::DOUBLE, XDouble );      \
    op( XMetaPrimitiveType::LONG, XLong );          \
    op( XMetaPrimitiveType::ULONG, XULong );        \
    op( XMetaPrimitiveType::I8, XInt8 );            \
    op( XMetaPrimitiveType::I16, XInt16 );          \
    op( XMetaPrimitiveType::I32, XInt32 );          \
    op( XMetaPrimitiveType::I64, XInt64 );          \
    op( XMetaPrimitiveType::UI8, XUInt8 );          \
    op( XMetaPrimitiveType::UI16, XUInt16 );        \
    op( XMetaPrimitiveType::UI32, XUInt32 );        \
    op( XMetaPrimitiveType::UI64, XUInt64 );        \
    op( XMetaPrimitiveType::STRING, XString );      \
    op( XMetaPrimitiveType::WSTRING, XWString );

//------------------------------------------------------------------------------
#define X_DECLARE_PRIMITIVE_TRANSLATOR( pt, t )  \
template <> \
class XMetaTranslatorHelper< t >    \
{   \
public: \
    static XMetaTranslator*    getTranslator() \
    {   \
        static_assert( std::is_arithmetic<t>::value || std::is_same<t,XString>::value || std::is_same<t,XWString>::value, "must arithmetic!" );    \
        static XMetaPrimitiveTranslator_T<t, pt> s_kIns;    \
        return &s_kIns; \
    }   \
};

X_META_PRIMITIVE_TYPE_TRAVERSAL( X_DECLARE_PRIMITIVE_TRANSLATOR )

X_NS_END

#endif // __XMETASCALARTRANSLATOR_H__