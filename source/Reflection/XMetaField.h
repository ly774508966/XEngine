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

#ifndef __XMETAFIELD_H__
#define __XMETAFIELD_H__


#include "Base/XPreDef.h"
#include "Base/XStringUtil.h"
#include "XMetaTranslator.h"

X_NS_BEGIN


enum eMetaFieldFlag
{
    MFF_READ        = X_BIT( 0 ),
    MFF_WRITE       = X_BIT( 1 ),
    MFF_SERIALIZE   = X_BIT( 2 ),
    MFF_SCRIPT      = X_BIT( 3 ),
    MFF_EDITOR      = X_BIT( 4 ),
    
    
    MFF_READ_WRITE = MFF_READ | MFF_WRITE,
};

class XMetaTranslator;
class X_API XMetaField
{
	X_DECLARE_NO_COPY_CLASS( XMetaField );
public:
    friend class XMetaFieldPointer;
protected:
    const XMetaClass*       m_pkParent;

	XString					m_strName;
    
    XBool                   m_bStatic;
    union
    {
        XUInt32             m_uiOffset;     // used if member field.
        XVoid*              m_pAddress;     // used if static field.
    };
    XUInt32                 m_uiSize;
    XUInt32                 m_uiCount;
    XUInt32                 m_uiFlag;
	XUInt32					m_uiCrc32;
    
    const XMetaTranslator*  m_pkTranslator;
    
public:
    
    template< typename TC, typename TF >
    XMetaField( const XMetaClass* pkParent, const XString& strName, TF TC::* f, XUInt32 uiFlag );
    
    
    template< typename TF >
    XMetaField( const XMetaClass* pkParent, const XString& strName, TF* f, XUInt32 uiFlag );
    
	const XMetaClass*       GetParent() const { return m_pkParent; }
	const XString&			getName() const { return m_strName; }
    XUInt32                 getOffset() const { return m_uiOffset; }
    XUInt32                 getSize() const { return m_uiSize; }
    XUInt32                 getCount() const { return m_uiCount; }
	XUInt32					getFlag() const { return m_uiFlag; }
	XUInt32					getCrc32() const { return m_uiCrc32; }
    
    XBool                   isStatic() const { return m_bStatic; }
    
    const XMetaTranslator*  getTranslator() const { return m_pkTranslator; }
};


//------------------------------------------------------------------------------
template< typename TC, typename TF >
XMetaField::XMetaField( const XMetaClass* pkParent, const XString& strName, TF TC::* f, XUInt32 uiFlag )
: m_pkParent( pkParent )
, m_strName( strName )
, m_bStatic( false )
, m_uiOffset( nsXE::getOffset(f) )
, m_uiSize( sizeof( TF ) )
, m_uiCount( TArrayHelper<TF>::getArrayCount() )
, m_uiFlag( uiFlag )
, m_uiCrc32( XStringUtil::crc32( strName ) )
{
    m_pkTranslator = getMetaTranslator<TF>();
    assert( m_pkTranslator != nullptr );
}


//------------------------------------------------------------------------------
template< typename TF >
XMetaField::XMetaField( const XMetaClass* pkParent, const XString& strName, TF* f, XUInt32 uiFlag )
: m_pkParent( pkParent )
, m_strName( strName )
, m_bStatic( true )
, m_pAddress( (XVoid*)f )
, m_uiSize( sizeof( TF ) )
, m_uiCount( TArrayHelper<TF>::getArrayCount() )
, m_uiFlag(uiFlag)
, m_uiCrc32( XStringUtil::crc32(strName) )
{
    m_pkTranslator = getMetaTranslator<TF>();
    assert( m_pkTranslator != nullptr );
}



class XMetaObject;
class X_API XMetaFieldPointer
{
protected:
    XMetaObject*        m_pObj;
    const XMetaField*   m_pkField;
    XVoid*              m_pAddress;
public:
    
    XMetaFieldPointer( XMetaObject* pObj, const XMetaField* pkField, XUInt32 uiIdx = 0 )
    : m_pObj( pObj )
    , m_pkField( pkField )
    {
        assert( m_pObj && m_pkField );
        if ( pkField->isStatic() )
        {
            m_pAddress = (XVoid*)( (XChar*)(m_pkField->m_pAddress) + ( m_pkField->m_uiSize / m_pkField->m_uiCount ) * uiIdx );
        }
        else
        {
            assert( m_pObj != nullptr );
            m_pAddress = (XVoid*)( (XChar*)m_pObj + ( m_pkField->m_uiOffset + ( m_pkField->m_uiSize / m_pkField->m_uiCount ) * uiIdx ) );
        }
    }
    
    XMetaFieldPointer( XMetaObject* pObj, XVoid* pComposite, const XMetaField* pkField, XUInt32 uiIdx = 0 )
    : m_pObj( pObj )
    , m_pkField( pkField )
    {
        assert( m_pObj && m_pkField && pComposite );
        if ( pkField->isStatic() )
        {
            m_pAddress = (XVoid*)( (XChar*)(m_pkField->m_pAddress) + ( m_pkField->m_uiSize / m_pkField->m_uiCount ) * uiIdx );
        }
        else
        {
            assert( m_pObj != nullptr );
            m_pAddress = (XVoid*)( (XChar*)pComposite + ( m_pkField->m_uiOffset + ( ( m_pkField->m_uiSize / m_pkField->m_uiCount ) * uiIdx ) ) );
        }
    }
    
    template < typename T >
    T& as() { return *(T*)&((const XMetaFieldPointer*)(this))->as<T>(); }
    
    template < typename T >
    const T& as() const { return *reinterpret_cast< const T* >( m_pAddress ); }
    
    XVoid*              getAddress() const { return m_pAddress; }
    XMetaObject*        getObject() const { return m_pObj; }
    const XMetaField*   getField() const { return m_pkField; }
};

X_NS_END

#endif // __XMETAFIELD_H__
