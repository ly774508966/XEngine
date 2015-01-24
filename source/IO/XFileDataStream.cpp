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
XFileInputDataStream::XFileInputDataStream()
: m_pkFile( nullptr )
{
}

//------------------------------------------------------------------------------
XFileInputDataStream::~XFileInputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XRet XFileInputDataStream::open( const XString& strName )
{
    X_RET_VAL_IF( strName.empty(), X_ERROR );
    
    FILE* pkFile = nullptr;
#if X_OS_WIN
	if (_wfopen_s(&pkFile, XStringUtil::UTF8ToWide(strName).c_str(), L"rb"))
	{
		return X_ERROR;
	}
#else
    pkFile = fopen( strName.c_str(), "rb" );
#endif
    return open( pkFile );
}

//------------------------------------------------------------------------------
XRet XFileInputDataStream::open( FILE* pkFile )
{
    X_RET_VAL_IF( !pkFile, X_ERROR );
    
    m_pkFile = pkFile;
    
    fseek( m_pkFile, 0, SEEK_END );
    m_size = ftell( m_pkFile );
    fseek( m_pkFile, 0, SEEK_SET );
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XFileOutputDataStream::XFileOutputDataStream()
: m_pkFile( nullptr )
{
}

//------------------------------------------------------------------------------
XFileOutputDataStream::~XFileOutputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XRet XFileOutputDataStream::open( const XString& strName, XBool bAppend /*= false*/ )
{
    X_RET_VAL_IF( strName.empty(), X_ERROR );
    
    FILE* pkFile = nullptr;
#if X_OS_WIN
    _wfopen_s( &pkFile, XStringUtil::UTF8ToWide( strName ).c_str(), bAppend ? L"ab" : L"wb" );
#else
    pkFile = fopen( strName.c_str(), bAppend ? "ab" : "wb" );
#endif
    return open( pkFile );
}

//------------------------------------------------------------------------------
XRet XFileOutputDataStream::open( FILE* pkFile )
{
    X_RET_VAL_IF( !pkFile, X_ERROR );
    
    m_pkFile = pkFile;
    
    return X_SUCCESS;
}

X_NS_END