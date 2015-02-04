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

#ifndef __XMETATPOINTERTRANSLATOR_H__
#define __XMETATPOINTERTRANSLATOR_H__

#include "XMetaTranslator.h"

X_NS_BEGIN


//------------------------------------------------------------------------------
template < typename T >
class TPointerTranslator
: public XMetaPointerTranslator
{
    typedef typename std::remove_pointer<T>::type TTargetType;
public:
    
    virtual XVoid*                      newObj() const override { return XMetaTranslator::defaultNewObj<T>(); }
    virtual XVoid                       delObj( XVoid* pAddress ) const override { XMetaTranslator::defaultDelObj<T>( pAddress ); }
    virtual XSize                       getMemSize() const override { return XMetaTranslator::defaultGetMemSize<T>(); }
    virtual XVoid                       construct( XVoid* pAddress ) const override { XMetaTranslator::defaultConstruct<T>( pAddress ); }
    virtual XVoid                       destruct( XVoid* pAddress ) const override { XMetaTranslator::defaultDestruct<T>( pAddress ); }
    
    virtual const XMetaTranslator*      getTargetTranslator() const
    {
        return getMetaTranslator< TTargetType >();
    }
    
    virtual XBool                       equals( const XVoid* pA, const XVoid* pB ) const override
    {
        return getTargetTranslator()->equals( pA, pB );
    }
    
    virtual XVoid                       assign( XVoid* pDest, const XVoid* pSrc, XUInt32 uiFlag ) const override
    {
        return getTargetTranslator()->assign( pDest, pSrc, uiFlag );
    }
};


//------------------------------------------------------------------------------
template < typename T >
class XMetaTranslatorHelper<T*>
{
public:
    static const XMetaTranslator*    getTranslator()
    {
        static_assert( std::is_pointer<T*>::value, "must pointer type!" );
        static TPointerTranslator<T*> s_kIns;
        return &s_kIns;
    }
};

X_NS_END

#endif // __XMETATPOINTERTRANSLATOR_H__