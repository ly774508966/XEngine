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

#ifndef __XARCHIVE_H__
#define __XARCHIVE_H__

#include "Base/XPreDef.h"
#include "Base/XSmartPointer.h"

X_NS_BEGIN

class XInputDataStream;
typedef XVoid* XArchiveNodePtr;
typedef XVoid* XArchiveAttributePtr;
class X_API XInputArchive
	: public XRefObject
{
public:
	virtual ~XInputArchive() {}

	virtual XUInt32				getVersion() const = 0;

	virtual const XString&		getTypeName() const = 0;
    
    virtual XRet                load( XInputDataStream* pkStream ) = 0;
    virtual XRet                load( const XVoid* pkData, XSize size ) = 0;

	virtual XRet				read( const XString& name, XBool& v ) = 0;
	virtual XRet				read( const XString& name, XFloat& v ) = 0;
	virtual XRet				read( const XString& name, XDouble& v ) = 0;
	virtual XRet				read( const XString& name, XLong& v ) = 0;
	virtual XRet				read( const XString& name, XULong& v ) = 0;

	virtual XRet				read( const XString& name, XInt8& v ) = 0;
	virtual XRet				read( const XString& name, XInt16& v ) = 0;
	virtual XRet				read( const XString& name, XInt32& v ) = 0;
	virtual XRet				read( const XString& name, XInt64& v ) = 0;

	virtual XRet				read( const XString& name, XUInt8& v ) = 0;
	virtual XRet				read( const XString& name, XUInt16& v ) = 0;
	virtual XRet				read( const XString& name, XUInt32& v ) = 0;
	virtual XRet				read( const XString& name, XUInt64& v ) = 0;

	virtual XRet				read( const XString& name, XString& v ) = 0;
	virtual XRet				read( const XString& name, XWString& v ) = 0;

	virtual XRet				readSectionBegin( const XString& name ) = 0;
	virtual XRet				readSectionEnd() = 0;
};
X_DefSmartPointer( XInputArchive );

class X_API XOutputArchive
	: public XRefObject
{
public:
	virtual ~XOutputArchive() {}

	virtual XUInt32				getVersion() const = 0;

	virtual const XString&		getTypeName() const = 0;
    
    // save archive to a file.
    virtual XRet                save( const XString& name ) = 0;
    // save archive to a stream.
    virtual XRet                save( std::ostream& s ) = 0;
    
	virtual XRet				write( const XString& name, XBool v ) = 0;
	virtual XRet				write( const XString& name, XFloat v ) = 0;
	virtual XRet				write( const XString& name, XDouble v ) = 0;
	virtual XRet				write( const XString& name, XLong v ) = 0;
	virtual XRet				write( const XString& name, XULong v ) = 0;

	virtual XRet				write( const XString& name, XInt8 v ) = 0;
	virtual XRet				write( const XString& name, XInt16 v ) = 0;
	virtual XRet				write( const XString& name, XInt32 v ) = 0;
	virtual XRet				write( const XString& name, XInt64 v ) = 0;

	virtual XRet				write( const XString& name, XUInt8 v ) = 0;
	virtual XRet				write( const XString& name, XUInt16 v ) = 0;
	virtual XRet				write( const XString& name, XUInt32 v ) = 0;
	virtual XRet				write( const XString& name, XUInt64 v ) = 0;

	virtual XRet				write( const XString& name, const XString& v ) = 0;
	virtual XRet				write( const XString& name, const XWString& v ) = 0;

	virtual XRet				writeSectionBegin( const XString& name ) = 0;
	virtual XRet				writeSectionEnd() = 0;
};
X_DefSmartPointer( XOutputArchive );


X_NS_END

#endif // __XARCHIVE_H__