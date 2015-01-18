/********************************************************************
	Project:	Gaea Engine
	Created:	2010/09/15   15:37

	File name:	GeRefObject.h
	
	Author:		Fred( XieFuXiang )
	MSN:		xfxsworld@hotmail.com
	QQ:			18425540
	E-Mail:		xfxsworld@gmail.com
				Http://

	Organization:	
	Copyright (c) 2010-2020 XieFuXiang, All rights reserved.

	Purpose:	
	Version:	1.0
	Histroy:
*********************************************************************/

#ifndef __GeRefObject_h__
#define __GeRefObject_h__

#include "GeEngineCorePrerequisites.h"
#include "GeMemory.h"

namespace nsGE
{

	class CORE_EXPORT GeRefObject
	{

	protected:

		GeInt32						m_nRefCount;

	public:
		virtual ~GeRefObject() {}

		//! Add new reference to this object.
		GeVoid						IncRefCount() { ++m_nRefCount; }

		//! Release reference to this object.
		GeVoid						DecRefCount()
		{
			if ( --m_nRefCount <= 0 )
				DeleteThis();
		}

		GeInt32						GetRefCount() const { return m_nRefCount; }

	protected:
		GeRefObject()
			: m_nRefCount( 0 )
		{
		}

		virtual GeVoid				DeleteThis() { GAEA_DEL( this ); }
	};
}

#endif // __GeRefObject_h__