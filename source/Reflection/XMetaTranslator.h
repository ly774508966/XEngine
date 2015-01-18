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

#include <iostream>
#include "Base/XSmartPointer.h"

X_NS_BEGIN

enum eMetaTranslatorType
{
    SCALOR = 0,
    CLASS,
    SEQUENTIAL_CONTAINER,
    ASSOCIATIVE_CONTAINER,
    UNKNOWN
};

class XMetaFieldPointer;
class X_API XSerializer
{
public:
    template < typename T >
    XSerializer&   operator << ( const T& v )
    {
        std::cout << v;
        return *this;
    }
    
    template < typename T, XUInt32 N >
    XSerializer&   operator << ( T arr[N] )
    {
        for ( XUInt32 i = 0; i < N; ++i )
        {
            std::cout << "idx : " << i << "v : " << arr[i];
        }
        return *this;
    }
    
    XVoid   end()
    {
        std::cout << std::endl;
    }
};

class XMetaType;
class X_API XMetaTranslator
{
    
protected:

public:
    
    virtual const XMetaType&            getMetaType() const = 0;
    
    virtual XBool                       equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const = 0;
    virtual XVoid                       copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const = 0;
    
    virtual XRet                        write( const XMetaFieldPointer& kPointer, XSerializer* pkSerializer ) const = 0;
};


/*
    arithmetic, pointer, enum.
 */
class X_API XScalorTranslator
: public XMetaTranslator
{
};



class X_API XClassTranslator
: public XMetaTranslator
{
};


class X_API XContainerTranslator
: public XMetaTranslator
{
public:
    virtual XUInt32                     getLength( const XMetaFieldPointer& kPointer ) const = 0;
    virtual XVoid                       clear( XMetaFieldPointer& kPointer ) = 0;
};


class X_API XSequenceTranslator
: public XContainerTranslator
{
public:
    virtual const XMetaTranslator*      getItemTranslator() const = 0;
    
    virtual XVoid                       resize( XMetaFieldPointer& kPointer, XUInt32 uiLength ) = 0;
    virtual XVoid                       setItem( XMetaFieldPointer& kPointer, XUInt32 uiIdx, const XMetaFieldPointer& kValue ) = 0;
    virtual XMetaFieldPointer           getItem( const XMetaFieldPointer& kPointer, XUInt32 uiIdx ) = 0;
    virtual XVoid                       insert( XMetaFieldPointer& kPointer, XUInt32 uiIdx, const XMetaFieldPointer& kValue ) = 0;
    virtual XVoid                       remove( XMetaFieldPointer& kPointer, XUInt32 uiIdx ) = 0;
    virtual XVoid                       moveUp( XMetaFieldPointer& kPointer, XUInt32 uiIdx ) = 0;
    virtual XVoid                       moveDown( XMetaFieldPointer& kPointer, XUInt32 uiIdx ) = 0;
};


class X_API XAssociationTranslator
: public XContainerTranslator
{
public:
    
    virtual const XMetaTranslator*      getKeyTranslator() const = 0;
    virtual const XMetaTranslator*      getValueTranslator() const = 0;
    
    virtual XVoid                       setItem( XMetaFieldPointer& kPointer, const XMetaFieldPointer& kKey, const XMetaFieldPointer& kValue ) = 0;
    virtual XMetaFieldPointer           getItem( XMetaFieldPointer& kPointer, const XMetaFieldPointer& kKey ) = 0;
    virtual XVoid                       remove( XMetaFieldPointer& kPointer, const XMetaFieldPointer& kKey ) = 0;
};

template < typename T >
class XTranslatorHelper;

X_NS_END

#endif // __XMETATRANSLATOR_H__