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
    
    virtual const XMetaType&        getMetaType() const { return XMetaTypeHelper<T>::getMetaType(); }
    
    virtual XBool                   equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        return false;
    }
    
    virtual XVoid                   copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        
    }
    
    virtual XRet                    write( const XMetaFieldPointer& kPointer, XSerializer* pkSerializer ) const
    {
        assert( pkSerializer != nullptr );
        const XMetaClass* pkMetaClass = getMetaType().getMetaClass();
        assert( pkMetaClass != nullptr );
        
        if ( kPointer.getField() != nullptr )
        {
            (*pkSerializer) << kPointer.getField()->getName().c_str();
        }
        else
        {
            (*pkSerializer) << pkMetaClass->getName().c_str();
        }
        pkSerializer->end();
        
        const TMapMetaFields& mapFields = pkMetaClass->getAllFields();
        for ( auto iter = mapFields.begin(); iter != mapFields.end(); ++iter )
        {
            const XMetaField* pkField = iter->second;
            const XMetaTranslator* pkTranslator = pkField->getTranslator();
            assert( pkTranslator != nullptr );
            
            XMetaFieldPointer kP( (XVoid*)kPointer.getObject(), kPointer.getAddress(), pkField );
            pkTranslator->write( kP, pkSerializer );
        }
        
        pkSerializer->end();
        return 1;
    }
};

template < typename T >
class XTranslatorHelper
{
public:
    static const XMetaTranslator*    getTranslator()
    {
        static XClassTranslator_T<T> s_kIns;
        return &s_kIns;
    }
};

X_NS_END

#endif // __XMETATCLASSRANSLATOR_H__