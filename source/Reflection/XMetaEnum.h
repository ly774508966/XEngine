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

#ifndef __XMETAENUM_H__
#define __XMETAENUM_H__


#include "XMetaObject.h"
#include "XMetaSystem.h"

X_NS_BEGIN

class X_API XEnumObject
{
};

class X_API XMetaEnumElement
{
public:
    XString     strName;
    XUInt32     uiValue;
    XMetaEnumElement( const XString& n, XUInt32 v )
    : strName( n )
    , uiValue( v )
    {
    }
};
typedef std::vector< XMetaEnumElement > TVecMetaEnumElements;


typedef XVoid (*TFunMetaEnumInit)( XMetaEnum& );

class X_API XMetaEnum
    : public XMetaObject
{
protected:
    XUInt32						m_uiCrc32;
    TFunMetaEnumInit            m_pkFunInit;
    XBool                       m_bInited;
    TVecMetaEnumElements        m_vecElements;
public:
    XMetaEnum( const XString& strName, TFunMetaEnumInit f );
    
    XUInt32						getCrc32() const { return m_uiCrc32;  }
    
    XRet                        addElement( const XString& strName, XUInt32 value );
    XRet                        getValueByName( const XString& strName, XUInt32& value ) const;
    XRet                        getNameByValue( XUInt32 value, XString& strName ) const;
    const TVecMetaEnumElements& getAllElements() const { const_cast<XMetaEnum*>(this)->lazyInit(); return m_vecElements; }
    
protected:
    XVoid                       lazyInit();
};



//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XMetaEnum::lazyInit()
{
    X_RET_IF( m_bInited );
    
    if ( m_pkFunInit )
    {
        (*m_pkFunInit)( *this );
    }
    
    m_bInited = true;
}


//------------------------------------------------------------------------------
#define X_DECLARE_META_ENUM( class_name )  \
    public: \
        Enum    m_value;    \
        static const XMetaEnum  ms_kMetaEnum;   \
    public: \
        class_name() : m_value() {} \
        class_name( Enum v ) : m_value( v ) {}  \
        class_name( class_name& r ) : m_value( r.m_value ) {}   \
        operator const Enum&() const { return m_value; } \
    protected:  \
        static XRet ms_registerRet;   \
        static XVoid buildMetaEnum( XMetaEnum& kMetaEnum );

#define X_IMPLEMENT_META_ENUM( class_name, e )   \
    const XMetaEnum class_name::ms_kMetaEnum( #class_name, &class_name::buildMetaEnum ); \
    XRet class_name::ms_registerRet = XMetaSystem::getIns().registerMetaEnum( &class_name::ms_kMetaEnum );  \
    XVoid class_name::buildMetaEnum( XMetaEnum& kMetaEnum ) { e }

#define X_META_ENUM_ELEMENT( e )    \
    kMetaEnum.addElement( #e, e );

X_NS_END

#endif // __XMETAENUM_H__
