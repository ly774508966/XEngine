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

#include "XArchiveXML.h"
#include "XMemDataStream.h"
#include "XFileDataStream.h"
#include "Base/XLogger.h"
#include "Base/XStringUtil.h"
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

X_NS_BEGIN

//------------------------------------------------------------------------------
XInputArchiveXML::XInputArchiveXML()
: m_pkRootNode( nullptr )
, m_pkCurNode( nullptr )
{
    
}

//------------------------------------------------------------------------------
XInputArchiveXML::~XInputArchiveXML()
{
    rapidxml::xml_document<>* pkDoc = (rapidxml::xml_document<>*)m_pkRootNode;
    X_SAFE_DEL( pkDoc );
    m_pkCurNode = nullptr;
}

XRet XInputArchiveXML::load( XInputDataStream* pkStream )
{
    assert( pkStream );
    rapidxml::xml_document<>* pkDoc = nullptr;
    XChar* pData = nullptr;
    try
    {
        pkDoc = X_NEW rapidxml::xml_document<>;
        XSize size = pkStream->getSize();
        pData = pkDoc->allocate_string( nullptr, size + 1 );
        size = pkStream->read( pData, size );
        pData[size] = 0;
        pkDoc->parse< rapidxml::parse_default >( pData );
        
        m_pkRootNode = (XArchiveNodePtr)pkDoc;
        m_pkCurNode = m_pkRootNode;
    }
    catch( const rapidxml::parse_error& e )
    {
        X_SAFE_DEL( pkDoc );
        X_LOG_ERROR( "failed to parse xml : " << e.what() << " pos : " << (XSize)( e.where<XChar>() - (XChar*)pData ) );
        return X_ERROR;
    }
    catch( const std::bad_alloc& e )
    {
        X_SAFE_DEL( pkDoc );
        X_LOG_ERROR( "failed to parse xml : " << e.what() );
        return X_ERROR;
    }
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::load( const XVoid* pkData, XSize size )
{
    assert( pkData && size );
    XMemoryInputDataStream kMIDS( pkData, size );
    return load( &kMIDS );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XBool& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XFloat& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XDouble& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XLong& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XULong& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XInt8& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XInt16& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XInt32& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XInt64& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XUInt8& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XUInt16& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XUInt32& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XUInt64& v )
{
    XString str;
    X_RET_VAL_IF( !X_IS_SUCCESS( read( name, str ) ), X_ERROR );
    return XStringUtil::fromString( str, v );
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XString& v )
{
    X_RET_VAL_IF( !m_pkCurNode || name.empty(), X_ERROR );
    rapidxml::xml_attribute<>* pkAttribute = ( (rapidxml::xml_document<>*)m_pkCurNode )->first_attribute( name.c_str(), name.size() );
    X_RET_VAL_IF( !pkAttribute, X_ERROR );
    v.assign( pkAttribute->value(), pkAttribute->value_size() );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::read( const XString& name, XWString& v )
{
    X_RET_VAL_IF( !m_pkCurNode || name.empty(), X_ERROR );
    rapidxml::xml_attribute<>* pkAttribute = ( (rapidxml::xml_document<>*)m_pkCurNode )->first_attribute( name.c_str(), name.size() );
    X_RET_VAL_IF( !pkAttribute, X_ERROR );
    v = XStringUtil::utf8ToWide( pkAttribute->value(), pkAttribute->value_size() );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::readSectionBegin( const XString& name )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidxml::xml_node<>* pkNode = ( (rapidxml::xml_document<>*)m_pkCurNode )->first_node( name.c_str(), name.size() );
    X_RET_VAL_IF( !pkNode, X_ERROR );
    m_pkCurNode = (XArchiveNodePtr)pkNode;
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XInputArchiveXML::readSectionEnd()
{
    X_RET_VAL_IF( !m_pkCurNode || m_pkCurNode == m_pkRootNode, X_ERROR );
    rapidxml::xml_node<>* pkParent = ( (rapidxml::xml_node<>*)m_pkCurNode )->parent();
    X_RET_VAL_IF( !pkParent, X_ERROR );
    m_pkCurNode = (XArchiveNodePtr)pkParent;
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XOutputArchiveXML::XOutputArchiveXML()
{
    rapidxml::xml_document<>* pkDoc = X_NEW rapidxml::xml_document<>;
    rapidxml::xml_node<>* pkDecl = pkDoc->allocate_node( rapidxml::node_declaration );
    pkDecl->append_attribute( pkDoc->allocate_attribute( "version", "1.0" ) );
    pkDecl->append_attribute( pkDoc->allocate_attribute( "encoding", "utf-8" ) );
    pkDoc->append_node( pkDecl );
    
    m_pkRootNode = (XArchiveNodePtr)pkDoc;
    m_pkCurNode = m_pkRootNode;
}

//------------------------------------------------------------------------------
XOutputArchiveXML::~XOutputArchiveXML()
{
    rapidxml::xml_document<>* pkDoc = (rapidxml::xml_document<>*)m_pkRootNode;
    X_SAFE_DEL( pkDoc );
    m_pkCurNode = nullptr;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::save( const XString& name )
{
    std::ofstream ofs( name.c_str() );
    XRet rt = save( ofs );
    ofs.close();
    return rt;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::save( std::ostream& s )
{
    X_RET_VAL_IF( !m_pkRootNode, X_ERROR );
    if ( !s.good() )
    {
        X_LOG_ERROR( "failed to save xml archive! output stream is not good." );
        return X_ERROR;
    }
    
    if ( m_pkCurNode != m_pkRootNode )
    {
        X_LOG_ERROR( "failed to save xml archive! Did you call 'writeSectionBegin' and 'writeSectionEnd' pair function correctly?" );
        return X_ERROR;
    }
    s << *(rapidxml::xml_node<>*)m_pkRootNode;
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XBool v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XFloat v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XDouble v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XLong v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XULong v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XInt8 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XInt16 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XInt32 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XInt64 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XUInt8 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XUInt16 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XUInt32 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, XUInt64 v )
{
    return write( name, XStringUtil::toString( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, const XString& v )
{
    X_RET_VAL_IF( !m_pkCurNode || v.empty(), X_ERROR );
    rapidxml::xml_attribute<>* pkAttribute = ( (rapidxml::xml_document<>*)m_pkRootNode )->allocate_attribute(
    ( (rapidxml::xml_document<>*)m_pkRootNode )->allocate_string( name.c_str(), name.size() ),
    ( (rapidxml::xml_document<>*)m_pkRootNode )->allocate_string( v.c_str(), v.size() ),                                                                                                     name.size(), v.size() );
    X_RET_VAL_IF( !pkAttribute, X_ERROR );
    ( (rapidxml::xml_node<>*)m_pkCurNode )->append_attribute( pkAttribute );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::write( const XString& name, const XWString& v )
{
    return write( name, XStringUtil::wideToUTF8( v ) );
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::writeSectionBegin( const XString& name )
{
    X_RET_VAL_IF( !m_pkCurNode, X_ERROR );
    rapidxml::xml_node<>* pkNode = ( (rapidxml::xml_document<>*)m_pkRootNode )->allocate_node(
        rapidxml::node_element, ( (rapidxml::xml_document<>*)m_pkRootNode )->allocate_string( name.c_str(), name.size() ),
        0,
        name.size() );
    X_RET_VAL_IF( !pkNode, X_ERROR );
    ( (rapidxml::xml_node<>*)m_pkCurNode )->append_node( pkNode );
    m_pkCurNode = (XArchiveNodePtr)pkNode;
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XRet XOutputArchiveXML::writeSectionEnd()
{
    X_RET_VAL_IF( !m_pkCurNode || m_pkCurNode == m_pkRootNode, X_ERROR );
    rapidxml::xml_node<>* pkParent = ( (rapidxml::xml_node<>*)m_pkCurNode )->parent();
    X_RET_VAL_IF( !pkParent, X_ERROR );
    m_pkCurNode = (XArchiveNodePtr)pkParent;
    return X_SUCCESS;
}

X_NS_END