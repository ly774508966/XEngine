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


class XPatternUnknown
: public XLogFormater::XPattern
{
protected:
    XString     m_strUnknown;
public:
    XPatternUnknown( const XString& strUnknown )
    : m_strUnknown( strUnknown )
    {
    }
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        strOut.append( m_strUnknown );
    }
};

class XPatternYear
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        return format( strOut, kLog, etm );
    }
    XVoid format( XString& strOut, const XLogElement& kLog, tm& tm )
    {
        std::stringstream stream;
        stream << std::setw(4) << (1900 + tm.tm_year);
        strOut.append( stream.str() );
    }
};

class XPatternMonth
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        return format( strOut, kLog, etm );
    }
    
    XVoid format( XString& strOut, const XLogElement& kLog, tm& tm )
    {
        std::stringstream stream;
        stream << std::setfill( '0' ) << std::setw(2) << 1 + tm.tm_mon;
        strOut.append( stream.str() );
    }
};

class XPatternDay
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        return format( strOut, kLog, etm );
    }
    
    XVoid format( XString& strOut, const XLogElement& kLog, tm& tm )
    {
        std::stringstream stream;
        stream << std::setfill( '0' ) << std::setw(2) << tm.tm_mday;
        strOut.append( stream.str() );
    }
};

class XPatternHour
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        return format( strOut, kLog, etm );
    }
    
    XVoid format( XString& strOut, const XLogElement& kLog, tm& tm )
    {
        std::stringstream stream;
        stream << std::setfill( '0' ) << std::setw(2) << tm.tm_hour;
        strOut.append( stream.str() );
    }
};

class XPatternMin
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        return format( strOut, kLog, etm );
    }
    
    XVoid format( XString& strOut, const XLogElement& kLog, tm& tm )
    {
        std::stringstream stream;
        stream << std::setfill( '0' ) << std::setw(2) << tm.tm_min;
        strOut.append( stream.str() );
    }
};

class XPatternSec
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm etm = *localtime( &et );
        
        return format( strOut, kLog, etm );
    }
    
    XVoid format( XString& strOut, const XLogElement& kLog, tm& tm )
    {
        std::stringstream stream;
        stream << std::setfill( '0' ) << std::setw(2) << tm.tm_sec;
        strOut.append( stream.str() );
    }
};

class XPatternDate
: public XLogFormater::XPattern
{
protected:
    std::vector< XLogFormater::XPatternPtr >  m_vecPatterns;
public:
    XPatternDate( const XString& strPattern )
    {
        X_RET_IF( strPattern.empty() );
        
        m_vecPatterns.clear();
        
        XString::size_type offset = 0;
        XString::size_type pos = strPattern.find( '%' );
        while ( pos != XString::npos
               && pos != strPattern.size() - 1 )
        {
            if ( pos != offset )
            {
                m_vecPatterns.push_back( X_NEW XPatternUnknown( strPattern.substr( offset, pos - offset ) ) );
            }
            
            switch ( strPattern[ pos + 1 ] )
            {
                case 'y': m_vecPatterns.push_back( X_NEW XPatternYear ); break;
                case 'm': m_vecPatterns.push_back( X_NEW XPatternMonth ); break;
                case 'd': m_vecPatterns.push_back( X_NEW XPatternDay ); break;
                case 'h': m_vecPatterns.push_back( X_NEW XPatternHour ); break;
                case 'M': m_vecPatterns.push_back( X_NEW XPatternMin ); break;
                case 's': m_vecPatterns.push_back( X_NEW XPatternSec ); break;
                default:
                    break;
            }
            offset = pos + 2;
            pos = strPattern.find( '%', offset );
        }
        
        if ( offset < strPattern.size() )
        {
            m_vecPatterns.push_back( X_NEW XPatternUnknown( strPattern.substr( offset ) ) );
        }
    }
    
    ~XPatternDate()
    {
        
    }
    
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        time_t  et;
        time( &et );
        tm tm = *localtime( &et );

        if ( !m_vecPatterns.empty() )
        {
            for ( auto i : m_vecPatterns )
            {
                i->format( strOut, kLog );
            }
        }
        else
        {
            std::stringstream stream;
            stream << std::setw(4) << (1900 + tm.tm_year) << '/' <<
            std::setfill( '0' ) << std::setw(2) << 1 + tm.tm_mon << '/' <<
            std::setfill( '0' ) << std::setw(2) << tm.tm_mday << ' ' <<
            std::setfill( '0' ) << std::setw(2) << tm.tm_hour << ':' <<
            std::setfill( '0' ) << std::setw(2) << tm.tm_min << ':' <<
            std::setfill( '0' ) << std::setw(2) << tm.tm_sec;
            strOut.append( stream.str() );
        }
    }
};

class XPatternSection
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        strOut.append( kLog.strSection );
    }
};

class XPatternLevel
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        // to do...
    }
};

class XPatternLog
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        strOut.append( kLog.strLog );
    }
};

class XPatternFile
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        XPath kPath( kLog.strFile );
        strOut.append( kPath.getFileName() );
    }
};

class XPatternFunction
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        strOut.append( kLog.strFunction );
    }
};

class XPatternLine
: public XLogFormater::XPattern
{
public:
    virtual XVoid format( XString& strOut, const XLogElement& kLog )
    {
        std::stringstream stream;
        stream << kLog.uiLine;
        strOut.append( stream.str() );
    }
};

XVoid XLogFormater::setPattern( const XString& strPattern )
{
    X_RET_IF( strPattern.empty() );
    
    m_vecPatterns.clear();
    
    XString::size_type offset = 0;
    XString::size_type pos = strPattern.find( '%' );
    while ( pos != XString::npos
           && pos != strPattern.size() - 1 )
    {
        if ( pos != offset )
        {
            m_vecPatterns.push_back( X_NEW XPatternUnknown( strPattern.substr( offset, pos - offset ) ) );
        }
        
        switch ( strPattern[ pos + 1 ] )
        {
        case 'd':
            {
                XString strDatePattern;
                XString::size_type posDPStart = pos + 2;
                XString::size_type posDPEnd = 0;
                if ( strPattern[ posDPStart ] == '{' )
                {
                    posDPEnd = strPattern.find( '}', posDPStart + 1 );
                    if ( posDPEnd != XString::npos
                        && posDPEnd - posDPStart > 2 )
                    {
                        strDatePattern = strPattern.substr( posDPStart + 1, posDPEnd - posDPStart - 1 );
                    }
                }
                m_vecPatterns.push_back( X_NEW XPatternDate( strDatePattern ) );
                if ( posDPEnd != 0 )
                {
                    offset = posDPEnd + 1;
                }
                else
                {
                    offset = pos + 2;
                }
            }
                break;
            case 's':
            {
                m_vecPatterns.push_back( X_NEW XPatternSection );
                offset = pos + 2;
            }
                break;
            case 'L':
            {
                m_vecPatterns.push_back( X_NEW XPatternLevel );
                offset = pos + 2;
            }
                break;
            case 'm':
            {
                m_vecPatterns.push_back( X_NEW XPatternLog );
                offset = pos + 2;
            }
                break;
            case 'f':
            {
                m_vecPatterns.push_back( X_NEW XPatternFile );
                offset = pos + 2;
            }
                break;
            case 'F':
            {
                m_vecPatterns.push_back( X_NEW XPatternFunction );
                offset = pos + 2;
            }
                break;
            case 'l':
            {
                m_vecPatterns.push_back( X_NEW XPatternLine );
                offset = pos + 2;
            }
                break;
            default:
                break;
        }
        
        pos = strPattern.find( '%', offset );
    }
    
    if ( offset < strPattern.size() )
    {
        m_vecPatterns.push_back( X_NEW XPatternUnknown( strPattern.substr( offset ) ) );
    }
}

XString XLogFormater::format( const XLogElement& kLog )
{
    XString strOut;
    format( strOut, kLog );
    return strOut;
}

XVoid XLogFormater::format( XString& strOut, const XLogElement& kLog )
{
    for ( auto i : m_vecPatterns )
    {
        assert( i != nullptr );
        i->format( strOut, kLog );
    }
}


XLogger::XLogger()
: m_uiFilter( LL_ALL )
, m_pkListener( nullptr )
{
}


XVoid XLogger::log( const XString& strSection, eLogLevel level, const XString &strLog, const XString& strFile, const XString& strFunction, XUInt32 uiLine )
{
    if ( m_uiFilter & (XUInt32)level )
    {
        XLogElement kElement;
        kElement.strSection = strSection;
        kElement.level = level;
        kElement.strLog = strLog;
        kElement.strFile = strFile;
        kElement.strFunction = strFunction;
        kElement.uiLine = uiLine;
        
        if ( m_pkListener )
        {
            m_pkListener->onLog( kElement );
        }
        else
        {
            m_vecBuffedLog.push_back( kElement );
        }
    }
}


XVoid XLogger::setListener( XLogListener* pkLinstener )
{
    XBool bOutputBuffedLog = !m_pkListener && pkLinstener && !m_vecBuffedLog.empty();
    m_pkListener = pkLinstener;
    if ( bOutputBuffedLog )
    {
        assert( !m_vecBuffedLog.empty() && m_pkListener );
        
        for ( auto& i : m_vecBuffedLog )
        {
            m_pkListener->onLog( i );
        }
        m_vecBuffedLog.clear();
    }
}

X_NS_END