#include "Vector3.h"

#include <Refureku/TypeInfo/Archetypes/ArchetypeRegistererAPI.h>

#include "CustomProperties.h"

std::hash<std::string> stringHasher;

template <>
rfk::ArchetypeAPI const* rfk::getArchetypeAPI<Vector3f>() noexcept
{
	static bool				initialized = false;
	static rfk::ClassAPI	type("Vector3f", stringHasher("some_namespace::Vector3<float>"), sizeof(Vector3f), true);

	if (!initialized)
	{
		initialized = true;

		//Add properties to the class
		static CustomProperty vector3fProp(2, 3);
		type.addProperty(&vector3fProp);

		//Register fields
		rfk::FieldAPI* field;
		field = type.addField("x", stringHasher("some_namespace::Vector3<float>::x"), rfk::getType<float>(), rfk::EFieldFlags::Public, offsetof(Vector3f, x), &type);
		field = type.addField("y", stringHasher("some_namespace::Vector3<float>::y"), rfk::getType<float>(), rfk::EFieldFlags::Public, offsetof(Vector3f, y), &type);
		field = type.addField("z", stringHasher("some_namespace::Vector3<float>::z"), rfk::getType<float>(), rfk::EFieldFlags::Public, offsetof(Vector3f, z), &type);

		//Optionally add properties to the fields
		static CustomProperty fieldProp(1, 2);
		field->addProperty(&fieldProp);

		//Register static fields
		/*rfk::StaticFieldAPI* staticField = */type.addStaticField("exampleStaticField", stringHasher("some_namespace::Vector3<float>::exampleStaticField"), rfk::getType<float>(), rfk::EFieldFlags::Public | rfk::EFieldFlags::Static, &some_namespace::Vector3<float>::exampleStaticField, &type);


		//Register methods
		/*rfk::MethodAPI* method = */type.addMethod("sqrSize", stringHasher("some_namespace::Vector3<float>::sqrSize()"), rfk::getType<float>(), 
											 new rfk::MemberFunction<Vector3f, float()>(&Vector3f::sqrSize),
											 rfk::EMethodFlags::Public | rfk::EMethodFlags::Inline | rfk::EMethodFlags::Const);

		//Register static methods
		rfk::StaticMethodAPI* staticMethod = type.addStaticMethod("dot", stringHasher("some_namespace::Vector3<float>::dot(Vector3 const&, Vector3 const&)"), rfk::getType<float>(),
																  new rfk::NonMemberFunction<float(Vector3f const&, Vector3f const&)>(&Vector3f::dot),
																  rfk::EMethodFlags::Public | rfk::EMethodFlags::Static | rfk::EMethodFlags::Inline);

		staticMethod->setParametersCapacity(2u);
		staticMethod->addParameter("lhs",  0u, rfk::getType<Vector3f const&>());
		staticMethod->addParameter("rhs",  0u, rfk::getType<Vector3f const&>());
	}

	return &type;
}

//Register the class to the database (note that it is not registered in any namespace, so it's accessible at file level)
rfk::ArchetypeRegistererAPI vector3fRegisterer = *rfk::getArchetypeAPI<Vector3f>();