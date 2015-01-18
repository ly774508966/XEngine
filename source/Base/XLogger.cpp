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


#include "XLogger.h"
#include "XPath.h"
#include <iomanip>

X_NS_BEGIN

class TDefaultLogFormater
: public XLogFormater
{
public:
    static TDefaultLogFormater& getIns() { static TDefaultLogFormater s_kIns; return s_kIns; }
    
    virtual XString     format( const XString& strSection,
                               eLogLevel level,
                               const XString& strLog,
                               const XChar* strFile,
                               const XChar* strFunction,
                               XUInt32 uiLine )
    {
        static const XChar* s_pSeparator = "  |  ";
        static std::stringstream stream;
        stream.str("");
        
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        stream << std::setw(4) << (1900 + etm.tm_year) << '/' <<
        std::setfill( '0' ) << std::setw(2) << 1 + etm.tm_mon << '/' <<
        std::setfill( '0' ) << std::setw(2) << etm.tm_mday << ' ';
        
        stream << std::setfill( '0' ) << std::setw(2) << etm.tm_hour << ':' <<
        std::setfill( '0' ) << std::setw(2) << etm.tm_min << ':' <<
        std::setfill( '0' ) << std::setw(2) << etm.tm_sec << ' ';
        
        stream << strSection << s_pSeparator /*<< CLogLevel::ToString( level ) << s_pSeparator */ << strLog;
        
        XPath kFile( strFile );
        stream << s_pSeparator << kFile.getFileName() << '(' << uiLine << ')';
        
        stream << std::endl;
        
        return stream.str();
    }
};


XLogger::XLogger()
: m_uiFilter( LL_ALL )
, m_pkCurLogFormater( &TDefaultLogFormater::getIns() )
{
}


XVoid XLogger::log( const XString& strSection, eLogLevel level, const XString &strLog, const XChar *strFile, const XChar *strFunction, XUInt32 uiLine)
{
    if ( (m_uiFilter & (XUInt32)level) )
    {
        assert( m_pkCurLogFormater != nullptr );
        XString log = m_pkCurLogFormater->format( strSection, level, strLog, strFile, strFunction, uiLine );
        for ( auto i : m_vecListeners )
        {
            i->onLog( log );
        }
    }
}

//------------------------------------------------------------------------------
XRet XLogger::registerListener( XLogListener* pkListener )
{
    if ( std::find( m_vecListeners.begin(), m_vecListeners.end(), pkListener ) == m_vecListeners.end() )
    {
        m_vecListeners.push_back( pkListener );
        return X_SUCCESS;
    }
    return X_ERROR;

}

//------------------------------------------------------------------------------
XRet XLogger::unregisterListener( XLogListener* pkListener )
{
    auto iter = std::find( m_vecListeners.begin(), m_vecListeners.end(), pkListener );
    if ( iter != m_vecListeners.end() )
    {
        m_vecListeners.erase( iter );
        return X_SUCCESS;
    }
    return X_ERROR;
}

//------------------------------------------------------------------------------

XVoid XLog2Console::onLog( const XString& strLog )
{
    XLogger::trace( strLog.c_str() );
}

X_NS_END