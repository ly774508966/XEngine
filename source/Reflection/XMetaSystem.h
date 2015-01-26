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

#ifndef __XMETASYSTEM_H__
#define __XMETASYSTEM_H__

#include "Base/XPreDef.h"

X_NS_BEGIN

class XMetaClass;
class XMetaEnum;
class X_API XMetaSystem
{
public:
	// < crc32 -- XMetaClass >
    typedef std::map< XUInt32, const XMetaClass* >      TMapMetaClasses;
    typedef std::map< XUInt32, const XMetaEnum* >       TMapMetaEnums;
    
private:
    
    TMapMetaClasses             m_mapAllMetaClasses;
    TMapMetaEnums               m_mapAllMetaEnums;
public:
    
    static XMetaSystem&         getIns() { static XMetaSystem s_kIns; return s_kIns; }
    
    XRet                        registerMetaClass( const XMetaClass* pkMetaClass );
	const XMetaClass*           getMetaClass( const XString& strName ) const;
	const XMetaClass*           getMetaClass( XUInt32 crc32 ) const;
    const TMapMetaClasses&      getAllMetaClasses() const { return m_mapAllMetaClasses; }
    
    
    XRet                        registerMetaEnum( const XMetaEnum* pkMetaEnum );
    const XMetaEnum*            getMetaEnum( const XString& strName ) const;
    const XMetaEnum*            getMetaEnum( XUInt32 crc32 ) const;
    const TMapMetaEnums&        getAllMetaEnums() const { return m_mapAllMetaEnums; }
};

X_NS_END

#endif // __XMETASYSTEM_H__
