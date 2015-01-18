set ( IO_FILES
	IO/XDataStream.h
	IO/XDataStream.cpp
	IO/XFileDataStream.h
	IO/XFileDataStream.cpp
	IO/XMemDataStream.h
	IO/XMemDataStream.cpp
)

list( APPEND ALL_FILES ${IO_FILES} )

SOURCE_GROUP("IO" FILES
  ${IO_FILES}
)