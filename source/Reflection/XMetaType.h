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

#ifndef __XMETATYPE_H__
#define __XMETATYPE_H__

#include "Base/XPreDef.h"

X_NS_BEGIN

template < typename T >
class XMetaClassHelper;

class X_API XMetaType
{
protected:
    
    XUInt32                 m_type;
    const XMetaClass*       m_pkObjClass;
    
public:
    enum
    {
        // inner use.
        
        MT_BOOL,
        
        MT_FLOAT,
        MT_DOUBLE,  // double or long double.
        
        MT_LONG,
        MT_ULONG,
        
        MT_I8,
        MT_I16,
        MT_I32,
        MT_I64,
        
        MT_UI8,
        MT_UI16,
        MT_UI32,
        MT_UI64,
        
        MT_STRING,
        MT_WSTRING,
        
        MT_OBJ,
        MT_OBJ_PTR,
        
        MT_FUN,
        
        MT_UNKNOWN,
    };
    
    XMetaType( XUInt32 t, const XMetaClass* pkMetaClass )
    : m_type( t )
    , m_pkObjClass( pkMetaClass )
    {
        if ( t == MT_OBJ || t == MT_OBJ_PTR )
        {
            assert( pkMetaClass != nullptr );
        }
    }
    
    XUInt32                 getType() const { return m_type; }
    const XMetaClass*       getMetaClass() const { return m_pkObjClass; }
};

template < typename T >
class XMetaTypeHelper
{
public:
    static const XMetaType& getMetaType()
    {
        static XMetaType s_kMetaType( XMetaType::MT_OBJ, &XMetaClassHelper<T>::getMetaClass() );
        return s_kMetaType;
    }
};


template < typename T >
class XMetaTypeHelper< T* >
{
public:
    static const XMetaType& getMetaType()
    {
        static XMetaType s_kMetaType( XMetaType::MT_OBJ_PTR, &XMetaClassHelper<T>::getMetaClass() );
        return s_kMetaType;
    }
};


template < typename T >
class XMetaTypeHelper< T& >
{
public:
    static const XMetaType& getMetaType()
    {
        static XMetaType s_kMetaType( XMetaType::MT_OBJ_PTR, &XMetaClassHelper<T>::getMetaClass() );
        return s_kMetaType;
    }
};


template < typename T >
class XMetaTypeHelper< std::vector< T > >
{
public:
    static const XMetaType& getMetaType()
    {
        static XMetaType s_kMetaType( XMetaTypeHelper<T>::getMetaType().getType(), XMetaTypeHelper<T>::getMetaType().getMetaClass() );
        return s_kMetaType;
    }
};

template < typename T >
class XMetaTypeHelper< std::vector< T* > >
{
public:
    
    static const XMetaType& getMetaType()
    {
        static XMetaType s_kMetaType( XMetaTypeHelper<T*>::getMetaType().getType(), XMetaTypeHelper<T>::getMetaType().getMetaClass() );
        return s_kMetaType;
    }
};


#define X_IMPLEMENT_META_TYPE( T, t )  \
template <> \
class XMetaTypeHelper< T >  \
{   \
public: \
static const XMetaType& getMetaType()   \
{   \
static XMetaType s_kMetaType( XMetaType::t, nullptr ); \
return s_kMetaType; \
}   \
};

X_IMPLEMENT_META_TYPE( XBool, MT_BOOL );
X_IMPLEMENT_META_TYPE( XFloat, MT_FLOAT );
X_IMPLEMENT_META_TYPE( XDouble, MT_DOUBLE );
X_IMPLEMENT_META_TYPE( XLongDouble, MT_DOUBLE );
X_IMPLEMENT_META_TYPE( XLong, MT_LONG );
X_IMPLEMENT_META_TYPE( XULong, MT_ULONG );
X_IMPLEMENT_META_TYPE( XChar, MT_I8 );
X_IMPLEMENT_META_TYPE( XSChar, MT_I8 );
X_IMPLEMENT_META_TYPE( XInt16, MT_I16 );
X_IMPLEMENT_META_TYPE( XInt32, MT_I32 );
X_IMPLEMENT_META_TYPE( XInt64, MT_I64 );
X_IMPLEMENT_META_TYPE( XUInt8, MT_UI8 );
X_IMPLEMENT_META_TYPE( XUInt16, MT_UI16 );
X_IMPLEMENT_META_TYPE( XUInt32, MT_UI32 );
X_IMPLEMENT_META_TYPE( XUInt64, MT_UI64 );
X_IMPLEMENT_META_TYPE( XString, MT_STRING );
X_IMPLEMENT_META_TYPE( XWString, MT_WSTRING );

X_NS_END

#endif // __XMETATYPE_H__
