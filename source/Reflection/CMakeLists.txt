set ( REFLECTION_FILES
	Reflection/XMetaObject.h
	Reflection/XMetaClass.h
	Reflection/XMetaClass.cpp
	Reflection/XMetaEnum.h
	Reflection/XMetaEnum.cpp
	Reflection/XMetaField.h
	Reflection/XMetaField.cpp
	Reflection/XMetaMethod.h
	Reflection/XMetaMethod.cpp
	Reflection/XMetaTranslator.h
	Reflection/XMetaPrimitiveTranslator.h
	Reflection/XMetaClassTranslator.h
	Reflection/XMetaSTLTranslator.h
	Reflection/XMetaSystem.h
	Reflection/XMetaSystem.cpp
)

list( APPEND ALL_FILES ${REFLECTION_FILES} )

SOURCE_GROUP("Reflection" FILES
  ${REFLECTION_FILES}
)