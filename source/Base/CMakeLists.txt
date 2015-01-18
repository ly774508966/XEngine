set ( BASE_FILES
	Base/XConfig.h
	Base/XVersion.h
	Base/XPlatform.h
	Base/XPreDef.h
	Base/XTypes.h
	Base/XUtils.h
	Base/XSmartPointer.h
	Base/XStringUtil.h
	Base/XStringUtil.cpp
	Base/XPath.h
	Base/XPath.cpp
	Base/XLogger.h
	Base/XLogger.cpp
	)

if (WIN32)
	list ( APPEND BASE_FILES
		Base/XPlatform_WIN.cpp
		)
elseif(APPLE)
	list ( APPEND BASE_FILES
		Base/XPlatform_MAC.mm
		)
endif()

list ( APPEND ALL_FILES ${BASE_FILES} )

SOURCE_GROUP("Base" FILES
  ${BASE_FILES}
)