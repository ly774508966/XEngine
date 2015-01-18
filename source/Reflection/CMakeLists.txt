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
	Reflection/XMetaType.h
	Reflection/XMetaVariant.h
	Reflection/XMetaTranslator.h
	Reflection/XMetaScalarTranslator.h
	Reflection/XMetaClassTranslator.h
	Reflection/XMetaSTLTranslator.h
)

list( APPEND ALL_FILES ${REFLECTION_FILES} )

SOURCE_GROUP("Reflection" FILES
  ${REFLECTION_FILES}
)