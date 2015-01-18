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

#include "XMetaClass.h"
#include "XMetaField.h"
#include "XMetaMethod.h"

X_NS_BEGIN

XMetaClass::XMetaClass( const XString& strName, XUInt32 size, TFunMetaClassInit fun_fields, TFunMetaClassInit fun_methods )
: XMetaObject( strName )
, m_uiSize( size )
, m_pkFunInitFields( fun_fields )
, m_pkFunInitMethods( fun_methods )
, m_bFieldsInited( false )
, m_bMethodsInited( false )
{
}

XRet XMetaClass::addBaseClass( const XMetaClass* pkBase )
{
    for ( auto iter = m_vecBaseClasses.begin();
         iter != m_vecBaseClasses.end(); ++iter )
    {
        if ( (*iter) == pkBase )
        {
            return RET_BASE_CLASS_ALREADY_EXIST;
        }
    }
    
    m_vecBaseClasses.push_back( pkBase );
    
    return X_SUCCESS;
}

XBool XMetaClass::isKindOf( const XString& strTypeName ) const
{
    X_RET_VAL_IF( strTypeName.empty(), false );
    
    X_RET_VAL_IF( m_strName == strTypeName, true );
    
    for ( auto iter = m_vecBaseClasses.begin();
         iter != m_vecBaseClasses.end(); ++iter )
    {
        if ( (*iter)->isKindOf( strTypeName ) )
        {
            return true;
        }
    }
    
    return false;
}

const XMetaField* XMetaClass::getFieldByName( const XString& strName ) const
{
    const_cast<XMetaClass*>(this)->lazyInitFields();
    
    auto iter = m_mapFields.find( strName );
    if ( iter != m_mapFields.end() )
    {
        return iter->second;
    }
    
    return nullptr;
}

const TVecMetaMethods* XMetaClass::getMethodsByName( const XString& strName ) const
{
    const_cast<XMetaClass*>(this)->lazyInitMethods();
    
    auto iter = m_mapMethods.find( strName );
    if ( iter != m_mapMethods.end() )
    {
        return &iter->second;
    }
    
    return nullptr;
}

X_NS_END