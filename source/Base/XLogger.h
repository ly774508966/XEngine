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

#ifndef __XLOGGER_H__
#define __XLOGGER_H__

#include "XPreDef.h"

X_NS_BEGIN

enum eLogLevel
{
    LL_DEBUG	= X_BIT( 0 ),
    LL_INFO		= X_BIT( 1 ),
    LL_WARNING	= X_BIT( 2 ),
    LL_ERROR	= X_BIT( 3 ),
    LL_ALL		= LL_DEBUG | LL_INFO | LL_WARNING | LL_ERROR,
};


class X_API XLogListener
{
public:
    
    virtual ~XLogListener() {}
    
    virtual XVoid		onLog( const XString& strLog ) = 0;
};


class X_API XLog2Console:
public XLogListener
{
public:
    virtual XVoid		onLog( const XString& strLog );
};


class X_API XLogFormater
{
public:
    virtual XString     format( const XString& strSection,
                               eLogLevel level,
                               const XString& strLog,
                               const XChar* strFile,
                               const XChar* strFunction,
                               XUInt32 uiLine ) = 0;
};

class X_API XLogger
{

protected:
    /**
     output log if ( filter & level ).
     default filter is LL_ALL. means output all log.
     */
    XUInt32             m_uiFilter;
    
    XLogFormater*       m_pkCurLogFormater;
    
    std::vector< XLogListener* >	m_vecListeners;
public:
    XLogger();
    
    XVoid				setFilter( XUInt32 uiFilter ) { m_uiFilter = uiFilter; }
    XUInt32             getFilter() const { return m_uiFilter; }
    XVoid				log( const XString& strSection,
                            eLogLevel level,
                            const XString& strLog,
                            const XChar* strFile,
                            const XChar* strFunction,
                            XUInt32 uiLine );
    XRet				registerListener( XLogListener* pkListener );
    XRet				unregisterListener( XLogListener* pkListener );
    
    static XLogger&     getIns() { static XLogger s_kIns; return s_kIns; }
    static XVoid        trace( const XChar* log );
};


class X_API XLogStreamHelper
{
public:
    template <typename T>
    XLogStreamHelper& operator << ( T value ) { m_kStream << value;	return *this; }
    
public:
    std::ostringstream m_kStream;
};

#define X_LOGGING( section, level, text )	\
XLogger::getIns().log( section, level, ( XLogStreamHelper() << text ).m_kStream.str(), __FILE__, __FUNCTION__, __LINE__ )

#define X_ENGINE_LOG_SECTION	"XEngine"

//! stream base log version. use as : msg << a << b.
#define	X_LOG_DEBUG( log )			X_LOGGING( X_ENGINE_LOG_SECTION, LL_DEBUG, log )
#define	X_LOG_INFO( log )			X_LOGGING( X_ENGINE_LOG_SECTION, LL_INFO, log )
#define	X_LOG_WARNING( log )		X_LOGGING( X_ENGINE_LOG_SECTION, LL_WARNING, log )
#define	X_LOG_ERROR( log )			X_LOGGING( X_ENGINE_LOG_SECTION, LL_ERROR, log )


X_NS_END

#endif // __XLOGGER_H__