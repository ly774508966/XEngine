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

#ifndef __XMETACLASS_H__
#define __XMETACLASS_H__

#include "XMetaObject.h"
#include "XMetaField.h"
#include "XMetaMethod.h"

X_NS_BEGIN

template < typename T >
class XMetaClassHelper;

typedef XVoid (*TFunMetaClassInit)( XMetaClass& );

#define RET_BASE_CLASS_ALREADY_EXIST    -1

class X_API XMetaClass
    : public XMetaObject
{
protected:
	XUInt32						m_uiCrc32;
    XUInt32                     m_uiSize;
    
    TFunMetaClassInit           m_pkFunInitFields;
    TFunMetaClassInit           m_pkFunInitMethods;
    

    mutable TVecMetaClasses     m_vecBaseClasses;

    mutable TMapMetaEnums       m_mapEnums;
    mutable TMapMetaFields      m_mapFields;
    mutable TMapMetaMethods     m_mapMethods;
    
    XBool                       m_bFieldsInited;
    XBool                       m_bMethodsInited;
    
private:
    static std::map< std::string, const XMetaClass* >  ms_mapMetaClasses;
    
public:
    XMetaClass( const XString& strName, XUInt32 size, TFunMetaClassInit fun_parents, TFunMetaClassInit fun_fields, TFunMetaClassInit fun_methods );
    
	XUInt32						getCrc32() const { return m_uiCrc32;  }
    XUInt32                     getSize() const { return m_uiSize; }
    
    XRet                        addBaseClass( const XMetaClass* pkBase );
    
    template < typename T >
    XBool                       isKindOf() const;
    XBool                       isKindOf( const XMetaClass* pkMetaClass ) const;
    XBool                       isKindOf( const XString& strTypeName ) const;
    
    template< typename TC, typename TF >
    const XMetaField*           registerField( const XString& strName, TF TC::* f, unsigned int uiFlag = 0 );
    template< typename TF >
    const XMetaField*           registerField( const XString& strName, TF* f, unsigned int uiFlag = 0 );
    const XMetaField*           getFieldByName( const XString& strName ) const;
    const TMapMetaFields&       getAllFields() const { const_cast<XMetaClass*>(this)->lazyInitFields(); return m_mapFields; }
    
    template< typename TFun >
    const XMetaMethod*          registerMethod( const XString& strName, TFun f ) const;
    const TVecMetaMethods*      getMethodsByName( const XString& strName ) const;
    const TMapMetaMethods&      getAllMethods() const { const_cast<XMetaClass*>(this)->lazyInitMethods(); return m_mapMethods; }
    
protected:
    XVoid                       lazyInitFields();
    XVoid                       lazyInitMethods();
};

//------------------------------------------------------------------------------
template < typename T >
XBool XMetaClass::isKindOf() const
{
    return isKindOf( T::ms_kMetaClass.getName() );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XBool XMetaClass::isKindOf( const XMetaClass* pkMetaClass ) const
{
    assert( pkMetaClass != nullptr );
    return isKindOf( pkMetaClass->getName() );
}

//------------------------------------------------------------------------------
template< typename TC, typename TF >
const XMetaField* XMetaClass::registerField(const XString& strName, TF TC::* f, unsigned int uiFlag )
{
    const XMetaField* pkField = new XMetaField( this, strName, f, uiFlag );
    m_mapFields.insert( std::make_pair( pkField->getName(), pkField ) );
    return pkField;
}

//------------------------------------------------------------------------------
template< typename TF >
const XMetaField* XMetaClass::registerField( const XString& strName, TF* f, unsigned int uiFlag )
{
    const XMetaField* pkField = new XMetaField( this, strName, f, uiFlag );
    m_mapFields.insert( std::make_pair( pkField->getName(), pkField ) );
    return pkField;
}


//------------------------------------------------------------------------------
template< typename TFun >
const XMetaMethod* XMetaClass::registerMethod( const XString& strName, TFun f ) const
{
    /*
    const XMetaMethod* pkMethod = new XMetaMethod_T< TFun >( this, strName, f );
    assert( pkMethod != nullptr );
    m_mapMethods[strName].push_back( pkMethod );
    return pkMethod;
     */
    return nullptr;
}


//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XMetaClass::lazyInitFields()
{
    X_RET_IF( m_bFieldsInited );
    
    if ( m_pkFunInitFields )
    {
        (*m_pkFunInitFields)( *this );
    }
    
    m_bFieldsInited = true;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XMetaClass::lazyInitMethods()
{
    X_RET_IF( m_bMethodsInited );
    
    if ( m_pkFunInitMethods )
    {
        (*m_pkFunInitMethods)( *this );
    }
    
    m_bMethodsInited = true;
}


//------------------------------------------------------------------------------
#define X_DECLARE_META_CLASS( class_name )    \
public: \
    virtual const XMetaClass* getMetaClass() const { return &ms_kMetaClass; } \
    static const XMetaClass ms_kMetaClass;    \
    static XRet ms_registerRet;   \
    static XVoid buildMetaParents( XMetaClass& kMetaClass );    \
    static XVoid buildMetaFields( XMetaClass& kMetaClass ); \
    static XVoid buildMetaMethods( XMetaClass& kMetaClass );    \


#define X_IMPLEMENT_META_CLASS( class_name, b, f, m ) \
    const XMetaClass class_name::ms_kMetaClass( #class_name, sizeof( class_name ), &class_name::buildMetaParents, &class_name::buildMetaFields, &class_name::buildMetaMethods );   \
    XRet class_name::ms_registerRet = XMetaSystem::getIns().registerMetaClass( &class_name::ms_kMetaClass );  \
    XVoid class_name::buildMetaParents( XMetaClass& kMetaClass ) { b }  \
    XVoid class_name::buildMetaFields( XMetaClass& kMetaClass ) { f }  \
    XVoid class_name::buildMetaMethods( XMetaClass& kMetaClass ) { m }

#define X_META_BASE( base_name ) kMetaClass.addBaseClass( &base_name::ms_kMetaClass );
#define X_META_FIELD( n, f, flag )  kMetaClass.registerField( n, f, flag );
#define X_META_METHOD( n, m ) kMetaClass.registerMethod( n, m );

#define IS_KINDOF( ptr, name ) (ptr)->getMetaClass()->isKindOf( name )
#define IS_KINDOF_TYPE( ptr, type )   (ptr)->getMetaClass()->isKindOf<type>()

X_NS_END

#endif // __XMETACLASS_H__
