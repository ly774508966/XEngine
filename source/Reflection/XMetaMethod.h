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

#ifndef __XMETAMETHOD_H__
#define __XMETAMETHOD_H__


#include "XMetaObject.h"

X_NS_BEGIN


/*
typedef std::vector< const XMetaType* > TVecMetaTypes;
class X_API XMetaMethod
: public XMetaObject
{
protected:
    
    const XMetaClass*       m_pkParent;
    
    XBool                   m_bIsMemberMethod;
    XUInt8                  m_uiNumOfParams;
    
    TVecMetaTypes           m_vecParamTypes;
    const XMetaType*        m_pkRetType;
    
public:
    XMetaMethod( const XMetaClass* pkParent, const XString& strName );
    
    const XMetaClass*       getParent() const { return m_pkParent; }
    
    XBool                   isMemberMethod() const { return m_bIsMemberMethod; }
    const TVecMetaTypes&    getParamTypes() const { return m_vecParamTypes; }
    const XMetaType&        getReturnType() const { return *m_pkRetType; }
    
    virtual XVoid           invoke( XMetaVariant*& kRet, XVoid* pkObj, const std::vector<XMetaVariant*>& vecParams ) const = 0;
};





template< typename TFun, typename D = TFun >
class XMetaMethodTraits;


template< typename TFun >
class XMetaMethod_T
: public XMetaMethod
{
    friend class XMetaMethodTraits< TFun >;
protected:
    
    TFun    m_pkFun;
public:
    XMetaMethod_T( const XMetaClass* pkParent, const XString& strName, TFun f )
    : XMetaMethod( pkParent, strName )
    , m_pkFun( f )
    {
        XMetaMethodTraits< TFun >::buildMetaMethod( *this );
    }
    
    virtual XVoid           invoke( XMetaVariant*& kRet, XVoid* pkObj, const std::vector<XMetaVariant*>& vecParams ) const
    {
        XMetaMethodTraits< TFun >::invoke( m_pkFun, kRet, pkObj, vecParams );
    }
};

template< typename R, typename D >
class XMetaMethodTraits< R (*) (), D >
{
public:
    static const XBool bMemberFunction = false;
    static const XUInt8 uiNumOfParams = 0;
    typedef D DeclType;
    typedef R ReturnType;
    static XVoid invoke( D fp, XMetaVariant*& kRet, XVoid* pkObj, const std::vector<XMetaVariant*>& vecParams )
    {
        kRet = new XMetaVariant_T< R >( fp () );
        //kRet( fp () );
    }
    static XVoid buildMetaMethod( XMetaMethod_T< D >& kMetaMethod )
    {
        kMetaMethod.m_bIsMemberMethod = false;
        
        kMetaMethod.m_uiNumOfParams = uiNumOfParams;
        
        kMetaMethod.m_pkRetType = &XMetaTypeHelper< ReturnType >::getMetaType();
    }
};

template< typename R, typename P1, typename D >
class XMetaMethodTraits< R (*) (P1), D >
{
public:
    static const XBool bMemberFunction = false;
    static const XUInt8 uiNumOfParams = 1;
    typedef D DeclType;
    typedef R ReturnType;
    static XVoid invoke( D fp, XMetaVariant*& kRet, XVoid* pkObj, const std::vector<XMetaVariant*>& vecParams )
    {
        if( vecParams.size() >= 1
           && vecParams[0]->getMetaType().getType() == XMetaTypeHelper<P1>::getMetaType().getType() )
        {
            XMetaVariant_T< P1 >* p1 = (XMetaVariant_T< R >*)( vecParams[0] );
            kRet = new XMetaVariant_T< R >( fp ( p1->getValue() ) );
        }
    }
    static XVoid buildMetaMethod( XMetaMethod_T< D >& kMetaMethod )
    {
        kMetaMethod.m_uiNumOfParams = uiNumOfParams;
        
        kMetaMethod.m_pkRetType = &XMetaTypeHelper< ReturnType >::getMetaType();
        
        kMetaMethod.m_vecParamTypes.clear();
        kMetaMethod.m_vecParamTypes.push_back( &XMetaTypeHelper< P1 >::getMetaType() );
    }
};
 */

X_NS_END

#endif // __XMETAMETHOD_H__
