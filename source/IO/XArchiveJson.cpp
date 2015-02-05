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
#include "rapidjson/error/en.h"

X_NS_BEGIN

typedef std::vector< rapidjson::Value* > XVecJsonNodeStack;

rapidjson::Value* getJsonValue( XArchiveNodePtr stack, const std::string& name )
{
    X_RET_VAL_IF( !stack, nullptr );
    XVecJsonNodeStack* pkCurStack = (XVecJsonNodeStack*)stack;
    assert( pkCurStack );
    X_RET_VAL_IF( pkCurStack->empty(), nullptr );
    rapidjson::Value* pkCurValue = pkCurStack->back();
    assert( pkCurValue );
    rapidjson::Value::MemberIterator iter = pkCurValue->FindMember( name.c_str() );
    X_RET_VAL_IF( iter == pkCurValue->MemberEnd(), nullptr );
    return &iter->value;
}


//------------------------------------------------------------------------------
XInputArchiveJson::XInputArchiveJson()
: m_pkRootNode( nullptr )
, m_pkCurNode( nullptr )
{
    
}

//------------------------------------------------------------------------------
XInputArchiveJson::~XInputArchiveJson()
{
    rapidjson::Document* pkDocument = (rapidjson::Document*)m_pkRootNode;
    X_SAFE_DEL( pkDocument );
    m_pkRootNode = nullptr;
    
    XVecJsonNodeStack* pkStack = (XVecJsonNodeStack*)m_pkCurNode;
    X_SAFE_DEL( pkStack );
    m_pkCurNode = nullptr;
}

XRet XInputArchiveJson::load( XInputDataStream* pkStream )
{
    assert( pkStream );
    XString str = pkStream->getAsString();
    X_RET_VAL_IF( str.empty(), X_ERROR );
    return load( (const XVoid*)str.c_str(), str.size() );
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::load( const XVoid* pkData, XSize size )
{
    assert( pkData && size );
    
    rapidjson::Document* pkDocument = X_NEW rapidjson::Document;
    assert( pkDocument );
    pkDocument->Parse( (const XChar*)pkData );
    if ( pkDocument->HasParseError() )
    {
        X_LOG_ERROR( "failed to parse json : " << GetParseError_En(pkDocument->GetParseError())<< " pos : " << pkDocument->GetErrorOffset() );
        X_SAFE_DEL( pkDocument );
        return X_ERROR;
    }
    
    m_pkRootNode = (XArchiveNodePtr)pkDocument;
    
    m_pkCurNode = (XArchiveNodePtr)( X_NEW XVecJsonNodeStack );
    ((XVecJsonNodeStack*)m_pkCurNode)->push_back( pkDocument );
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XBool& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsBool(), X_ERROR );
    v = pkValue->GetBool();
    return X_SUCCESS;

}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XFloat& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsDouble(), X_ERROR );
    v = (XFloat)pkValue->GetDouble();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XDouble& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsDouble(), X_ERROR );
    v = pkValue->GetDouble();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XLong& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsInt(), X_ERROR );
    v = (XLong)pkValue->GetInt();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XULong& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsUint(), X_ERROR );
    v = (XULong)pkValue->GetUint();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt8& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsInt(), X_ERROR );
    v = (XInt8)pkValue->GetInt();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt16& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsInt(), X_ERROR );
    v = (XInt16)pkValue->GetInt();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt32& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsInt(), X_ERROR );
    v = (XInt32)pkValue->GetInt();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XInt64& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsInt64(), X_ERROR );
    v = pkValue->GetInt64();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt8& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsUint(), X_ERROR );
    v = (XUInt8)pkValue->GetUint();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt16& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsUint(), X_ERROR );
    v = (XUInt16)pkValue->GetUint();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt32& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsUint(), X_ERROR );
    v = (XUInt32)pkValue->GetUint();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XUInt64& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsUint64(), X_ERROR );
    v = pkValue->GetUint64();
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XString& v )
{
    rapidjson::Value* pkValue = getJsonValue( m_pkCurNode, name );
    X_RET_VAL_IF( !pkValue || !pkValue->IsString(), X_ERROR );
    v.assign( pkValue->GetString(), pkValue->GetStringLength() );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::read( const XString& name, XWString& v )
{
    XString str;
    if ( X_IS_SUCCESS( read( name, str ) ) )
    {
        v = XStringUtil::utf8ToWide( str );
        return X_SUCCESS;
    }
    
    return X_ERROR;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::readSectionBegin( const XString& name )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    XVecJsonNodeStack* pkCurStack = (XVecJsonNodeStack*)m_pkCurNode;
    assert( pkCurStack );
    X_RET_VAL_IF( pkCurStack->empty(), X_ERROR );
    rapidjson::Value* pkCurValue = pkCurStack->back();
    assert( pkCurValue );
    
    rapidjson::Value::MemberIterator iter = pkCurValue->FindMember( name.c_str() );
    if ( iter != pkCurValue->MemberEnd()
        && iter->value.IsObject() )
    {
        pkCurStack->push_back( &iter->value );
        return X_SUCCESS;
    }
    return X_ERROR;
}

//------------------------------------------------------------------------------
XRet XInputArchiveJson::readSectionEnd()
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    XVecJsonNodeStack* pkCurStack = (XVecJsonNodeStack*)m_pkCurNode;
    assert( pkCurStack );
    X_RET_VAL_IF( pkCurStack->size() < 2 , X_ERROR );
    pkCurStack->pop_back();
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
    if ( !pkWrite->IsComplete() )
    {
        pkWrite->EndObject();
    }
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