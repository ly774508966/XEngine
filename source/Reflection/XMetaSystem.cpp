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

#include "XMetaSystem.h"
#include "XMetaClass.h"
#include "XMetaEnum.h"
#include "Base/XLogger.h"

X_NS_BEGIN

//------------------------------------------------------------------------------
XRet XMetaSystem::registerMetaClass( const XMetaClass* pkMetaClass )
{
    assert( pkMetaClass );
	auto iter = m_mapAllMetaClasses.find( pkMetaClass->getCrc32() );
	if ( iter != m_mapAllMetaClasses.end() )
	{
		X_LOG_ERROR( "failed to register meta class[ " << pkMetaClass->getName() << " ]. "
			"crc32[ " << iter->second->getCrc32() << " ] of meta class[ " << iter->second->getName() << " ] already exist!" );
		return X_ERROR;
	}
    return m_mapAllMetaClasses.insert( std::make_pair( pkMetaClass->getCrc32(), pkMetaClass ) ).second ? X_SUCCESS : X_ERROR;
}

//------------------------------------------------------------------------------
X_FORCEINLINE const XMetaClass* XMetaSystem::getMetaClass( const XString& strName ) const
{
	return getMetaClass( XStringUtil::crc32( strName ) );
}

//------------------------------------------------------------------------------
const XMetaClass* XMetaSystem::getMetaClass( XUInt32 crc32 ) const
{
	auto iter = m_mapAllMetaClasses.find( crc32 );
	if( iter != m_mapAllMetaClasses.end() )
	{
		return iter->second;
	}

	return nullptr;
}

//------------------------------------------------------------------------------
XRet XMetaSystem::registerMetaEnum( const XMetaEnum* pkMetaEnum )
{
    assert( pkMetaEnum );
    auto iter = m_mapAllMetaEnums.find( pkMetaEnum->getCrc32() );
    if ( iter != m_mapAllMetaEnums.end() )
    {
        X_LOG_ERROR( "failed to register meta enum[ " << pkMetaEnum->getName() << " ]. "
                    "crc32[ " << iter->second->getCrc32() << " ] of meta enum[ " << iter->second->getName() << " ] already exist!" );
        return X_ERROR;
    }
    return m_mapAllMetaEnums.insert( std::make_pair( pkMetaEnum->getCrc32(), pkMetaEnum ) ).second ? X_SUCCESS : X_ERROR;
}

//------------------------------------------------------------------------------
X_FORCEINLINE const XMetaEnum* XMetaSystem::getMetaEnum( const XString& strName ) const
{
    return getMetaEnum( XStringUtil::crc32( strName ) );
}

//------------------------------------------------------------------------------
const XMetaEnum* XMetaSystem::getMetaEnum( XUInt32 crc32 ) const
{
    auto iter = m_mapAllMetaEnums.find( crc32 );
    if( iter != m_mapAllMetaEnums.end() )
    {
        return iter->second;
    }
    
    return nullptr;
}


X_NS_END
