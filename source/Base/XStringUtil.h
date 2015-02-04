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

#ifndef __XSTRINGUTIL_H__
#define __XSTRINGUTIL_H__

#include "XPreDef.h"

X_NS_BEGIN

class X_API XStringUtil
{
public:
	static XString					toUpper( const XString& str );
	static XString					toLower( const XString& str );
    
	static XString					format( const XChar* format, ... );
    
    template< typename T >
    static XString                  toString( const T& v );
    template< typename T >
    static XRet                     fromString( const XString& str, T& v );
    
	static XVoid					trim( XString& str, XBool left = true, XBool right = true );
	static XVoid 					splitString( XArrString& strArray, const XString& str, const XString& strSplit );
	static XString                  toString( const XArrString& arr, const XString& strMid = ";" );
    
    static XWString                 utf8ToWide( const XChar* pUTF8, XSize len );
    static XWString                 utf8ToWide( const XString& strUTF8 );
    
    static XString                  wideToUTF8( const XWChar* pWide, XSize len );
    static XString                  wideToUTF8( const XWString& strWide );

	static XUInt32					crc32( const XChar* pStr, XSize len );
	static XUInt32					crc32( const XString& str );
	static XUInt32                  crc32( const XWChar* pStr, XSize len );
	static XUInt32                  crc32( const XWString& str );
};


//------------------------------------------------------------------------------
X_FORCEINLINE XString XStringUtil::toUpper( const XString& str )
{
    XString strResult = str;
    std::transform( str.begin(), str.end(), strResult.begin(), ::toupper );
    return strResult;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XString XStringUtil::toLower( const XString& str )
{
    XString strResult = str;
    std::transform( str.begin(), str.end(), strResult.begin(), ::tolower );
    return strResult;
}

//------------------------------------------------------------------------------
template< typename T >
X_FORCEINLINE XString XStringUtil::toString( const T& v )
{
    std::stringstream ss;
    ss << v;
    return ss.str();
}

//------------------------------------------------------------------------------
template<>
X_FORCEINLINE XString XStringUtil::toString<XString>( const XString& v )
{
    return v;
}

//------------------------------------------------------------------------------
template<>
X_FORCEINLINE XString XStringUtil::toString<XWString>( const XWString& v )
{
    return XStringUtil::wideToUTF8( v );
}

//------------------------------------------------------------------------------
template<>
X_FORCEINLINE XString XStringUtil::toString<XBool>( const XBool& v )
{
    return v ? "true" : "false";
}

//------------------------------------------------------------------------------
template< typename T >
X_FORCEINLINE XRet XStringUtil::fromString( const XString& str, T& v )
{
    std::stringstream ss( str );
    ss >> v;
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
template<>
X_FORCEINLINE XRet XStringUtil::fromString<XString>( const XString& str, XString& v )
{
    v = str;
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
template<>
X_FORCEINLINE XRet XStringUtil::fromString<XWString>( const XString& str, XWString& v )
{
    v = XStringUtil::utf8ToWide( str );
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
template<>
X_FORCEINLINE XRet XStringUtil::fromString<XBool>( const XString& str, XBool& v )
{
    if ( str == "true" )
    {
        v = true;
        return X_SUCCESS;
    }
    else if ( str == "false" )
    {
        v = false;
        return X_SUCCESS;
    }
    return X_ERROR;
}

// ------------------------------------------------------------------------
X_FORCEINLINE XWString XStringUtil::utf8ToWide( const XString& strUTF8 )
{
    return utf8ToWide( strUTF8.c_str(), strUTF8.size() );
}

// ------------------------------------------------------------------------
X_FORCEINLINE XWString XStringUtil::utf8ToWide( const XChar* pUTF8, XSize len )
{
    std::wstring_convert< std::codecvt_utf8_utf16< XWChar > > cvt;
    return cvt.from_bytes( pUTF8, pUTF8 + ( len ? len : strlen(pUTF8) ) );
}

// ------------------------------------------------------------------------
X_FORCEINLINE XString XStringUtil::wideToUTF8( const XWString& strWide )
{
    return wideToUTF8( strWide.c_str(), strWide.size() );
}

// ------------------------------------------------------------------------
X_FORCEINLINE XString XStringUtil::wideToUTF8( const XWChar* pWide, XSize len )
{
    std::wstring_convert< std::codecvt_utf8_utf16< XWChar > > cvt;
    return cvt.to_bytes( pWide, pWide + ( len ? len : wcslen(pWide) ) );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XUInt32 XStringUtil::crc32( const XString& str )
{
	X_RET_VAL_IF( str.empty(), 0 );
	return crc32( str.c_str(), str.size() );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XUInt32 XStringUtil::crc32( const XWString& str )
{
	X_RET_VAL_IF( str.empty(), 0 );
	return crc32( str.c_str(), str.size() );
}

X_NS_END

#endif // __XSTRINGUTIL_H__