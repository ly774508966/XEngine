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

#ifndef __XSMARTPOINTER_H__
#define __XSMARTPOINTER_H__

#include "XPreDef.h"

X_NS_BEGIN


class X_API XRefObject
{
    
protected:
    
    XInt32						m_nRefCount;
    
public:
    virtual ~XRefObject() {}
    
    //! Add new reference to this object.
    XVoid						addRef() { ++m_nRefCount; }
    
    //! Release reference to this object.
    XVoid						release()
    {
        if ( --m_nRefCount <= 0 )
            deleteThis();
    }
    
    XInt32						getRefCount() const { return m_nRefCount; }
    
protected:
    XRefObject()
        : m_nRefCount( 0 )
    {
    }
    
    virtual XVoid				deleteThis() { delete this; }
};


// Smart pointers. The  template T  must be derived from XRefObject.
template < typename T >
class XSmartPointer
{
public:
    // construction and destruction
    XSmartPointer(T* pObject = (T*) 0);
    XSmartPointer(const XSmartPointer& ptr);
    ~XSmartPointer();

    // implicit conversions
    operator T*() const;
    T& operator*() const;
    T* operator->() const;

    // assignment
    XSmartPointer& operator=(const XSmartPointer& ptr);
    XSmartPointer& operator=(T* pObject);

    // comparisons
    bool operator==(T* pObject) const;
    bool operator!=(T* pObject) const;
    bool operator==(const XSmartPointer& ptr) const;
    bool operator!=(const XSmartPointer& ptr) const;

protected:
    // the managed pointer
    T* m_pObject;
};

#define X_DefSmartPointer(classname) \
class classname; \
typedef XSmartPointer<classname> classname##Ptr

// Use for casting a smart pointer of one type to a pointer or smart pointer
// of another type.
#define X_SmartPointerCast(type, smartptr) ((type*) (void*) (smartptr))

//---------------------------------------------------------------------------
template < typename T >
inline XSmartPointer<T >::XSmartPointer(T* pObject)
{
    m_pObject = pObject;
    if (m_pObject)
        m_pObject->addRef();
}
//---------------------------------------------------------------------------
template < typename T >
inline XSmartPointer<T>::XSmartPointer(const XSmartPointer& ptr)
{
    m_pObject = ptr.m_pObject;
    if (m_pObject)
        m_pObject->addRef();
}
//---------------------------------------------------------------------------
template < typename T >
inline XSmartPointer<T>::~XSmartPointer()
{
    if (m_pObject)
        m_pObject->release();
}
//---------------------------------------------------------------------------
template < typename T >
inline XSmartPointer<T>::operator T*() const
{
    return m_pObject;
}
//---------------------------------------------------------------------------
template < typename T >
inline T& XSmartPointer<T>::operator*() const
{
    return *m_pObject;
}
//---------------------------------------------------------------------------
template < typename T >
inline T* XSmartPointer<T>::operator->() const
{
    return m_pObject;
}
//---------------------------------------------------------------------------
template < typename T >
inline XSmartPointer<T>& XSmartPointer<T>::operator=(const XSmartPointer& ptr)
{
    if (m_pObject != ptr.m_pObject)
    {
        if (m_pObject)
            m_pObject->release();
        m_pObject = ptr.m_pObject;
        if (m_pObject)
            m_pObject->addRef();
    }
    return *this;
}
//---------------------------------------------------------------------------
template < typename T >
inline XSmartPointer<T>& XSmartPointer<T>::operator=(T* pObject)
{
    if (m_pObject != pObject)
    {
        if (m_pObject)
            m_pObject->release();
        m_pObject = pObject;
        if (m_pObject)
            m_pObject->addRef();
    }
    return *this;
}
//---------------------------------------------------------------------------
template < typename T >
inline bool XSmartPointer<T>::operator==(T* pObject) const
{
    return (m_pObject == pObject);
}
//---------------------------------------------------------------------------
template < typename T >
inline bool XSmartPointer<T>::operator!=(T* pObject) const
{
    return (m_pObject != pObject);
}
//---------------------------------------------------------------------------
template < typename T >
inline bool XSmartPointer<T>::operator==(const XSmartPointer& ptr) const
{
    return (m_pObject == ptr.m_pObject);
}
//---------------------------------------------------------------------------
template < typename T >
inline bool XSmartPointer<T>::operator!=(const XSmartPointer& ptr) const
{
    return (m_pObject != ptr.m_pObject);
}


X_NS_END

#endif  // __XSMARTPOINTER_H__