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

#ifndef __XMETASTLTRANSLATOR_H__
#define __XMETASTLTRANSLATOR_H__

#include "XMetaTranslator.h"

X_NS_BEGIN

template < typename T >
class X_API XSequenceTranslator_Vector
: public XMetaSequenceTranslator
{
    typedef typename T::value_type  value_type;
public:
    
    virtual XVoid*                      newObj() const override { return XMetaTranslator::defaultNewObj<T>(); }
    virtual XVoid                       delObj( XVoid* pAddress ) const override { XMetaTranslator::defaultDelObj<T>( pAddress ); }
    virtual XSize                       getMemSize() const override { return XMetaTranslator::defaultGetMemSize<T>(); }
    virtual XVoid                       construct( XVoid* pAddress ) const override { XMetaTranslator::defaultConstruct<T>( pAddress ); }
    virtual XVoid                       destruct( XVoid* pAddress ) const override { XMetaTranslator::defaultDestruct<T>( pAddress ); }

    virtual XBool                       equals( const XVoid* pA, const XVoid* pB ) const override
    {
        X_RET_VAL_IF( pA == pB, true );
        const XMetaTranslator* pkItemTranslator = getItemTranslator();
        assert( pkItemTranslator );
        const T* pVectorA = (const T*)pA;
        const T* pVectorB = (const T*)pB;
        X_RET_VAL_IF( pVectorA->size() != pVectorB->size(), false );
        for ( XSize i = 0; i < pVectorA->size(); ++i )
        {
            if ( !pkItemTranslator->equals( (const XVoid*)( &pVectorA->at( i ) ), (const XVoid*)( &pVectorB->at( i ) ) ) )
            {
                return false;
            }
        }
        return true;
    }

    virtual XVoid                       assign( XVoid* pDest, const XVoid* pSrc, XUInt32 uiFlag ) const override
    {
        X_RET_IF( pDest == pSrc );
        const XMetaTranslator* pkItemTranslator = getItemTranslator();
        assert( pkItemTranslator );
        T* pVectorDest = (T*)pDest;
        const T* pVectorSrc = (const T*)pSrc;
        pVectorDest->resize( pVectorSrc->size() );
        for ( XSize i = 0; i < pVectorDest->size(); ++i )
        {
            pkItemTranslator->assign( (XVoid*)( &pVectorDest->at( i ) ), (const XVoid*)( &pVectorSrc->at( i ) ), uiFlag );
        }
    }

    virtual const XMetaTranslator*      getItemTranslator() const override { return getMetaTranslator<value_type>(); }
    
    virtual XSize                       getSize( const XVoid* pAddress ) const override
    {
        assert( pAddress );
        const T* pVector = (const T*)pAddress;
        return pVector->size();
    }

    virtual XVoid                       clear( XVoid* pAddress ) const
    {
        assert( pAddress );
        T* pVector = (T*)pAddress;
        pVector->clear();
    }

    virtual XVoid                       resize( XVoid* pAddress, XSize uiSize ) const override
    {
        assert( pAddress );
        T* pVector = (T*)pAddress;
        pVector->resize( uiSize );
    }

    virtual XVoid                       setItem( XVoid* pAddress, XSize uiIdx, const XVoid* pValue ) const override
    {
        assert( pAddress );
        T* pVector = (T*)pAddress;
        X_RET_IF( uiIdx >= pVector->size() );

        getItemTranslator()->assign( (XVoid*)( &pVector->at( uiIdx ) ), pValue, 0 );
    }

    virtual const XVoid*                getItem( const XVoid* pAddress, XSize uiIdx ) const override
    {
        assert( pAddress );
        const T* pVector = (const T*)pAddress;
        X_RET_VAL_IF( uiIdx >= pVector->size(), nullptr );
        return (const XVoid*)( &pVector->at( uiIdx ) );
    }

    virtual XVoid                       insert( XVoid* pAddress, XSize uiIdx, const XVoid* pValue ) const override
    {
        assert( pAddress );
        T* pVector = (T*)pAddress;
        X_RET_IF( uiIdx >= pVector->size() );
        pVector->insert( pVector->begin() + uiIdx, *(const value_type*)pValue );
    }

    virtual XVoid                       remove( XVoid* pAddress, XSize uiIdx ) const override
    {
        assert( pAddress );
        T* pVector = (T*)pAddress;
        X_RET_IF( uiIdx >= pVector->size() );
        pVector->erase( pVector->begin() + uiIdx );
    }

    virtual XVoid                       moveUp( XVoid* pAddress, XSize uiIdx ) const override {}
    virtual XVoid                       moveDown( XVoid* pAddress, XSize uiIdx ) const override {}
};


//------------------------------------------------------------------------------
template < typename T >
class XMetaTranslatorHelper< std::vector< T > >
{
public:
    static const XMetaTranslator*   getTranslator()
    {
        static XSequenceTranslator_Vector< std::vector< T >  > s_kIns;
        return &s_kIns;
    }
};



//------------------------------------------------------------------------------
template < typename T >
class X_API XSequenceTranslator_Map
: public XMetaAssociationTranslator
{
public:
    typedef typename T::key_type key_type;
    typedef typename T::mapped_type value_type;
public:
    
    virtual XVoid*                      newObj() const override { return XMetaTranslator::defaultNewObj<T>(); }
    virtual XVoid                       delObj( XVoid* pAddress ) const override { XMetaTranslator::defaultDelObj<T>( pAddress ); }
    virtual XSize                       getMemSize() const override { return XMetaTranslator::defaultGetMemSize<T>(); }
    virtual XVoid                       construct( XVoid* pAddress ) const override { XMetaTranslator::defaultConstruct<T>( pAddress ); }
    virtual XVoid                       destruct( XVoid* pAddress ) const override { XMetaTranslator::defaultDestruct<T>( pAddress ); }

    virtual XBool                       equals( const XVoid* pA, const XVoid* pB ) const override
    {
        X_RET_VAL_IF( pA == pB, true );
        const T* pMapA = (const T*)pA;
        const T* pMapB = (const T*)pB;
        X_RET_VAL_IF( pMapA->size() != pMapB->size(), false );

        const XMetaTranslator* pkKeyTranslator = getKeyTranslator();
        const XMetaTranslator* pkValueTranslator = getValueTranslator();
        assert( pkKeyTranslator && pkValueTranslator );

        for ( auto& iterA : *pMapA )
        {
            auto iterB = pMapB->find( iterA.first );
            if ( iterB == pMapB->end() )
            {
                return false;
            }
            if ( !pkValueTranslator->equals( (const XVoid*)( &iterA.second ), (const XVoid*)( &iterB->second ) ) )
            {
                return false;
            }
        }
        return true;
    }

    virtual XVoid                       assign( XVoid* pDest, const XVoid* pSrc, XUInt32 uiFlag ) const override
    {
        X_RET_IF( pDest == pSrc );
        T& kMapDest = *(T*)pDest;
        const T& kMapSrc = *(const T*)pSrc;
        for ( auto& iterSrc : kMapSrc )
        {
            getValueTranslator()->assign( (XVoid*)( &kMapDest[ iterSrc.first ] ), (const XVoid*)( &iterSrc.second ), uiFlag );
        }
    }

    virtual XSize                       getSize( const XVoid* pAddress ) const override
    {
        assert( pAddress );
        const T* pMap = (const T*)pAddress;
        return pMap->size();
    }

    virtual XVoid                       clear( XVoid* pAddress ) const override
    {
        assert( pAddress );
        T& kMap = *(T*)pAddress;
        kMap.clear();
    }

    virtual const XMetaTranslator*      getKeyTranslator() const override
    {
        return getMetaTranslator< key_type >();
    }

    virtual const XMetaTranslator*      getValueTranslator() const override
    {
        return getMetaTranslator< value_type >();
    }

    virtual XVoid                       setItem( XVoid* pAddress, const XVoid* pKey, const XVoid* pValue ) const override
    {
        assert( pAddress );
        T& kMap = *(T*)pAddress;
        kMap[ *(const key_type*)pKey ] = *(const value_type*)pValue;
        //getValueTranslator()->assign( (XVoid*)( &kMap[ *(const key_type*)pKey ] ), pValue );
    }

    virtual XVoid                       getAllItems( const XVoid* pAddress, std::vector<const XVoid*>& allKeys, std::vector<const XVoid*>& allItems ) const override
    {
        assert( pAddress );
        T& kMap = *(T*)pAddress;
        allKeys.reserve( kMap.size() );
        allItems.reserve( kMap.size() );
        for ( auto& iter : kMap )
        {
            allKeys.push_back( (const XVoid*)( &iter.first ) );
            allItems.push_back( (const XVoid*)( &iter.second ) );
        }
    }

    virtual const XVoid*                getItem( const XVoid* pAddress, const XVoid* pKey ) const override
    {
        assert( pAddress );
        T* pMap = (T*)pAddress;
        auto iter = pMap->find( *(const key_type*)pKey );
        if ( iter == pMap->end() )
        {
            return (const XVoid*)( &iter->second );
        }
        return nullptr;
    }

    virtual XVoid                       remove( XVoid* pAddress, const XVoid* pKey ) const override
    {
        assert( pAddress );
        T* pMap = (T*)pAddress;
        pMap->erase( *(const key_type*)pKey );
    }
};


//------------------------------------------------------------------------------
template < typename TKey, typename TItem >
class XMetaTranslatorHelper< std::map< TKey, TItem > >
{
public:
    static const XMetaTranslator*   getTranslator()
    {
        static XSequenceTranslator_Map< std::map< TKey, TItem > > s_kIns;
        return &s_kIns;
    }
};

X_NS_END

#endif // __XMETASTLTRANSLATOR_H__