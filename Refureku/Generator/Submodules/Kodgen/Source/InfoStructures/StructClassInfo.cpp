#include "InfoStructures/StructClassInfo.h"

using namespace kodgen;

StructClassInfo::StructClassInfo() noexcept:
	EntityInfo(),
	qualifiers{ false }
{
	initContainers();
}

StructClassInfo::StructClassInfo(std::string&& entityName, PropertyGroup&& propertyGroup, EType&& entityType) noexcept:
	EntityInfo(std::forward<std::string>(entityName), std::forward<PropertyGroup>(propertyGroup), std::forward<EType>(entityType)),
	qualifiers{ false }
{
	initContainers();
}

void StructClassInfo::initContainers() noexcept
{
	parents.reserve(3u);
	parents.emplace(EAccessSpecifier::Public, std::vector<TypeInfo>());
	parents.emplace(EAccessSpecifier::Protected, std::vector<TypeInfo>());
	parents.emplace(EAccessSpecifier::Private, std::vector<TypeInfo>());

	fields.reserve(3u);
	fields.emplace(EAccessSpecifier::Public, std::vector<FieldInfo>());
	fields.emplace(EAccessSpecifier::Protected, std::vector<FieldInfo>());
	fields.emplace(EAccessSpecifier::Private, std::vector<FieldInfo>());

	methods.reserve(3u);
	methods.emplace(EAccessSpecifier::Public, std::vector<MethodInfo>());
	methods.emplace(EAccessSpecifier::Protected, std::vector<MethodInfo>());
	methods.emplace(EAccessSpecifier::Private, std::vector<MethodInfo>());
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, StructClassInfo const& structClassInfo) noexcept
{
	out_stream << (structClassInfo.entityType == EntityInfo::EType::Class ? "Class: " : "Struct: ") << structClassInfo.name;

	//Properties
	out_stream << " " << structClassInfo.properties << std::endl;

	//Fields
	out_stream << " - Fields" << std::endl;
	for (decltype(structClassInfo.fields)::const_iterator it = structClassInfo.fields.cbegin(); it != structClassInfo.fields.cend(); it++)
	{
		out_stream << "   - " << toString(it->first) << std::endl;

		for (FieldInfo const& field : it->second)
		{
			out_stream << "       " << field << std::endl;
		}
	}

	//Methods
	out_stream << " - Methods" << std::endl;
	for (decltype(structClassInfo.methods)::const_iterator it = structClassInfo.methods.cbegin(); it != structClassInfo.methods.cend(); it++)
	{
		out_stream << "   - " << toString(it->first) << std::endl;

		for (MethodInfo const& method : it->second)
		{
			out_stream << "       " << method << std::endl;
		}
	}

	return out_stream;
}