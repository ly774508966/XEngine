cmake_minimum_required(VERSION 2.8)
PROJECT( XEngine )

include_directories( ${PROJECT_SOURCE_DIR} )

set ( ALL_FILES XEngine.h )

SOURCE_GROUP("" FILES
    XEngine.h
)

include( Base/CMakeLists.txt )
include( Reflection/CMakeLists.txt )
include( IO/CMakeLists.txt )
include( Math/CMakeLists.txt )

ADD_LIBRARY( XEngine
		SHARED
		${ALL_FILES}
)

ADD_LIBRARY( XEngine_Static
		STATIC
		${ALL_FILES}
)

SET_TARGET_PROPERTIES(XEngine PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(XEngine_Static PROPERTIES OUTPUT_NAME "XEngine")
SET_TARGET_PROPERTIES(XEngine_Static PROPERTIES CLEAN_DIRECT_OUTPUT 1)