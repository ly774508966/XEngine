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
    
	static const XString			EMPTY_STRING;
	static const XWString			EMPTY_WSTRING;
    
	static XString					toUpper( const XString& str );
	static XString					toLower( const XString& str );
    
	static XString					format( const XChar* format, ... );
    
	static XVoid					trim( XString& str, XBool left = true, XBool right = true );
	static XVoid 					splitString( XArrString& strArray, const XString& str, const XString& strSplit );
	static XString                  toString( const XArrString& arr );
};


X_NS_END

#endif // __XSTRINGUTIL_H__