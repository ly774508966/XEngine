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

#ifndef __XDATASTREAM_H__
#define __XDATASTREAM_H__

#include "Base/XPreDef.h"
#include "Base/XSmartPointer.h"

X_NS_BEGIN

enum eAccessMode
{
    READ	=	X_BIT( 0 ),
    WRITE	=	X_BIT( 1 ),
    READ_WRITE = READ | WRITE,
};

enum class XStreamSeekMode
{
    //! value from stdio.h
    //#define SEEK_CUR    1
    //#define SEEK_END    2
    //#define SEEK_SET    0
    SET = 0,
    CUR = 1,
    END = 2,
};

class X_API XInputDataStream
: public XRefObject
{
protected:
    XSize                       m_uiSize;
    
    XInputDataStream()
    : m_uiSize( 0 )
    {
    }
public:
    
    XSize                       getSize() const { return m_uiSize; }
    
    XString                     getLine( XBool trimAfter = true );
    
    /** Returns a string containing the entire stream. */
    virtual XString             getAsString();
    
    virtual const XByte*        getData( XBool& bNeedDel, XSize* pSize = nullptr ) const;
    
    /** Skip a defined number of bytes. This can also be a negative value, in which case
     the file pointer rewinds a defined number of bytes. */
    XRet                        skip( XSize n );
    
    //! Streaming operators
    template<typename T>
    XInputDataStream&			operator >> ( T& val );
    
    /** Read the requisite number of bytes from the stream, stopping at the end of the file. */
    virtual XSize               read( XVoid* pkBuffer, XSize uiNumOfBytesToRead ) = 0;
    
    
    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close() = 0;
    
    
    /** Repositions the read point to a specified byte. */
    virtual XRet				seek( XSize offset, XStreamSeekMode mode = XStreamSeekMode::CUR ) = 0;
    
    
    /** Returns the current byte offset from beginning */
    virtual XSize				tell() const = 0;
    
    /** Returns true if the stream has reached the end. */
    virtual XBool				eof() const = 0;
};
X_DefSmartPointer( XInputDataStream );


//------------------------------------------------------------------------------
class X_API XOutputDataStream
: public XRefObject
{
public:

    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close() = 0;
    
    // Flushes this output stream and forces any buffered output bytes to be written out.
    virtual XVoid               flush() = 0;
    
    /** Write the requisite number of bytes to the stream. */
    virtual XSize               write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite ) = 0;
    
    //! Streaming operators
    template<typename T>
    XOutputDataStream&			operator << ( const T& val );
};
X_DefSmartPointer( XOutputDataStream );

//------------------------------------------------------------------------------
X_FORCEINLINE XRet XInputDataStream::skip( XSize n )
{
    return seek( n, XStreamSeekMode::CUR );
}

//------------------------------------------------------------------------------
template<typename T>
X_FORCEINLINE XInputDataStream& XInputDataStream::operator>>( T& val )
{
    read( (XVoid*&)val, sizeof(T) );
    return *this;
}


//------------------------------------------------------------------------------
template<typename T>
X_FORCEINLINE XOutputDataStream& XOutputDataStream::operator<<( const T& val )
{
    write( (const XVoid*)&val, sizeof(T) );
    return *this;
}

X_NS_END

#endif // __XDATASTREAM_H__