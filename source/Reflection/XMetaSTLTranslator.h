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

#ifndef __XMETASTLTRANSLATOR_H__
#define __XMETASTLTRANSLATOR_H__

#include "XMetaTranslator.h"

X_NS_BEGIN

template < typename T >
class X_API XSequenceTranslator_Vector
: public XSequenceTranslator
{
    typedef typename T::value_type  value_type;
public:
    
    virtual XBool                   equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        return true;
    }
    
    virtual XVoid                   copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        
    }
    
    virtual XUInt32                 getLength( const XMetaFieldPointer& kPointer ) const
    {
        const T& kVector = kPointer.as<T>();
        return kVector.size();
    }
    
    virtual XVoid                   clear( XMetaFieldPointer& kPointer )
    {
        T& kVector = kPointer.as<T>();
        kVector.clear();
    }
    
    virtual const XMetaTranslator*  getItemTranslator() const { return XTranslatorHelper<value_type>::getTranslator(); }
    
    virtual XVoid                   resize( XMetaFieldPointer& kPointer, XUInt32 uiLength )
    {
        T& kVector = kPointer.as<T>();
        kVector.resize( uiLength );
    }
    
    virtual XVoid                   setItem( XMetaFieldPointer& kPointer, XUInt32 uiIdx, const XMetaFieldPointer& kValue )
    {
        T& kVector = kPointer.as<T>();
        kVector.resize( uiIdx );
        
        XMetaFieldPointer kDest( (XVoid*)&kVector[uiIdx], kPointer.getField(), kPointer.getObject() );
        getItemTranslator()->copy( kDest, kValue, 0 );
    }
    
    virtual XMetaFieldPointer       getItem( const XMetaFieldPointer& kPointer, XUInt32 uiIdx )
    {
        const T& kVector = kPointer.as<T>();
        assert( uiIdx < kVector.size() );
        return XMetaFieldPointer( (XVoid*)&kVector[uiIdx], kPointer.getField(), kPointer.getObject() );
    }
    
    virtual XVoid                   insert( XMetaFieldPointer& kPointer, XUInt32 uiIdx, const XMetaFieldPointer& kValue )
    {
        T& kVector = kPointer.as<T>();
        kVector.insert( kVector.begin() + uiIdx, kValue.as<value_type>() );
    }
    
    virtual XVoid                   remove( XMetaFieldPointer& kPointer, XUInt32 uiIdx )
    {
        T& kVector = kPointer.as<T>();
        kVector.erase( kVector.begin() + uiIdx );
    }
    
    virtual XVoid                   moveUp( XMetaFieldPointer& kPointer, XUInt32 uiIdx )
    {
        
    }
    
    virtual XVoid                   moveDown( XMetaFieldPointer& kPointer, XUInt32 uiIdx )
    {
        
    }
};

//------------------------------------------------------------------------------
template < typename T >
class XTranslatorHelper< std::vector< T > >
{
public:
    static const XMetaTranslator*   getTranslator()
    {
        static XSequenceTranslator_Vector< std::vector< T >  > s_kIns;
        return &s_kIns;
    }
    
};

X_NS_END

#endif // __XMETASTLTRANSLATOR_H__