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

#include "XMemDataStream.h"

X_NS_BEGIN


//------------------------------------------------------------------------------
XMemoryInputDataStream::XMemoryInputDataStream( const XVoid* pkData, XSize size )
: m_pData( (const XChar*)pkData )
, m_pPos( m_pData )
, m_pEnd( m_pData + size )
{
    m_uiSize = size;
    assert( m_pData );
    assert( m_pEnd >= m_pData );
}

//------------------------------------------------------------------------------
XMemoryInputDataStream::~XMemoryInputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XSize XMemoryInputDataStream::read( XVoid* pkBuffer, XSize uiNumOfBytesToRead )
{
    X_RET_VAL_IF( !m_pData, 0 );
    
    assert( pkBuffer );
    
    XSize cnt = uiNumOfBytesToRead;
    
    // Read over end of memory?
    if ( m_pPos + cnt > m_pEnd )
    {
        cnt = m_pEnd - m_pPos;
    }
    
    X_RET_VAL_IF( cnt == 0, 0 );
    
    assert ( cnt <= uiNumOfBytesToRead );
    
    memcpy( pkBuffer, m_pPos, cnt );
    
    m_pPos += cnt;
    
    return cnt;
}

//------------------------------------------------------------------------------
XRet XMemoryInputDataStream::seek( XSize offset, XStreamSeekMode mode )
{
    X_RET_VAL_IF( !m_pData, X_ERROR );
    
    const XChar* pkStart = ( mode == XStreamSeekMode::SET ) ? m_pData : ( mode == XStreamSeekMode::CUR ) ? m_pPos : m_pEnd;
    const XChar* pkTarget = pkStart + offset;
    if ( pkTarget >= m_pData
        && pkTarget <= m_pEnd )
    {
        m_pPos = pkTarget;
        return X_SUCCESS;
    }
    
    return X_ERROR;
}

XSize getCapacity( XSize cur, XSize need )
{
    X_RET_VAL_IF( cur >= need, cur );
    XSize capacity = cur ? ( cur * 2 ) : 32;
    while ( capacity <= need )
    {
        capacity *= 2;
    }
    return capacity;
}

//------------------------------------------------------------------------------
XMemoryOutputDataStream::XMemoryOutputDataStream( XSize size )
: m_pData( nullptr )
, m_uiSize( 0 )
, m_uiCapacity( size )
{
}

//------------------------------------------------------------------------------
XMemoryOutputDataStream::~XMemoryOutputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XSize XMemoryOutputDataStream::write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite )
{
    assert( pkBuffer && uiNumOfBytesToWrite );
    
    XBool bNeedResize = false;
    XSize uiNeed = m_uiSize + uiNumOfBytesToWrite;
    if ( uiNeed > m_uiCapacity )
    {
        m_uiCapacity = m_uiCapacity ? ( m_uiCapacity * 2 ) : 32;
        while ( uiNeed > m_uiCapacity )
        {
            m_uiCapacity *= 2;
        }
        
        bNeedResize = true;
    }
    
    if ( !m_pData
        || bNeedResize )
    {
        XChar* pkData = X_NEW XChar[ m_uiCapacity ];
        assert( pkData );
        
        if ( m_pData
            && m_uiSize )
        {
            // copy old data to new buff.
            memcpy( pkData, m_pData, m_uiSize );
            // free old buff.
            X_SAFE_DEL_ARR( m_pData );
        }
        
        m_pData = pkData;
    }
    
    assert( m_pData );
    
    memcpy( m_pData + m_uiSize, pkBuffer, uiNumOfBytesToWrite );
    m_uiSize += uiNumOfBytesToWrite;
    return uiNumOfBytesToWrite;
}

X_NS_END