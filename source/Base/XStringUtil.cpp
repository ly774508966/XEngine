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


#include "XStringUtil.h"

X_NS_BEGIN

const XString XStringUtil::EMPTY_STRING;
const XWString XStringUtil::EMPTY_WSTRING;

//------------------------------------------------------------------------------
XString XStringUtil::toUpper( const XString& str )
{
	XString strResult = str;
	std::transform( str.begin(), str.end(), strResult.begin(), toupper );
	return strResult;
}

//------------------------------------------------------------------------------
XString XStringUtil::toLower( const XString& str )
{
	XString strResult = str;
	std::transform( str.begin(), str.end(), strResult.begin(), tolower );
	return strResult;
}

//------------------------------------------------------------------------------
XString XStringUtil::format( const XChar* format, ... )
{
	XChar temp[1024];
	va_list ap;
	va_start( ap, format );
	XInt32 nResult = vsnprintf( temp, 1024-sizeof(XChar), format, ap );
	va_end( ap );
	if ( nResult > -1
		&& nResult < 1024 - sizeof(XChar) )
	{
		temp[nResult ] = '\0';
		return XString( temp );
	}
    
	XInt32 nBufferSize = 256;
	XChar* pkCodeBuffer = 0;
    
	while( true )
	{
		pkCodeBuffer = new XChar[nBufferSize];
        
		va_list ap;
		va_start( ap, format );
		nResult = vsnprintf( pkCodeBuffer, nBufferSize-sizeof(XChar), format, ap );
		va_end( ap );
        
		if ( nResult > -1
			&& nResult < nBufferSize-sizeof(XChar) )
		{
			pkCodeBuffer[nResult] = '\0';
			break;
		}
		else
		{
			nBufferSize *= 2;
			X_SAFE_DEL( pkCodeBuffer );
		}
	}
    
	XString strResult = pkCodeBuffer;
	X_SAFE_DEL( pkCodeBuffer );
	return strResult;
}

//------------------------------------------------------------------------------
XVoid XStringUtil::trim( XString& str, XBool left /*= true*/, XBool right /*= true */ )
{
	static const XString delims = " \t\r";
	if(right)
	{
		str.erase(str.find_last_not_of(delims)+1); // trim right
	}
	if(left)
	{
		str.erase(0, str.find_first_not_of(delims)); // trim left
	}
}

// ------------------------------------------------------------------------
XVoid XStringUtil::splitString( XArrString& strArray, const XString& str, const XString& strSplit )
{
	XString::size_type nPos = 0;
	XString::size_type nPrev_Pos = 0;
    
	while( ( nPos = str.find_first_of( strSplit, nPos ) ) != XString::npos )
	{
		if( nPrev_Pos < nPos )
			strArray.push_back( str.substr(nPrev_Pos, nPos-nPrev_Pos) );
        
		nPos += strSplit.length();
		nPrev_Pos = nPos;
	}
	if( nPrev_Pos < str.size() )
		strArray.push_back( str.substr(nPrev_Pos, str.size()-nPrev_Pos) );
}

// ------------------------------------------------------------------------
XString XStringUtil::toString( const XArrString& arr )
{
	X_RET_VAL_IF( arr.empty(), EMPTY_STRING );
    
	std::stringstream stream;
	for ( XUInt32 i = 0; i < arr.size(); ++i )
	{
		if ( i != 0 )
		{
			stream << "";
		}
        
		stream << arr[i];
	}
    
	return stream.str();
}

X_NS_END