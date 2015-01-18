set ( MATH_FILES
	Math/XMath.h
	Math/XMath.cpp
)

list( APPEND ALL_FILES ${MATH_FILES} )

SOURCE_GROUP("Math" FILES
  ${MATH_FILES}
)