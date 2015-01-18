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

enum eSeekMode
{
    //! value from stdio.h
    //#define SEEK_CUR    1
    //#define SEEK_END    2
    //#define SEEK_SET    0
    SET = 0,
    CUR = 1,
    END = 2,
};

class X_API XDataStream
: public XRefObject
{
protected:
    XSize                       m_size;
    
protected:
    
    XDataStream();
    
public:
    
    XSize                       getSize() const { return m_size; }
    
    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close() = 0;
    
    /** Skip a defined number of bytes. This can also be a negative value, in which case
     the file pointer rewinds a defined number of bytes. */
    virtual XRet				skip( XSize count );
    
    /** Repositions the read point to a specified byte. */
    virtual XRet				seek( XSize pos );
    virtual XRet				seek( XSize offset, eSeekMode mode ) = 0;
    
    /** Returns the current byte offset from beginning */
    virtual XSize				tell() const = 0;
    
    /** Returns true if the stream has reached the end. */
    virtual XBool				eof() const = 0;
};


class X_API XInputDataStream
: public XDataStream
{
public:
    
    XString                     getLine( XBool trimAfter = true );
    
    /** Returns a string containing the entire stream. */
    XString                     getAsString();
    
    //! Streaming operators
    template<typename T>
    XInputDataStream&			operator >> ( T& val );
    
    /** Read the requisite number of bytes from the stream, stopping at the end of the file. */
    virtual XSize               read( XVoid* pkBuffer, XSize uiNumOfBytesToRead ) = 0;
    XRet     					read2( XVoid* pkBuffer, XSize uiNumOfBytesToRead, XSize* uiNumOfBytesRead = nullptr );
};


class X_API XOutputDataStream
: public XDataStream
{
public:
    
    virtual XVoid               flush() = 0;
    
    /** Write the requisite number of bytes to the stream. */
    virtual XSize               write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite ) = 0;
    XRet						write2( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite, XSize* uiNumOfBytesWritten = nullptr );
};


//------------------------------------------------------------------------------
X_FORCEINLINE XRet XDataStream::skip( XSize count )
{
    return seek( count, CUR );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XRet XDataStream::seek( XSize pos )
{
    return seek( pos, SET );
}

//------------------------------------------------------------------------------
template<typename T>
X_FORCEINLINE XInputDataStream& XInputDataStream::operator>>( T& val )
{
    read( (XVoid*&)val, sizeof(T) );
    return *this;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XRet XInputDataStream::read2( XVoid* pkBuffer, XSize uiNumOfBytesToRead, XSize* uiNumOfBytesRead /*= nullptr */ )
{
    XSize uiBytes = read( pkBuffer, uiNumOfBytesToRead );
    if ( uiNumOfBytesRead )
    {
        *uiNumOfBytesRead = uiBytes;
    }
    
    return uiBytes == uiNumOfBytesToRead ? X_SUCCESS : X_ERROR;
}


//------------------------------------------------------------------------------
X_FORCEINLINE XRet XOutputDataStream::write2( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite, XSize* uiNumOfBytesWritten /*= nullptr*/ )
{
    XSize uiBytes = write( pkBuffer, uiNumOfBytesToWrite );
    if ( uiNumOfBytesWritten )
    {
        *uiNumOfBytesWritten = uiBytes;
    }
    
    return uiBytes == uiNumOfBytesToWrite ? X_SUCCESS : X_ERROR;
}

X_NS_END

#endif // __XDATASTREAM_H__