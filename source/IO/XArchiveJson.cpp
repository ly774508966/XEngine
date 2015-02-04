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

#include "XArchiveJson.h"
#include "XMemDataStream.h"
#include "XFileDataStream.h"
#include "Base/XLogger.h"
#include "Base/XStringUtil.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/PrettyWriter.h>
#include <rapidjson/stringbuffer.h>

X_NS_BEGIN
//------------------------------------------------------------------------------
XInputArchiveJson::XInputArchiveJson()
: m_pkRootNode( nullptr )
, m_pkCurNode( nullptr )
{
    
}

//------------------------------------------------------------------------------
XInputArchiveJson::~XInputArchiveJson()
{
}

XRet XInputArchiveJson::load( XInputDataStream* pkStream )
{
    assert( pkStream );
    XBool bNeedDel = false;
    XSize size = 0;
    const XByte* pData = pkStream->getData( bNeedDel, &size );
    XRet ret = load( pData, size );
    if ( bNeedDel )
    {
        X_SAFE_DEL_ARR( pData );
    }
    return ret;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::load( const XVoid* pkData, XSize size )
{
    assert( pkData && size );
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XBool& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XFloat& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XDouble& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XLong& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XULong& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt8& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt16& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt32& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt64& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt8& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt16& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt32& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt64& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XString& v )
{
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XWString& v )
{
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::readSectionBegin( const XString& name )
{
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::readSectionEnd()
{
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XOutputArchiveJson::XOutputArchiveJson()
{
    rapidjson::StringBuffer* pkSB = X_NEW rapidjson::StringBuffer;
    rapidjson::Writer<rapidjson::StringBuffer>* pkWriter = X_NEW rapidjson::Writer<rapidjson::StringBuffer>( *pkSB );
    pkWriter->StartObject();
    m_pkRootNode = (XArchiveNodePtr)pkWriter;
    m_pkCurNode = m_pkRootNode;
}

//------------------------------------------------------------------------------
XOutputArchiveJson::~XOutputArchiveJson()
{
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    rapidjson::StringBuffer* pkSB = (rapidjson::StringBuffer*)pkWrite->getOutputStream();
    X_SAFE_DEL( pkSB );
    X_SAFE_DEL( pkWrite );
    m_pkRootNode = nullptr;
    m_pkCurNode = nullptr;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::save( const XString& name )
{
    X_RET_VAL_IF( name.empty(), X_ERROR );
    std::ofstream ofs( name.c_str() );
    XRet ret = save( ofs );
    ofs.close();
    return ret;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::save( std::ostream& s )
{
    X_RET_VAL_IF( !m_pkRootNode, X_ERROR );
    if ( !s.good() )
    {
        X_LOG_ERROR( "failed to save json archive! output stream is not good." );
        return X_ERROR;
    }
    
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->EndObject();
    rapidjson::StringBuffer* pkSB = (rapidjson::StringBuffer*)pkWrite->getOutputStream();
    assert( pkSB );
    
    s << pkSB->GetString() << std::endl;
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XBool v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Bool( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XFloat v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Double( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XDouble v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Double( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XLong v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Int64( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XULong v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Uint64( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XInt8 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Int( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XInt16 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Int( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XInt32 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Int( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XInt64 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Int64( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XUInt8 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Uint( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XUInt16 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Uint( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XUInt32 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Uint( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, XUInt64 v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->Uint64( v );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, const XString& v )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    pkWrite->String( v.c_str(), v.size() );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::write( const XString& name, const XWString& v )
{
    return write( name, XStringUtil::wideToUTF8( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::writeSectionBegin( const XString& name )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidjson::Writer<rapidjson::StringBuffer>* pkWrite = ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode);
    pkWrite->String( name.c_str(), name.size() );
    return pkWrite->StartObject() ? X_SUCCESS : X_ERROR;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveJson::writeSectionEnd()
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    return ((rapidjson::Writer<rapidjson::StringBuffer>*)m_pkCurNode)->EndObject() ? X_SUCCESS : X_ERROR;
}

X_NS_END