#include "Vector3.h"

#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>

#include "CustomProperties.h"

std::hash<std::string> stringHasher;

template <>
rfk::Archetype const* rfk::getArchetype<Vector3f>() noexcept
{
	static bool			initialized = false;
	static rfk::Class	type("Vector3f", stringHasher("some_namespace::Vector3<float>"), sizeof(Vector3f), true);

	if (!initialized)
	{
		initialized = true;

		//Add properties to the class
		static CustomProperty vector3fProp(2, 3);
		type.addProperty(&vector3fProp);

		//Register fields
		rfk::Field* field;
		field = type.addField("x", stringHasher("some_namespace::Vector3<float>::x"), rfk::Type::getType<float>(), rfk::EFieldFlags::Public, &type, offsetof(Vector3f, x));
		field = type.addField("y", stringHasher("some_namespace::Vector3<float>::y"), rfk::Type::getType<float>(), rfk::EFieldFlags::Public, &type, offsetof(Vector3f, y));
		field = type.addField("z", stringHasher("some_namespace::Vector3<float>::z"), rfk::Type::getType<float>(), rfk::EFieldFlags::Public, &type, offsetof(Vector3f, z));

		//Optionally add properties to the fields
		static CustomProperty fieldProp(1, 2);
		field->addProperty(&fieldProp);

		//Register static fields
		/*rfk::StaticField* staticField = */type.addStaticField("exampleStaticField", stringHasher("some_namespace::Vector3<float>::exampleStaticField"), rfk::Type::getType<float>(), rfk::EFieldFlags::Public | rfk::EFieldFlags::Static, &type, &some_namespace::Vector3<float>::exampleStaticField);

		//Register methods
		/*rfk::Method* method = */type.addMethod("sqrSize", stringHasher("some_namespace::Vector3<float>::sqrSize()"), rfk::Type::getType<float>(), 
											 std::make_unique<rfk::MemberFunction<Vector3f, float()>>(static_cast<float(Vector3f::*)() const noexcept>(&Vector3f::sqrSize)),
											 rfk::EMethodFlags::Public | rfk::EMethodFlags::Inline | rfk::EMethodFlags::Const);

		//Register static methods
		rfk::StaticMethod* staticMethod = type.addStaticMethod("dot", stringHasher("some_namespace::Vector3<float>::dot(Vector3 const&, Vector3 const&)"), rfk::Type::getType<float>(),
															   std::make_unique<rfk::NonMemberFunction<float(Vector3f const&, Vector3f const&)>>(static_cast<float(*)(Vector3f const&, Vector3f const&)>(&Vector3f::dot)), 
															   rfk::EMethodFlags::Public | rfk::EMethodFlags::Static | rfk::EMethodFlags::Inline);

		staticMethod->parameters.reserve(2);
		staticMethod->addParameter("lhs", rfk::Type::getType<Vector3f const&>())->addParameter("rhs", rfk::Type::getType<Vector3f const&>());
	}

	return &type;
}

//Register the class to the database (note that it is not registered in any namespace, so it's accessible at file level)
rfk::ArchetypeRegisterer vector3fRegisterer = *rfk::getArchetype<Vector3f>();