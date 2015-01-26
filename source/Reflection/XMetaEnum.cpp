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

#include "XMetaEnum.h"
#include "Base/XStringUtil.h"

X_NS_BEGIN

//------------------------------------------------------------------------------
XMetaEnum::XMetaEnum( const XString& strName, TFunMetaEnumInit f )
: XMetaObject( strName )
, m_uiCrc32( XStringUtil::crc32( strName ) )
, m_pkFunInit( f )
{
    
}

//------------------------------------------------------------------------------
XRet XMetaEnum::addElement( const XString& strName, XUInt32 value )
{
    for ( auto& i : m_vecElements )
    {
        if ( i.strName == strName
            || i.uiValue == value )
        {
            return X_ERROR;
        }
    }
    
    m_vecElements.push_back( XMetaEnumElement( strName, value ) );
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XMetaEnum::getValueByName( const XString& strName, XUInt32& value ) const
{
    const_cast<XMetaEnum*>(this)->lazyInit();
    
    for ( auto& i : m_vecElements )
    {
        if ( i.strName == strName )
        {
            value = i.uiValue;
            return X_SUCCESS;
        }
    }
    return X_ERROR;
}

//------------------------------------------------------------------------------
XRet XMetaEnum::getNameByValue( XUInt32 value, XString& strName ) const
{
    const_cast<XMetaEnum*>(this)->lazyInit();
    
    for ( auto& i : m_vecElements )
    {
        if ( i.uiValue == value )
        {
            strName = i.strName;
            return X_SUCCESS;
        }
    }
    return X_ERROR;
}

X_NS_END

