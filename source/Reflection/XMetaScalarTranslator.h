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

#ifndef __XMETASCALARTRANSLATOR_H__
#define __XMETASCALARTRANSLATOR_H__

#include "XMetaTranslator.h"
#include "XMetaField.h"
#include "XMetaType.h"

X_NS_BEGIN


template < typename T >
class XScalorTranslator_T
: public XScalorTranslator
{
    
public:
    
    virtual const XMetaType&        getMetaType() const { return XMetaTypeHelper<T>::getMetaType(); }
    
    virtual XBool                   equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        const T& src = kSrc.as<T>();
        const T& dest = kDest.as<T>();
        return src == dest;
    }
    
    virtual XVoid                   copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        const T& src = kSrc.as<T>();
        T& dest = kDest.as<T>();
        dest = src;
    }
    
    virtual XRet                    write( const XMetaFieldPointer& kPointer, XSerializer* pkSerializer ) const
    {
        const T& kV = kPointer.as<T>();
        (*pkSerializer) << kPointer.getField()->getName().c_str() << ": " << kV << " address: " << kPointer.getAddress();
        pkSerializer->end();
        return 1;
    }
};


template < typename T >
class TClassPtrTranslator
: public XScalorTranslator
{
    typedef typename std::remove_pointer<T>::type   type;
public:
    virtual const XMetaType&        getMetaType() const { return XMetaTypeHelper<T>::getMetaType(); }
    
    virtual XBool                   equals( const XMetaFieldPointer& kSrc, const XMetaFieldPointer& kDest ) const
    {
        const T& src = kSrc.as<T>();
        const T& dest = kDest.as<T>();
        //return *src == *dest;
    }
    
    virtual XVoid                   copy( XMetaFieldPointer& kDest, const XMetaFieldPointer& kSrc, XUInt32 uiFlag ) const
    {
        const T& src = kSrc.as<T>();
        T& dest = kDest.as<T>();
        //*dest = *src;
    }
    
    virtual XRet                    write( const XMetaFieldPointer& kPointer, XSerializer* pkSerializer ) const
    {
        if ( *(T**)kPointer.getAddress() == nullptr )
        {
            return 1;
        }
        assert( pkSerializer != nullptr );
        const XMetaClass* pkMetaClass = &XMetaClassHelper<type>::getMetaClass();
        assert( pkMetaClass != nullptr );
        
        if ( kPointer.getField() != nullptr )
        {
            (*pkSerializer) << kPointer.getField()->getName().c_str() << " address : " << kPointer.getAddress();
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
            
            XMetaFieldPointer kP( (XVoid*)kPointer.getObject(), *(T**)kPointer.getAddress(), pkField );
            pkTranslator->write( kP, pkSerializer );
        }
        
        pkSerializer->end();
        return 1;
    }
};



template < typename T >
class XTranslatorHelper<T*>
{
public:
    static const XMetaTranslator*    getTranslator()
    {
        static TClassPtrTranslator<T*> s_kIns;
        return &s_kIns;
    }
};

#define DECLARE_SCALOR_TRANSLATOR( t )  \
template <> \
class XTranslatorHelper< t >    \
{   \
public: \
    static XMetaTranslator*    getTranslator() \
    {   \
        static XScalorTranslator_T<t> s_kIns;    \
        return &s_kIns; \
    }   \
};


DECLARE_SCALOR_TRANSLATOR( XBool );

DECLARE_SCALOR_TRANSLATOR( XFloat );
DECLARE_SCALOR_TRANSLATOR( XDouble );

DECLARE_SCALOR_TRANSLATOR( XInt8 );
DECLARE_SCALOR_TRANSLATOR( XInt16 );
DECLARE_SCALOR_TRANSLATOR( XInt32 );
DECLARE_SCALOR_TRANSLATOR( XInt64 );

DECLARE_SCALOR_TRANSLATOR( XUInt8 );
DECLARE_SCALOR_TRANSLATOR( XUInt16 );
DECLARE_SCALOR_TRANSLATOR( XUInt32 );
DECLARE_SCALOR_TRANSLATOR( XUInt64 );

X_NS_END

#endif // __XMETASCALARTRANSLATOR_H__