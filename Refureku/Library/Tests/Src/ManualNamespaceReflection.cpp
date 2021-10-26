#include "ManualNamespaceReflection.h"

#include <string_view>	//std::hash<std::string_view>

#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>
#include <Refureku/TypeInfo/Functions/Function.h>
#include <Refureku/TypeInfo/Namespace/Namespace.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>

void third_party_namespace::nested_third_party_namespace::thirdPartyFunc(){}

static rfk::Function const& getFunction_thirdPartyFunc() noexcept
{
	static rfk::Function func("thirdPartyFunc",
							  std::hash<std::string_view>()("third_party_namespace::nested_third_party_namespace::thirdPartyFunc"),
							  rfk::getType<void>(),
							  new rfk::NonMemberFunction<void()>(&third_party_namespace::nested_third_party_namespace::thirdPartyFunc),
							  rfk::EFunctionFlags::Default);

	return func;
}

static rfk::NamespaceFragment const& getNamespaceFragment_nested_third_party_namespace() noexcept
{
	static bool initialized = false;
	static rfk::NamespaceFragment fragment("nested_third_party_namespace",
										   std::hash<std::string_view>()("third_party_namespace::nested_third_party_namespace"));
	if (!initialized)
	{
		initialized = true;

		fragment.setNestedEntitiesCapacity(1u);
		fragment.addNestedEntity(&getFunction_thirdPartyFunc());
	}

	return fragment;
}

//Register to database
rfk::NamespaceFragmentRegisterer nested_third_party_namespace_registerer(getNamespaceFragment_nested_third_party_namespace(), false);

template <>
rfk::Enum const* rfk::getEnum<third_party_namespace::ThirdPartyEnum>() noexcept
{
	static rfk::Enum enumMetadata("ThirdPartyEnum",
								  std::hash<std::string_view>()("third_party_namespace::ThirdPartyEnum"),
								  rfk::getArchetype<int>(),
								  nullptr);

	return &enumMetadata;
}

static rfk::NamespaceFragment const& getNamespaceFragment_third_party_namespace() noexcept
{
	static bool initialized = false;
	static rfk::NamespaceFragment fragment("third_party_namespace",
										   std::hash<std::string_view>()("third_party_namespace"));
	if (!initialized)
	{
		initialized = true;

		fragment.setNestedEntitiesCapacity(2u);
		fragment.addNestedEntity(nested_third_party_namespace_registerer.getNamespaceInstance());
		fragment.addNestedEntity(rfk::getEnum<third_party_namespace::ThirdPartyEnum>());
	}

	return fragment;
}

rfk::NamespaceFragmentRegisterer third_party_namespace_registerer(getNamespaceFragment_third_party_namespace(), true);