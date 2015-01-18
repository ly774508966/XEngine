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

#ifndef __XMETAVARIANT_H__
#define __XMETAVARIANT_H__

#include "XMetaType.h"

X_NS_BEGIN

class X_API XMetaVariant
{
public:
    virtual ~XMetaVariant() {}
    virtual const XMetaType&    getMetaType() const = 0;
    virtual const XVoid*        getData() const = 0;
};

template < typename T >
class XMetaVariant_T
: public XMetaVariant
{
protected:
    
    T   m_value;
    
public:
    XMetaVariant_T( const T& v )
    : m_value( v )
    {
    }
    
    virtual const XMetaType&    getMetaType() const { return XMetaTypeHelper<T>::getMetaType(); }
    
    XVoid       setValue( const T& v ) { m_value = v; }
    const T&    getValue() const { return m_value; }
    
    virtual const XVoid*        getData() const { return (XVoid*)&m_value; }
};

template < typename T >
class XMetaVariant_T< T* >
: public XMetaVariant
{
protected:
    
    const T*   m_value;
    
public:
    XMetaVariant_T( const T* v )
    : m_value( v )
    {
    }
    
    virtual const XMetaType&    getMetaType() const { return XMetaTypeHelper<T*>::getMetaType(); }
    
    XVoid       setValue( const T* v ) { m_value = v; }
    const T*    getValue() const { return m_value; }
    
    virtual const XVoid*        getData() const { return (XVoid*)m_value; }
};

template < typename T >
class XMetaVariant_T< T& >
: public XMetaVariant
{
protected:
    
    const T*   m_value;
    
public:
    XMetaVariant_T( const T& v )
    : m_value( &v )
    {
    }
    
    virtual const XMetaType&    getMetaType() const { return XMetaTypeHelper<T&>::getMetaType(); }
    
    XVoid       setValue( const T& v ) { m_value = &v; }
    const T&    getValue() const { return *m_value; }
    
    virtual const XVoid*        getData() const { return (XVoid*)m_value; }
};

X_NS_END
/*
 
#include "Base/XPreDef.h"

X_NS_BEGIN

template < typename T >
class XMetaClassHelper;

enum eMetaVariantType
{
    VT_BOOL,
    
    VT_FLOAT,
    VT_DOUBLE,
    
    VT_I8,
    VT_I16,
    VT_I32,
    VT_I64,
    
    VT_UI8,
    VT_UI16,
    VT_UI32,
    VT_UI64,
    
    VT_OBJ,
    VT_OBJ_PTR,
    
    VT_UNKNOWN,
};

class X_API XMetaVariantInfo
{
public:
    eMetaVariantType    m_eType;
    const XMetaClass*   m_pkObjClass;
    XMetaVariantInfo()
    : m_eType( VT_UNKNOWN )
    , m_pkObjClass( nullptr )
    {
    }
};

class X_API XMetaVariant
{
protected:
    XMetaVariantInfo            m_kVariantInfo;
public:
    const XMetaVariantInfo&     getVariantInfo() const { return m_kVariantInfo; }
};

template < typename T >
class XMetaVariantHelper;

template < typename T >
class X_API XMetaVariant_T
: public XMetaVariant
{
    friend class XMetaVariantHelper<T>;
protected:
    
    T   m_value;
    
public:
    XMetaVariant_T( const T& v )
    {
        XMetaVariantHelper<T>::build( m_kVariantInfo );
    }
    
    XVoid       setValue( const T& v ) { m_value = v; }
    const T&    getValue() const { return m_value; }
};

template < typename T >
class XMetaVariantTypeHelper
{
public:
    static eMetaVariantType   getType() { return VT_OBJ; }
};

template < typename T >
class XMetaVariantTypeHelper< T* >
{
public:
    static eMetaVariantType   getType() { return VT_OBJ_PTR; }
};

template < typename T >
class XMetaVariantHelper
{
public:
    static XVoid build( XMetaVariantInfo& kInfo )
    {
        kInfo.m_eType = VT_OBJ;
        kInfo.m_pkObjClass = &XMetaClassHelper<T>::getMetaClass();
    }
    
    static XMetaVariantInfo& getVariantInfo()
    {
        static XMetaVariantInfo k_ins;
        build( k_ins );
        return k_ins;
    }
};

template < typename T >
class XMetaVariantHelper< T* >
{
public:
    static XVoid build( XMetaVariantInfo& kInfo )
    {
        kInfo.m_eType = VT_OBJ_PTR;
        kInfo.m_pkObjClass = &XMetaClassHelper<T>::getMetaClass();
    }
    
    static XMetaVariantInfo& getVariantInfo()
    {
        static XMetaVariantInfo k_ins;
        build( k_ins );
        return k_ins;
    }
};


template <>
class XMetaVariantHelper< std::vector< XUInt32 > >
{
public:
    static XVoid build( XMetaVariantInfo& kInfo )
    {
        kInfo.m_eType = VT_OBJ;
    }
    
    static XMetaVariantInfo& getVariantInfo()
    {
        static XMetaVariantInfo k_ins;
        build( k_ins );
        return k_ins;
    }
};

template < typename T >
class XMetaVariantHelper< std::vector< T > >
{
public:
    static XVoid build( XMetaVariantInfo& kInfo )
    {
        kInfo.m_eType = VT_OBJ;
        kInfo.m_pkObjClass = &XMetaClassHelper< typename std::vector< T >::value_type >::getMetaClass();
    }
    
    static XMetaVariantInfo& getVariantInfo()
    {
        static XMetaVariantInfo k_ins;
        build( k_ins );
        return k_ins;
    }
};

template < typename T >
class XMetaVariantHelper< std::vector< T* > >
{
public:
    static XVoid build( XMetaVariantInfo& kInfo )
    {
        kInfo.m_eType = VT_OBJ_PTR;
        kInfo.m_pkObjClass = &XMetaClassHelper< typename std::remove_pointer< typename std::vector< T >::value_type >::type >::getMetaClass();
    }
    
    static XMetaVariantInfo& getVariantInfo()
    {
        static XMetaVariantInfo k_ins;
        build( k_ins );
        return k_ins;
    }
};

#define IMPLEMENT_META_VARIANT_TYPE_HELPER( T, t )  \
template <> \
class XMetaVariantTypeHelper< T >   \
{   \
public: \
static eMetaVariantType   getType() { return t; }   \
};

#define IMPLEMENT_META_VARIANT_HELPER( T )   \
template <> \
class XMetaVariantHelper< T >   \
{   \
public: \
    static XVoid build( XMetaVariantInfo& kInfo )   \
    {   \
        kInfo.m_eType = XMetaVariantTypeHelper<T>::getType();    \
    }   \
    static XMetaVariantInfo& getVariantInfo()   \
    {   \
        static XMetaVariantInfo k_ins;  \
        build( k_ins ); \
        return k_ins;   \
    }   \
};

#define IMPLEMENT_META_VARIANT( T, t )  \
    IMPLEMENT_META_VARIANT_TYPE_HELPER( T, t )  \
    IMPLEMENT_META_VARIANT_HELPER( T )   \
    typedef XMetaVariant_T< T >     XMetaVariant##T;

IMPLEMENT_META_VARIANT( XBool, VT_BOOL );

IMPLEMENT_META_VARIANT( XFloat, VT_FLOAT );
IMPLEMENT_META_VARIANT( XDouble, VT_DOUBLE );

IMPLEMENT_META_VARIANT( XInt8, VT_I8 );
IMPLEMENT_META_VARIANT( XInt16, VT_I16 );
IMPLEMENT_META_VARIANT( XInt32, VT_I32 );
IMPLEMENT_META_VARIANT( XInt64, VT_I64 );

IMPLEMENT_META_VARIANT( XUInt8, VT_UI8 );
IMPLEMENT_META_VARIANT( XUInt16, VT_UI16 );
IMPLEMENT_META_VARIANT( XUInt32, VT_UI32 );
IMPLEMENT_META_VARIANT( XUInt64, VT_UI64 );


X_NS_END

 */
#endif // __XMETAVARIANT_H__
