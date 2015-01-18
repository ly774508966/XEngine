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

#ifndef __XFILEDATASTREAM_H__
#define __XFILEDATASTREAM_H__

#include "XDataStream.h"

X_NS_BEGIN

class X_API XFileInputDataStream
: public XInputDataStream
{
public:
    
    XFileInputDataStream();
    ~XFileInputDataStream();
    
    XRet                        open( const XString& strName );
    XRet                        open( FILE* pkFile );
    
    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close();
    
    /** Read the requisite number of bytes from the stream, stopping at the end of the file. */
    virtual XSize               read( XVoid* pkBuffer, XSize uiNumOfBytesToRead );
    
    /** Repositions the read point to a specified byte. */
    virtual XRet				seek( XSize offset, eSeekMode mode );
    
    /** Returns the current byte offset from beginning */
    virtual XSize				tell() const;
    
    /** Returns true if the stream has reached the end. */
    virtual XBool				eof() const;
    
    XBool						isError() const { return m_pkFile == nullptr || ( ferror( m_pkFile ) != 0 ); }
    
protected:
    FILE*                       m_pkFile;
};


class X_API XFileOutputDataStream
: public XOutputDataStream
{
public:
    
    XFileOutputDataStream();
    ~XFileOutputDataStream();
    
    XRet                        open( const XString& strName, XBool bAppend = false );
    XRet                        open( FILE* pkFile );
    XBool						isError() const { return m_pkFile == nullptr || ( ferror( m_pkFile ) != 0 ); }
    
    /** Close the stream; this makes further operations invalid. */
    virtual XVoid				close();
    
    /** Repositions the read point to a specified byte. */
    virtual XRet				seek( XSize offset, eSeekMode mode );
    
    /** Returns the current byte offset from beginning */
    virtual XSize				tell() const;
    
    /** Returns true if the stream has reached the end. */
    virtual XBool				eof() const;
    
    virtual XVoid               flush();
    
    /** Write the requisite number of bytes to the stream. */
    virtual XSize               write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite );
    
protected:
    FILE*                       m_pkFile;
};


//------------------------------------------------------------------------------
X_FORCEINLINE XSize XFileInputDataStream::read( XVoid* pkBuffer, XSize uiNumOfBytesToRead )
{
    X_RET_VAL_IF( !m_pkFile, 0 );
    
    return fread( pkBuffer, 1, uiNumOfBytesToRead, m_pkFile );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XRet XFileInputDataStream::seek( XSize offset, eSeekMode mode )
{
    if ( m_pkFile )
    {
        return ( fseek( m_pkFile, offset, mode ) == 0 ) ? X_SUCCESS : X_ERROR;
    }
    
    return X_ERROR;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XSize XFileInputDataStream::tell() const
{
    return m_pkFile ? ftell( m_pkFile ) : 0;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XBool XFileInputDataStream::eof() const
{
    return m_pkFile ? ( feof( m_pkFile ) != 0 ) : true;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XFileInputDataStream::close()
{
    if ( m_pkFile )
    {
        fclose( m_pkFile );
        m_pkFile = nullptr;
    }
}

//------------------------------------------------------------------------------
X_FORCEINLINE XRet XFileOutputDataStream::seek( XSize offset, eSeekMode mode )
{
    if ( m_pkFile )
    {
        return ( fseek( m_pkFile, offset, mode ) == 0 ) ? X_SUCCESS : X_ERROR;
    }
    
    return X_ERROR;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XSize XFileOutputDataStream::tell() const
{
    return m_pkFile ? ftell( m_pkFile ) : 0;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XBool XFileOutputDataStream::eof() const
{
    return m_pkFile ? ( feof( m_pkFile ) != 0 ) : true;
}

//------------------------------------------------------------------------------
X_FORCEINLINE XVoid XFileOutputDataStream::close()
{
    if ( m_pkFile )
    {
        fclose( m_pkFile );
        m_pkFile = nullptr;
    }
}

X_FORCEINLINE XVoid XFileOutputDataStream::flush()
{
    X_RET_IF( !m_pkFile );
    fflush( m_pkFile );
}

//------------------------------------------------------------------------------
X_FORCEINLINE XSize XFileOutputDataStream::write( const XVoid* pkBuffer, XSize uiNumOfBytesToWrite )
{
    X_RET_VAL_IF( !m_pkFile, 0 );
    return fwrite( pkBuffer, 1, uiNumOfBytesToWrite, m_pkFile );
}

X_NS_END

#endif // __XFILEDATASTREAM_H__