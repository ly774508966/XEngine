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

#include "XDataStream.h"
#include "Base/XStringUtil.h"

X_NS_BEGIN

//------------------------------------------------------------------------------
XString XInputDataStream::getLine( XBool trimAfter /*= true */ )
{
    XChar tmpBuf[128];
    XString retString;
    XSize readCount;
    XVoid* pBuf = (XVoid*)tmpBuf;
    
    // Keep looping while not hitting delimiter
    while ( (readCount = read( pBuf, 128-1 ) != 0) )
    {
        // Terminate string
        tmpBuf[readCount] = '\0';
        
        XChar* p = strchr(tmpBuf, '\n');
        if (p != 0)
        {
            // Reposition backwards
            skip( (XSize)(p + 1 - tmpBuf - readCount) );
            *p = '\0';
        }
        
        retString += tmpBuf;
        
        if (p != 0)
        {
            // trim off trailing CR if this was a CR/LF entry
            if (retString.length() && retString[retString.length()-1] == '\r')
            {
                retString.erase(retString.length()-1, 1);
            }
            
            // Found terminator, break out
            break;
        }
    }
    
    if (trimAfter)
    {
        XStringUtil::trim( retString );
    }
    
    return retString;
}

//------------------------------------------------------------------------------
XString XInputDataStream::getAsString()
{
    XSize curPos = tell();
    XString strResult;
    XSize size = getSize();
    XByte* pkBuffer = X_NEW XByte[size+1];
    
    seek( 0 );
    size = read( (XVoid*)pkBuffer, size );
    pkBuffer[size] = '\0';
    strResult.append( pkBuffer, size );
    
    X_SAFE_DEL_ARR( pkBuffer );
    
    // restore pos.
    seek( curPos, XStreamSeekMode::SET );
    
    return strResult;
}

//------------------------------------------------------------------------------
const XByte* XInputDataStream::getData( XBool& bNeedDel, XSize* pSize ) const
{
    XSize size = getSize();
    XByte* pData = X_NEW XByte[ size ];
    
    XSize curPos = tell();
    
    XInputDataStream* pkDS = (const_cast<XInputDataStream*>(this));
    pkDS->seek( 0 );
    size = pkDS->read( (XVoid*)pData, size );
    
    // restore pos.
    pkDS->seek( curPos, XStreamSeekMode::SET );
    
    bNeedDel = true;
    if ( pSize ) *pSize = size;
    return pData;
}

X_NS_END