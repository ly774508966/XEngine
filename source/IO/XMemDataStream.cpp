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
XMemoryInputDataStream::XMemoryInputDataStream()
: m_pData( nullptr )
, m_pPos( nullptr )
, m_pEnd( nullptr )
{
}

//------------------------------------------------------------------------------
XMemoryInputDataStream::~XMemoryInputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XRet XMemoryInputDataStream::open( const XVoid* pData, XSize size )
{
    X_RET_VAL_IF( !pData || size == 0, X_ERROR );
    
    m_size = size;
    m_pData = m_pPos = (const XChar*)pData;
    m_pEnd = m_pData + m_size;
    assert( m_pEnd >= m_pPos );
    
    return X_SUCCESS;
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
XRet XMemoryInputDataStream::seek( XSize offset, eSeekMode mode )
{
    X_RET_VAL_IF( !m_pData, X_ERROR );
    
    const XChar* pkStart = ( mode == SET ) ? m_pData : ( mode == CUR ) ? m_pPos : m_pEnd;
    const XChar* pkTarget = pkStart + offset;
    if ( pkTarget >= m_pData
        && pkTarget <= m_pEnd )
    {
        m_pPos = pkTarget;
        return X_SUCCESS;
    }
    
    return X_ERROR;
}


//------------------------------------------------------------------------------
TMemoryOutputDataStream::TMemoryOutputDataStream()
: m_pData( nullptr )
, m_pPos( nullptr )
, m_pEnd( nullptr )
{
}

//------------------------------------------------------------------------------
TMemoryOutputDataStream::~TMemoryOutputDataStream()
{
    close();
}

//------------------------------------------------------------------------------
XRet TMemoryOutputDataStream::open( XSize size, XBool bDynamic /*= false*/ )
{
    X_RET_VAL_IF( size == 0 && !bDynamic, X_ERROR );
    
    m_size = size;
    
    if ( m_size )
    {
        m_pData = X_NEW XChar[m_size];
        m_pPos = m_pData;
        m_pEnd = m_pData + m_size;
    }
    else
    {
        m_pData = m_pPos = m_pEnd = nullptr;
    }
    assert( m_pEnd >= m_pPos );
    
    m_bDynamic = bDynamic;
    
    return X_SUCCESS;
}

//------------------------------------------------------------------------------
XSize TMemoryOutputDataStream::write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite )
{
    X_RET_VAL_IF( !m_pData, 0 );
    
    XSize uiWritten = uiNumOfBytesToWrite;
    // we only allow writing within the extents of allocated memory
    // check for buffer overrun & disallow
    if ( m_pPos + uiWritten > m_pEnd )
    {
        if ( !m_bDynamic )
        {
            uiWritten = m_pEnd - m_pPos;
        }
        else
        {
            XSize offset = m_pPos - m_pData;
            
            // get new need size.
            XSize newSize = m_size ? ( m_size * 2 ) : 128;
            while ( m_pPos + uiWritten > m_pPos + newSize )
            {
                newSize *= 2;
            }
            // realloc memory.
            XChar* pNewData = X_NEW XChar[ newSize ];
            assert( pNewData != nullptr );
            
            if ( m_size )
            {
                assert( m_pData != nullptr && m_pPos != nullptr && m_pEnd != nullptr );
                // copy old data to new buff.
                memcpy( pNewData, m_pData, m_size );
                // free old buff.
                X_SAFE_DEL_ARR( m_pData );
            }
            
            // re pos.
            m_pData = pNewData;
            m_pPos = m_pData + offset;
            m_pEnd = m_pData + newSize;
            
            m_size = newSize;
            
            assert( m_pEnd >= m_pPos );
            assert( m_pPos + uiWritten <= m_pEnd );
        }
    }
    
    X_RET_VAL_IF( uiWritten == 0, X_ERROR );
    
    memcpy( m_pPos, pkBuffer, uiWritten );
    m_pPos += uiWritten;
    return uiWritten;
}

//------------------------------------------------------------------------------
XRet TMemoryOutputDataStream::seek( XSize offset, eSeekMode mode )
{
    X_RET_VAL_IF( !m_pData, X_ERROR );
    
    XChar* pkStart = ( mode == SET ) ? m_pData : ( mode == CUR ) ? m_pPos : m_pEnd;
    XChar* pkTarget = pkStart + offset;
    if ( pkTarget >= m_pData
        && pkTarget <= m_pEnd )
    {
        m_pPos = pkTarget;
        return X_SUCCESS;
    }
    
    return X_ERROR;
}

X_NS_END