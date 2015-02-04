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

#include "XMetaObjectSerializer.h"
#include "XMetaObject.h"
#include "XMetaClass.h"
#include "XMetaField.h"
#include "XMetaTranslator.h"
#include "XMetaPrimitiveTranslator.h"
#include "IO/XArchive.h"
#include "Base/XLogger.h"

X_NS_BEGIN


class XMetaObjectSerializerImpl
{
public:
    
    static const XUInt32    ms_uiVersion = 1;
    
    static XRet serialize( const XMetaObject* pkObject, XOutputArchive* pkArchive )
    {
        assert( pkObject && pkObject->getMetaClass() && pkArchive );
        
        do
        {
            ((XMetaObject*)pkObject)->preSerialize();
            
            if ( !X_IS_SUCCESS( pkArchive->writeSectionBegin( "XEngineArchive" ) ) ) break;
            {
                if ( !X_IS_SUCCESS( pkArchive->write( "Version" , ms_uiVersion ) ) ) break;
                
                pkArchive->writeSectionBegin( "Object" );
                pkArchive->write( "Class", pkObject->getMetaClass()->getName() );
                
                if ( !X_IS_SUCCESS( serializeMetaClass( (const XVoid*)pkObject, pkObject->getMetaClass(), pkArchive ) ) ) break;
                
                pkArchive->writeSectionEnd();
                
                if ( !X_IS_SUCCESS( pkArchive->writeSectionEnd() ) ) break;
            }
            
            ((XMetaObject*)pkObject)->postSerialize();
            
            return X_SUCCESS;
        }
        while ( 0 );
        
        return X_ERROR;
    }
    
    static XMetaObject* deserialize( XInputArchive* pkArchive )
    {
        assert( pkArchive );
        
        XMetaObject* pkObj = nullptr;
        do
        {
            if ( !X_IS_SUCCESS( pkArchive->readSectionBegin( "XEngineArchive" ) ) ) break;
            {
                XUInt32 uiVersion;
                if ( !X_IS_SUCCESS( pkArchive->read( "Version" , uiVersion ) ) ) break;
                
                if ( !X_IS_SUCCESS( pkArchive->readSectionBegin( "Object" ) ) ) break;
                {
                    XString strClass;
                    if ( !X_IS_SUCCESS( pkArchive->read( "Class", strClass ) ) ) break;
                    
                    if ( strClass.empty() ) break;
                    
                    const XMetaClass* pkMC = XMetaSystem::getIns().getMetaClass( strClass );
                    if ( !pkMC )
                        break;
                    
                    pkObj = pkMC->createObject();
                    if ( !pkObj )
                        break;
                    
                    pkObj->preDeserialize();
                    
                    if ( !X_IS_SUCCESS( deserializeMetaClass( (XVoid*)pkObj, pkMC, pkArchive ) ) )
                        break;
                    
                    pkObj->postDeserialize();
                    
                    if ( !X_IS_SUCCESS( pkArchive->readSectionEnd() ) ) break;
                }
                
                if ( !X_IS_SUCCESS( pkArchive->readSectionEnd() ) ) break;
            }
            
            return pkObj;
        }
        while (0);
        
        X_SAFE_DEL( pkObj );
        
        return nullptr;
    }
    
    
protected:
    static XRet serializeMetaClass( const XVoid* pAddress, const XMetaClass* pkMC, XOutputArchive* pkArchive )
    {
        assert( pAddress && pkMC && pkArchive );
        
        const TMapMetaFields& mapFields = pkMC->getAllFields();
        for ( auto& iter : mapFields )
        {
            const XVoid* pFieldAddress = (const XVoid*)( (const XChar*)pAddress + iter.second->getOffset() );
            serializeMetaTranslator( pFieldAddress, iter.second->getName(), iter.second->getTranslator(), pkArchive );
        }
        
        return X_SUCCESS;
    }
    static XRet serializeMetaTranslator( const XVoid* pAddress, const XString& strName, const XMetaTranslator* pkMT, XOutputArchive* pkArchive )
    {
        assert( pAddress && !strName.empty() && pkMT && pkArchive );
        
        switch ( pkMT->getTranslatorType() )
        {
            case XMetaTranslatorType::PRIMITIVE:
            {
#define X_IMPLEMENT_SERIALIZE_PRI_TRANSLATOR( pt, t )  \
    case pt: pkArchive->write( strName, *(t*)pAddress ); break;
                const XMetaPrimitiveTranslator* pkPTranslator = (const XMetaPrimitiveTranslator*)pkMT;
                assert( pkPTranslator );
                switch ( pkPTranslator->getPrimitiveType() )
                {
                    X_META_PRIMITIVE_TYPE_TRAVERSAL( X_IMPLEMENT_SERIALIZE_PRI_TRANSLATOR );
                    default: assert( 0 ); break;
                }
#undef X_IMPLEMENT_SERIALIZE_PRI_TRANSLATOR
            }
                break;
            case XMetaTranslatorType::POINTER:
            {
                const XMetaPointerTranslator* pkPTranslator = (const XMetaPointerTranslator*)pkMT;
                assert( pkPTranslator );
                const XMetaTranslator* pkTargetTranslator = pkPTranslator->getTargetTranslator();
                assert( pkTargetTranslator );
                XVoid* pkTargetAddress = *(XVoid**)pAddress;
                if ( pkTargetAddress != nullptr )
                {
                    serializeMetaTranslator( pkTargetAddress, strName, pkTargetTranslator, pkArchive );
                }
            }
                break;
            case XMetaTranslatorType::CLASS:
            {
                const XMetaClassTranslator* pkCTranslator = (const XMetaClassTranslator*)pkMT;
                assert( pkCTranslator );
                pkArchive->writeSectionBegin( strName );
                serializeMetaClass( pAddress, pkCTranslator->getMetaClass(), pkArchive );
                pkArchive->writeSectionEnd();
            }
                break;
            case XMetaTranslatorType::SEQUENTIAL_CONTAINER:
            {
                const XMetaSequenceTranslator* pkSTranslator = (const XMetaSequenceTranslator*)pkMT;
                assert( pkSTranslator );
                XSize uiSize = pkSTranslator->getSize( pAddress );
                if ( uiSize > 0 )
                {
                    pkArchive->writeSectionBegin( strName );
                    pkArchive->write( "Count", uiSize );
                    for ( XSize i = 0; i < uiSize; ++i )
                    {
                        const XVoid* pItemAddress = pkSTranslator->getItem( pAddress, i );
                        assert( pItemAddress );
                        serializeMetaTranslator( pItemAddress, XStringUtil::format( "Item_%u", i + 1 ), pkSTranslator->getItemTranslator(), pkArchive );
                    }
                    
                    pkArchive->writeSectionEnd(); 
                }
            }
                break;
            case XMetaTranslatorType::ASSOCIATIVE_CONTAINER:
            {
                const XMetaAssociationTranslator* pkATranslator = (const XMetaAssociationTranslator*)pkMT;
                assert( pkATranslator );
                XSize uiSize = pkATranslator->getSize( pAddress );
                if ( uiSize > 0 )
                {
                    pkArchive->writeSectionBegin( strName );
                    pkArchive->write( "Count", uiSize );
                    std::vector< const XVoid* > allKeys;
                    std::vector< const XVoid* > allItems;
                    pkATranslator->getAllItems( pAddress, allKeys, allItems );
                    for ( XSize i = 0; i < uiSize; ++i )
                    {
                        pkArchive->writeSectionBegin( XStringUtil::format( "Item_%u", i + 1 ) );
                        serializeMetaTranslator( allKeys[i], "Key", pkATranslator->getKeyTranslator(), pkArchive );
                        serializeMetaTranslator( allItems[i], "Value", pkATranslator->getValueTranslator(), pkArchive );
                        pkArchive->writeSectionEnd();
                    }
                    pkArchive->writeSectionEnd();
                }
            }
                break;
                
            default:
                break;
        }
        
        return X_SUCCESS;
    }
    
    static XRet deserializeMetaClass( XVoid* pAddress, const XMetaClass* pkMC, XInputArchive* pkArchive )
    {
        assert( pAddress && pkMC && pkArchive );
        
        const TMapMetaFields& mapFields = pkMC->getAllFields();
        for ( auto& iter : mapFields )
        {
            XVoid* pFieldAddress = (XVoid*)( (XChar*)pAddress + iter.second->getOffset() );
            if ( !X_IS_SUCCESS( deserializeMetaTranslator( pFieldAddress, iter.second->getName(), iter.second->getTranslator(), pkArchive ) ) )
            {
                //X_LOG_ERROR( "failed to deserialize field" );
            }
        }
        
        return X_SUCCESS;
    }
    
    static XRet deserializeMetaTranslator( XVoid* pAddress, const XString& strName, const XMetaTranslator* pkMT, XInputArchive* pkArchive )
    {
        assert( pAddress && !strName.empty() && pkMT && pkArchive );
        switch ( pkMT->getTranslatorType() )
        {
            case XMetaTranslatorType::PRIMITIVE:
            {
                
#define X_IMPLEMENT_DESERIALIZE_PRI_TRANSLATOR( pt, t )  \
    case pt:    \
    {   \
        t v;    \
        if ( X_IS_SUCCESS( pkArchive->read( strName, v ) ) ) \
            *(t*)pAddress = v;  \
    }   \
    break;
                
                const XMetaPrimitiveTranslator* pkPTranslator = (const XMetaPrimitiveTranslator*)pkMT;
                assert( pkPTranslator );
                switch ( pkPTranslator->getPrimitiveType() )
                {
                    X_META_PRIMITIVE_TYPE_TRAVERSAL( X_IMPLEMENT_DESERIALIZE_PRI_TRANSLATOR );
                    default: assert( 0 ); break;
                }
#undef X_IMPLEMENT_DESERIALIZE_PRI_TRANSLATOR
            }
                break;
            case XMetaTranslatorType::POINTER:
            {
                const XMetaPointerTranslator* pkPTranslator = (const XMetaPointerTranslator*)pkMT;
                assert( pkPTranslator );
                const XMetaTranslator* pkTargetTranslator = pkPTranslator->getTargetTranslator();
                assert( pkTargetTranslator );
                *(XVoid**)pAddress = pkTargetTranslator->newObj();
                if ( *(XVoid**)pAddress != nullptr )
                {
                    deserializeMetaTranslator( *(XVoid**)pAddress, strName, pkTargetTranslator, pkArchive );
                }
            }
                break;
            case XMetaTranslatorType::CLASS:
            {
                const XMetaClassTranslator* pkCTranslator = (const XMetaClassTranslator*)pkMT;
                assert( pkCTranslator );
                if ( X_IS_SUCCESS( pkArchive->readSectionBegin( strName ) ) )
                {
                    deserializeMetaClass( pAddress, pkCTranslator->getMetaClass(), pkArchive );
                    
                    pkArchive->readSectionEnd();
                }
            }
                break;
            case XMetaTranslatorType::SEQUENTIAL_CONTAINER:
            {
                const XMetaSequenceTranslator* pkSTranslator = (const XMetaSequenceTranslator*)pkMT;
                assert( pkSTranslator );
                if ( X_IS_SUCCESS( pkArchive->readSectionBegin( strName ) ) )
                {
                    XSize uiSize = 0;
                    if ( X_IS_SUCCESS( pkArchive->read( "Count", uiSize ) )
                        && uiSize > 0 )
                    {
                        pkSTranslator->resize( pAddress, uiSize );
                        for ( XSize i = 0; i < uiSize; ++i )
                        {
                            const XVoid* pItemAddress = pkSTranslator->getItem( pAddress, i );
                            deserializeMetaTranslator( (XVoid*)pItemAddress, XStringUtil::format( "Item_%u", i + 1 ), pkSTranslator->getItemTranslator(), pkArchive );
                        }
                    }
                    
                    pkArchive->readSectionEnd();
                }
            }
                break;
            case XMetaTranslatorType::ASSOCIATIVE_CONTAINER:
            {
                const XMetaAssociationTranslator* pkATranslator = (const XMetaAssociationTranslator*)pkMT;
                assert( pkATranslator );
                if ( X_IS_SUCCESS( pkArchive->readSectionBegin( strName ) ) )
                {
                    XSize uiSize = 0;
                    if ( X_IS_SUCCESS( pkArchive->read( "Count", uiSize ) )
                        && uiSize > 0 )
                    {
                        const XMetaTranslator* pkKeyTranslator = pkATranslator->getKeyTranslator();
                        const XMetaTranslator* pkValueTranslator = pkATranslator->getValueTranslator();
                        assert( pkKeyTranslator && pkValueTranslator );
                        for ( XSize i = 0; i < uiSize; ++i )
                        {
                            if ( X_IS_SUCCESS( pkArchive->readSectionBegin( XStringUtil::format( "Item_%u", i + 1 ) ) ) )
                            {
                                XVoid* pKey = pkKeyTranslator->newObj();
                                XVoid* pValue = pkValueTranslator->newObj();
                                assert( pKey && pValue );
                                deserializeMetaTranslator( pKey, "Key", pkKeyTranslator, pkArchive );
                                deserializeMetaTranslator( pValue, "Value", pkValueTranslator, pkArchive );
                                pkATranslator->setItem( pAddress, (const XVoid*)pKey, (const XVoid*)pValue );
                                pkKeyTranslator->delObj( pKey );
                                pkKeyTranslator->delObj( pValue );
                                
                                pkArchive->readSectionEnd();
                            }
                        }
                    }
                    
                    pkArchive->readSectionEnd();
                }
            }
                break;
                
            default:
                break;
        }
        
        return X_SUCCESS;
    }
};

//------------------------------------------------------------------------------
XRet XMetaObjectSerializer::serialize( const XMetaObject* pkObject, XOutputArchive* pkArchive )
{
    return XMetaObjectSerializerImpl::serialize( pkObject, pkArchive );
}

//------------------------------------------------------------------------------
XMetaObject* XMetaObjectSerializer::deserialize( XInputArchive* pkArchive )
{
    return XMetaObjectSerializerImpl::deserialize( pkArchive );
}

X_NS_END
