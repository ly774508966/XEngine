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

#ifndef __XARCHIVEJSON_H__
#define __XARCHIVEJSON_H__

#include "XArchive.h"

X_NS_BEGIN

class X_API XInputArchiveJson
: public XInputArchive
{
    X_DECLARE_NO_COPY_CLASS( XInputArchiveJson );
    
protected:
    XArchiveNodePtr             m_pkRootNode;
    XArchiveNodePtr             m_pkCurNode;
    
public:
    
    XInputArchiveJson();
    ~XInputArchiveJson();
    
    virtual XUInt32				getVersion() const override { return 1; };
    
    virtual const XString&		getTypeName() const override
    {
        static XString s_strType = "JSON";
        return s_strType;
    }

    virtual XRet                load( XInputDataStream* pkStream ) override;
    virtual XRet                load( const XVoid* pkData, XSize size ) override;

    virtual XRet				read( const XString& name, XBool& v ) override;
    virtual XRet				read( const XString& name, XFloat& v ) override;
    virtual XRet				read( const XString& name, XDouble& v ) override;
    virtual XRet				read( const XString& name, XLong& v ) override;
    virtual XRet				read( const XString& name, XULong& v ) override;
    
    virtual XRet				read( const XString& name, XInt8& v ) override;
    virtual XRet				read( const XString& name, XInt16& v ) override;
    virtual XRet				read( const XString& name, XInt32& v ) override;
    virtual XRet				read( const XString& name, XInt64& v ) override;
    
    virtual XRet				read( const XString& name, XUInt8& v ) override;
    virtual XRet				read( const XString& name, XUInt16& v ) override;
    virtual XRet				read( const XString& name, XUInt32& v ) override;
    virtual XRet				read( const XString& name, XUInt64& v ) override;
    
    virtual XRet				read( const XString& name, XString& v ) override;
    virtual XRet				read( const XString& name, XWString& v ) override;
    
    virtual XRet				readSectionBegin( const XString& name ) override;
    virtual XRet				readSectionEnd() override;
};
X_DefSmartPointer( XInputArchiveJson );



//------------------------------------------------------------------------------
class X_API XOutputArchiveJson
: public XOutputArchive
{
    X_DECLARE_NO_COPY_CLASS( XOutputArchiveJson );
    
protected:
    XArchiveNodePtr             m_pkRootNode;
    XArchiveNodePtr             m_pkCurNode;
    
public:
    
    XOutputArchiveJson();
    ~XOutputArchiveJson();
    
    virtual XUInt32				getVersion() const override { return 1; }
    
    virtual const XString&		getTypeName() const
    {
        static XString s_strType = "JSON";
        return s_strType;
    }

    virtual XRet                save( const XString& name ) override;
    virtual XRet                save( std::ostream& s ) override;

    virtual XRet				write( const XString& name, XBool v ) override;
    virtual XRet				write( const XString& name, XFloat v ) override;
    virtual XRet				write( const XString& name, XDouble v ) override;
    virtual XRet				write( const XString& name, XLong v ) override;
    virtual XRet				write( const XString& name, XULong v ) override;
    
    virtual XRet				write( const XString& name, XInt8 v ) override;
    virtual XRet				write( const XString& name, XInt16 v ) override;
    virtual XRet				write( const XString& name, XInt32 v ) override;
    virtual XRet				write( const XString& name, XInt64 v ) override;
    
    virtual XRet				write( const XString& name, XUInt8 v ) override;
    virtual XRet				write( const XString& name, XUInt16 v ) override;
    virtual XRet				write( const XString& name, XUInt32 v ) override;
    virtual XRet				write( const XString& name, XUInt64 v ) override;
    
    virtual XRet				write( const XString& name, const XString& v ) override;
    virtual XRet				write( const XString& name, const XWString& v ) override;
    
    virtual XRet				writeSectionBegin( const XString& name ) override;
    virtual XRet				writeSectionEnd() override;
};
X_DefSmartPointer( XOutputArchiveJson );

X_NS_END

#endif // __XARCHIVEJSON_H__