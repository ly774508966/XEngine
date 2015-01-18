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


#include "XPath.h"

X_NS_BEGIN


//------------------------------------------------------------------------------
XVoid XPath::format()
{
    std::replace( m_strPath.begin(), m_strPath.end(), '\\', '/' );
    
    XString::size_type iPos = m_strPath.find( "../" );
    while ( iPos != XString::npos )
    {
        XString::size_type iFront = iPos;
        if ( iFront == 0 )
        {
            break;
        }
        if ( m_strPath[iFront-1] == '/'
            && iFront > 0 )
        {
            iFront -= 2;
        }
        
        XBool bFind = false;
        while ( iFront > 0 )
        {
            XChar str = m_strPath[iFront];
            if ( str == '/' )
            {
                m_strPath.erase( iFront, iPos + 2 - iFront );
                bFind = true;
                break;
            }
            
            --iFront;
        }
        
        if ( bFind )
        {
            iPos = m_strPath.find( "../" );
        }
        else
        {
            break;
        }
    }
    
    if ( m_strPath.size() > 2 )
    {
#if X_OS_WIN
        // lower dirve name.
        if ( isalpha( strTemp[0] ) && strTemp[1] == ':' ) 
        {
            strTemp[0] = tolower( strTemp[0] );
        }
#endif
    }
}

//------------------------------------------------------------------------------
XString XPath::getDirectory()
{
    XSize uiPos = m_strPath.find_last_of( '/' );
    if ( uiPos != XString::npos )
    {
        if ( uiPos < ( m_strPath.length() - 1 ) )
        {
            return m_strPath.substr( 0, uiPos );
        }
        else
        {
            return m_strPath;
        }
    }
    
    return "";
}

//------------------------------------------------------------------------------
XString XPath::getExtension()
{
    XSize pos = m_strPath.find_last_of( '.' );
    if( pos == XString::npos )
    {
        return "";
    }
    
    if ( pos < ( m_strPath.length() - 1 ) )
    {
        return m_strPath.substr( pos + 1 );
    }
    
    return "";
}

//------------------------------------------------------------------------------
XString XPath::getFileName( XBool bWithExt /*= true*/ )
{
    XSize pos = m_strPath.find_last_of( '/' );
    if ( pos == XString::npos )
    {
        return m_strPath;
    }
    
    if ( pos < ( m_strPath.length() - 1) )
    {
        return m_strPath.substr( pos + 1 );
    }
    
    return "";
}

X_NS_END