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

#ifndef __XMETATRANSLATOR_H__
#define __XMETATRANSLATOR_H__

X_NS_BEGIN

#include "Base/XPreDef.h"

template < typename T >
class XMetaTranslatorHelper;

class XMetaTranslator;
template < typename T >
X_FORCEINLINE const XMetaTranslator* getMetaTranslator()
{
    return XMetaTranslatorHelper< typename std::remove_cv<T>::type >::getTranslator();
}


//------------------------------------------------------------------------------
enum class XMetaTranslatorType
{
	PRIMITIVE,
	POINTER,
	CLASS,
	SEQUENTIAL_CONTAINER,
	ASSOCIATIVE_CONTAINER,
	UNKNOWN
};

class X_API XMetaTranslator
{
public:

	virtual ~XMetaTranslator() {}
    
    virtual XMetaTranslatorType         getTranslatorType() const = 0;
    virtual XSize                       getMemSize() const = 0;
    virtual XVoid*                      newObj() const = 0;
    virtual XVoid                       delObj( XVoid* pAddress ) const = 0;
    virtual XVoid                       construct( XVoid* pAddress ) const = 0;
    virtual XVoid                       destruct( XVoid* pAddress ) const = 0;
    virtual XBool                       equals( const XVoid* pA, const XVoid* pB ) const = 0;
    virtual XVoid                       assign( XVoid* pDest, const XVoid* pSrc, XUInt32 uiFlag ) const = 0;
    
public:
    template < typename T >
    static XSize                        defaultGetMemSize() { return sizeof(T); }
    
    template < typename T >
    static XVoid*                       defaultNewObj() { return X_NEW T; }
    
    template < typename T >
    static XVoid                        defaultDelObj( XVoid* pAddress ) { T* p = (T*)pAddress; X_SAFE_DEL(p); }
    
    template < typename T >
    static XVoid                        defaultConstruct( XVoid* pAddress ) { assert( pAddress ); X_NEW( pAddress ) T; }
    
    template < typename T >
    static XVoid                        defaultDestruct( XVoid* pAddress ) { assert( pAddress ); ( (T*)pAddress )->~T(); }
};


//------------------------------------------------------------------------------
enum class XMetaPrimitiveType
{
    BOOL,
    
    FLOAT,
    DOUBLE,
    
    LONG,
    ULONG,
    
    I8,
    I16,
    I32,
    I64,
    
    UI8,
    UI16,
    UI32,
    UI64,
    
    STRING,
    WSTRING,
};
class X_API XMetaPrimitiveTranslator
: public XMetaTranslator
{
public:
	virtual XMetaTranslatorType         getTranslatorType() const { return XMetaTranslatorType::PRIMITIVE; }
    
	virtual XMetaPrimitiveType          getPrimitiveType() const = 0;
};


//------------------------------------------------------------------------------
class X_API XMetaPointerTranslator
	: public XMetaTranslator
{
public:
	virtual XMetaTranslatorType         getTranslatorType() const override { return XMetaTranslatorType::POINTER; }
	virtual const XMetaTranslator*      getTargetTranslator() const = 0;
};

//------------------------------------------------------------------------------
class XMetaClass;
class X_API XMetaClassTranslator
	: public XMetaTranslator
{
public:
	virtual XMetaTranslatorType         getTranslatorType() const override { return XMetaTranslatorType::CLASS; }
	virtual const XMetaClass*           getMetaClass() const = 0;
};


//------------------------------------------------------------------------------
class X_API XMetaSequenceTranslator
: public XMetaTranslator
{
public:
    
	virtual XMetaTranslatorType         getTranslatorType() const override { return XMetaTranslatorType::SEQUENTIAL_CONTAINER; }
    
    virtual const XMetaTranslator*      getItemTranslator() const = 0;

    virtual XSize                       getSize( const XVoid* pAddress ) const = 0;
    virtual XVoid                       clear( XVoid* pAddress ) const = 0;
    virtual XVoid                       resize( XVoid* pAddress, XSize uiSize ) const = 0;
    virtual XVoid                       setItem( XVoid* pAddress, XSize uiIdx, const XVoid* pValue ) const = 0;
    virtual const XVoid*                getItem( const XVoid* pAddress, XSize uiIdx ) const = 0;
    virtual XVoid                       insert( XVoid* pAddress, XSize uiIdx, const XVoid* pValue ) const = 0;
    virtual XVoid                       remove( XVoid* pAddress, XSize uiIdx ) const = 0;
    virtual XVoid                       moveUp( XVoid* pAddress, XSize uiIdx ) const = 0;
    virtual XVoid                       moveDown( XVoid* pAddress, XSize uiIdx ) const = 0;
};


//------------------------------------------------------------------------------
class X_API XMetaAssociationTranslator
: public XMetaTranslator
{
public:
    
	virtual XMetaTranslatorType         getTranslatorType() const override { return XMetaTranslatorType::ASSOCIATIVE_CONTAINER; }

    virtual XSize                       getSize( const XVoid* pAddress ) const = 0;
    virtual XVoid                       clear( XVoid* pAddress ) const = 0;

    virtual const XMetaTranslator*      getKeyTranslator() const = 0;
    virtual const XMetaTranslator*      getValueTranslator() const = 0;

    virtual XVoid                       getAllItems( const XVoid* pAddress, std::vector<const XVoid*>& allKeys, std::vector<const XVoid*>& allItems ) const = 0;
    virtual XVoid                       setItem( XVoid* pAddress, const XVoid* pKey, const XVoid* pValue ) const = 0;
    virtual const XVoid*                getItem( const XVoid* pAddress, const XVoid* pKey ) const = 0;
    virtual XVoid                       remove( XVoid* pAddress, const XVoid* pKey ) const = 0;
};

X_NS_END

#endif // __XMETATRANSLATOR_H__