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

#ifndef __XMETATCLASSRANSLATOR_H__
#define __XMETATCLASSRANSLATOR_H__

#include "XMetaTranslator.h"

X_NS_BEGIN

template < typename T >
class XClassTranslator_T
: public XClassTranslator
{
public:
    virtual const XMetaClass*           getMetaClass() const { return &T::ms_kMetaClass; }
    
    virtual XBool                       equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        return false;
    }
    
    virtual XVoid                       copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        
    }
};

template < typename T >
class XTranslatorHelper
{
public:
    static const XMetaTranslator*    getTranslator()
    {
        assert( std::is_class<T>::value );
        static XClassTranslator_T<T> s_kIns;
        return &s_kIns;
    }
};

X_NS_END

#endif // __XMETATCLASSRANSLATOR_H__