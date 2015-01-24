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

#ifndef __XPREDEF_H__
#define __XPREDEF_H__

#define X_NS_NAME       nsXE
#define X_NS_BEGIN		namespace X_NS_NAME {
#define X_NS_END		}


#include <cstdint>
#include <string>
#include <assert.h>
#include <stdarg.h>

#include <list>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>

#include "XConfig.h"
#include "XVersion.h"
#include "XPlatform.h"
#include "XTypes.h"
#include "XUtils.h"


X_NS_BEGIN

class XMetaObject;


class XMetaEnum;
typedef std::map< XUInt32, XString >   TMapMetaEnumElements;
typedef std::map< XString, const XMetaEnum* > TMapMetaEnums;

class XMetaField;
typedef std::map< XString, const XMetaField* > TMapMetaFields;

class XMetaMethod;
typedef std::vector< const XMetaMethod* > TVecMetaMethods;
typedef std::map< XString, TVecMetaMethods > TMapMetaMethods;

template < typename T >
class XMetaClass_T;
class XMetaClass;
typedef std::vector< const XMetaClass* > TVecMetaClasses;
typedef std::map< XString, const XMetaClass* > TMapMetaClasses;

class TMetaNamespace;
typedef std::map< XString, TMetaNamespace* > TMapMetaNamespaces;

X_NS_END

#endif // __XPREDEF_H__