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

#ifndef __XENGINE_H__
#define __XENGINE_H__


#include "Base/XPreDef.h"
#include "Base/XStringUtil.h"
#include "Base/XLogger.h"
#include "Base/XPath.h"
#include "Base/XSmartPointer.h"
#include "Base/XUtils.h"

#include "Reflection/XMetaSystem.h"
#include "Reflection/XMetaEnum.h"
#include "Reflection/XMetaClass.h"
#include "Reflection/XMetaField.h"
#include "Reflection/XMetaTranslator.h"
#include "Reflection/XMetaPrimitiveTranslator.h"
#include "Reflection/XMetaClasstranslator.h"
#include "Reflection/XMetaPointertranslator.h"
#include "Reflection/XMetaSTLTranslator.h"
#include "Reflection/XMetaObject.h"
#include "Reflection/XMetaObjectSerializer.h"

#include "IO/XDataStream.h"

#include "IO/XFileDataStream.h"
#include "IO/XMemDataStream.h"

#include "IO/XArchiveXML.h"
#include "IO/XArchiveJson.h"

#endif // __XENGINE_H__