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

#include "XFileDataStream.h"
#include "Base/XStringUtil.h"

X_NS_BEGIN

//------------------------------------------------------------------------------
XFileInputDataStream::XFileInputDataStream( const XString& strName )
: XFileInputDataStream( strName.c_str() )
{
}


XFileInputDataStream::XFileInputDataStream( const XChar* pName )
{
    X_RET_IF( !pName );
    
#if X_OS_WIN
    if (_wfopen_s(&m_pkFile, XStringUtil::utf8ToWide(pName,0).c_str(), L"rb"))
    {
        return;
    }
#else
    m_pkFile = fopen( pName, "rb" );
#endif
    
    X_RET_IF( !m_pkFile );
    
    fseek( m_pkFile, 0, SEEK_END );
    m_uiSize = ftell( m_pkFile );
    fseek( m_pkFile, 0, SEEK_SET );
}

//------------------------------------------------------------------------------
XFileInputDataStream::~XFileInputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XFileOutputDataStream::XFileOutputDataStream( const XString& strName, XBool bAppend )
: m_pkFile( nullptr )
{
    X_RET_IF( strName.empty() );
    
#if X_OS_WIN
    _wfopen_s(&m_pkFile, XStringUtil::utf8ToWide(strName).c_str(), bAppend ? L"ab" : L"wb");
#else
    m_pkFile = fopen( strName.c_str(), bAppend ? "ab" : "wb" );
#endif
}

//------------------------------------------------------------------------------
XFileOutputDataStream::~XFileOutputDataStream()
{
    close();
}

X_NS_END