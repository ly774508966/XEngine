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
#include "XSmartPointer.h"

X_NS_BEGIN

enum eLogLevel
{
    LL_DEBUG	= X_BIT( 0 ),
    LL_INFO		= X_BIT( 1 ),
    LL_WARNING	= X_BIT( 2 ),
    LL_ERROR	= X_BIT( 3 ),
    LL_ALL		= LL_DEBUG | LL_INFO | LL_WARNING | LL_ERROR,
};

struct XLogElement
{
    XString strSection;
    eLogLevel level;
    XString strLog;
    XString strFile;
    XString strFunction;
    XUInt32 uiLine;
};

class XLogListener;
class X_API XLogger
{

protected:
    /**
     output log if ( filter & level ).
     default filter is LL_ALL. means output all log.
     */
    XUInt32             m_uiFilter;
    
    XLogListener*       m_pkListener;
    std::vector< XLogElement >  m_vecBuffedLog;
public:
    XLogger();
    
    XVoid				setFilter( XUInt32 uiFilter ) { m_uiFilter = uiFilter; }
    XUInt32             getFilter() const { return m_uiFilter; }
    XVoid				log( const XString& strSection,
                            eLogLevel level,
                            const XString& strLog,
                            const XString& strFile,
                            const XString& strFunction,
                            XUInt32 uiLine );
    
    XVoid               setListener( XLogListener* pkLinstener );
    XLogListener*       getListener() { return m_pkListener; }
    
    static XLogger&     getIns() { static XLogger s_kIns; return s_kIns; }
};

class X_API XLogListener
{
public:
    
    virtual ~XLogListener() {}
    
    virtual XVoid		onLog( const XLogElement& kLog ) = 0;
};


// format log by pattern.
/*
 %d : data
    option :
     {  %y : year
        %m : month
        %d : day
        %h : hour
        %m : min
        %s : second
     }
    if not set data format, then default is : %y/%m/%d %h:%M:%s
 %s : setion
 %L : level
 %m : msg
 %f : file
 %F : function
 %l : line
 
 for example:
 "%d{%y/%m/%d %h:%m:%s} %s | %L | %m | %f(%l)" will output:
 2015/1/18 19:50:25 XEngine | DEBUG | ...... | XLogger.cpp(50)
 */
class X_API XLogFormater
{
public:
    class XPattern
    : public XRefObject
    {
    public:
        virtual ~XPattern() {}
        virtual XVoid format( XString& strOut, const XLogElement& kLog ) = 0;
    };
    typedef XSmartPointer< XPattern > XPatternPtr;
    
    XVoid               setPattern( const XString& strPattern );
    XString             format( const XLogElement& kLog );
    XVoid               format( XString& strOut, const XLogElement& kLog );
    
protected:
    std::vector< XPatternPtr > m_vecPatterns;
};


// used for write log like X_LOG_INFO( msg << ... << ... )
class X_API XLogStreamHelper
{
public:
    template <typename T>
    XLogStreamHelper& operator << ( T value ) { m_kStream << value;	return *this; }
    
public:
    std::ostringstream m_kStream;
};


#define X_LOGGING( section, level, text )	\
XLogger::getIns().log( section, level, ( XLogStreamHelper() << text ).m_kStream.str(), XString(__FILE__), XString(__FUNCTION__), __LINE__ )

#define X_ENGINE_LOG_SECTION	"XEngine"

#define	X_LOG_DEBUG( log )			X_LOGGING( X_ENGINE_LOG_SECTION, LL_DEBUG, log )
#define	X_LOG_INFO( log )			X_LOGGING( X_ENGINE_LOG_SECTION, LL_INFO, log )
#define	X_LOG_WARNING( log )		X_LOGGING( X_ENGINE_LOG_SECTION, LL_WARNING, log )
#define	X_LOG_ERROR( log )			X_LOGGING( X_ENGINE_LOG_SECTION, LL_ERROR, log )

X_NS_END

#endif // __XLOGGER_H__