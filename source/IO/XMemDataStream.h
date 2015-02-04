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

#ifndef __XMEMDATASTREAM_H__
#define __XMEMDATASTREAM_H__


#include "XDataStream.h"

X_NS_BEGIN

class X_API XMemoryInputDataStream
: public XInputDataStream
{
public:
    
    XMemoryInputDataStream( const XVoid* pkData, XSize size );
    ~XMemoryInputDataStream();
    
    virtual XString             getAsString() override;

    virtual const XByte*        getData( XBool& bNeedDel, XSize* pSize = nullptr ) const override;

    /** Read the requisite number of bytes from the stream, stopping at the end of the file. */
    virtual XSize               read( XVoid* pkBuffer, XSize uiNumOfBytesToRead ) override;
    
    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close() override;
    
    /** Repositions the read point to a specified byte. */
    virtual XRet				seek( XSize offset, XStreamSeekMode mode = XStreamSeekMode::CUR ) override;
    
    /** Returns the current byte offset from beginning */
    virtual XSize				tell() const override;
    
    /** Returns true if the stream has reached the end. */
    virtual XBool				eof() const override;
    
protected:
    
    //! Pointer to the start of the data area
    const XChar*				m_pData;
    
    //! Pointer to the current position in the memory
    const XChar*				m_pPos;
    
    //! Pointer to the end of the memory
    const XChar*				m_pEnd;
};
X_DefSmartPointer( XMemoryInputDataStream );


//------------------------------------------------------------------------------
class X_API XMemoryOutputDataStream
: public XOutputDataStream
{
public:
    
    // The buffer capacity is initially 32 bytes, though its size increases if necessary.
    XMemoryOutputDataStream( XSize size = 32 );
    ~XMemoryOutputDataStream();
    
    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close() override;
    
    virtual XVoid               flush() override {};
    
    virtual XSize               write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite ) override;
    
    const XVoid*                getData() const { return (XVoid*)m_pData; }

    XSize                       getSize() const { return m_uiSize; }
    XSize                       getCapacity() const { return m_uiCapacity; }

protected:
    
    //! Pointer to the start of the data area
    XChar*                      m_pData;

    XSize                       m_uiSize;
    XSize                       m_uiCapacity;
};
X_DefSmartPointer( XMemoryOutputDataStream );


//------------------------------------------------------------------------------
X_FORCEINLINE const XByte* XMemoryInputDataStream::getData( XBool& bNeedDel, XSize* pSize ) const
{
    bNeedDel = false;
    if ( pSize )
    {
        *pSize = getSize();
    }
    
    return m_pData;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XString XMemoryInputDataStream::getAsString()
{
    return XString( m_pData, m_uiSize );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XMemoryInputDataStream::close()
{
    m_pData = m_pPos = m_pEnd = nullptr;
    m_uiSize = 0;
}


//------------------------------------------------------------------------------
X_FORCEINLINE XSize XMemoryInputDataStream::tell() const
{
    if ( m_pData )
    {
        //m_pData is start, m_pPos is current location
        return m_pPos - m_pData;
    }
    
    return 0;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XBool XMemoryInputDataStream::eof() const
{
    return m_pData ? ( m_pPos >= m_pEnd ) : true;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XMemoryOutputDataStream::close()
{
    X_SAFE_DEL_ARR( m_pData );
    m_pData = nullptr;
    m_uiSize = m_uiCapacity = 0;
}

X_NS_END

#endif // __XMEMDATASTREAM_H__