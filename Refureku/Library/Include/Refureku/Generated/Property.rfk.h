#pragma once

/**
*	Source file: D:\Prog\GP3\PLA\Refureku\Refureku\Library\Include\Refureku\TypeInfo\Properties\Property.h
*/

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Class.h>
#include <Refureku/TypeInfo/Archetypes/Enum.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/DefaultEntityRegisterer.h>
#include <Refureku/Misc/DisableWarningMacros.h>


#ifdef __RFK6202377051882013391u_DeclareGetNamespaceFragment
	#undef __RFK6202377051882013391u_DeclareGetNamespaceFragment
#endif

#define __RFK6202377051882013391u_DeclareGetNamespaceFragment inline rfk::NamespaceFragment const& getNamespaceFragment6202377051882013391u_10047156167478885416() noexcept;

#ifdef __RFK6202377051882013391u_DefineGetNamespaceFragment
	#undef __RFK6202377051882013391u_DefineGetNamespaceFragment
#endif

#define __RFK6202377051882013391u_DefineGetNamespaceFragment	\
	inline rfk::NamespaceFragment const& getNamespaceFragment6202377051882013391u_10047156167478885416() noexcept	\
	{	\
		static rfk::NamespaceFragment	fragment("rfk", 6202377051882013391u);	\
		static bool						initialized = false;	\
		if (!initialized)	\
		{	\
			initialized = true;	\
			fragment.nestedEntities.reserve(1u);	\
			fragment.nestedEntities.emplace_back(&rfk::Property::staticGetArchetype());	\
		}	\
	return fragment;	\
	}

#ifdef __RFK6202377051882013391u_RegisterNamespace
	#undef __RFK6202377051882013391u_RegisterNamespace
#endif

#define __RFK6202377051882013391u_RegisterNamespace	\
	inline rfk::NamespaceFragmentRegisterer namespaceFragmentRegisterer6202377051882013391u_10047156167478885416 = rfk::NamespaceFragmentRegisterer("rfk", 6202377051882013391u, &getNamespaceFragment6202377051882013391u_10047156167478885416(), true);

#ifdef __RFK6202377051882013391u_GENERATED
	#undef __RFK6202377051882013391u_GENERATED
#endif

#ifdef KODGEN_PARSING
#define __RFK6202377051882013391u_GENERATED
#else
#define __RFK6202377051882013391u_GENERATED	\
	namespace rfk::generated {	\
	__RFK6202377051882013391u_DeclareGetNamespaceFragment	\
	__RFK6202377051882013391u_RegisterNamespace	\
	__RFK6202377051882013391u_DefineGetNamespaceFragment	\
	}

#endif

#define __RFK12037051384882068683u_GenerateParentsMetadata	\
	type.directParents.reserve(1);	\
	type.__RFKaddToParents<rfk::Object>(static_cast<rfk::EAccessSpecifier>(1));	\

#define __RFK12037051384882068683u_GenerateFieldsMetadata	\
	__RFKregisterChild<Property>(&type);	\

#define __RFK12037051384882068683u_GenerateFieldHelperMethods	\
private:	\
	template <typename ParentType, typename ChildType>	\
	static constexpr void __RFKrecurseRegisterChild([[maybe_unused]] rfk::Struct* childArchetype)	\
	{	\
		if constexpr (rfk::isReflectedClass<ParentType>)	\
		{	\
			ParentType::template __RFKregisterChild<ChildType>(childArchetype);	\
		}	\
	}	\
public:	\
	template <typename ChildType>	\
	static void __RFKregisterChild(rfk::Struct* childArchetype) noexcept	\
	{	\
		__RFKrecurseRegisterChild<rfk::Object, ChildType>(childArchetype);	\
		rfk::Struct const& thisArchetype = staticGetArchetype();	\
		if (childArchetype != &thisArchetype)	\
		{	\
			const_cast<rfk::Struct&>(thisArchetype).children.insert(childArchetype);	\
		}	\
	}

#define __RFK12037051384882068683u_GenerateMethodsMetadata	\
	type.__RFKaddRequiredMethods<Property>();	\

#define __RFK12037051384882068683u_GenerateArchetypeProperties	\
	

#define __RFK12037051384882068683u_GetTypeDeclaration	\
	__RFK12037051384882068683u_GenerateFieldHelperMethods	\
	public:	\
		inline static rfk::Struct const& staticGetArchetype() noexcept;	\
		rfk::Struct const& getArchetype() const noexcept override { return Property::staticGetArchetype(); }

#ifdef KODGEN_PARSING
#define __RFK12037051384882068683u_GetTypeDefinition
#else
#define __RFK12037051384882068683u_GetTypeDefinition	\
		inline rfk::Struct const& rfk::Property::staticGetArchetype() noexcept	\
		{	\
			static bool			initialized = false;	\
			static rfk::Struct	type("Property", 12037051384882068683u, sizeof(Property));	\
			\
			if (!initialized)	\
			{	\
				initialized = true;	\
			\
				__RFK12037051384882068683u_GenerateArchetypeProperties	\
				__RFK12037051384882068683u_GenerateParentsMetadata	\
					\
				__RFK12037051384882068683u_GenerateFieldsMetadata	\
				__RFK12037051384882068683u_GenerateMethodsMetadata	\
			}	\
			\
			return type;	\
		}

#endif
#define __RFK12037051384882068683u_DefaultInstantiateDefinition	\
	private:	\
		template <typename T>	\
		static void* __RFKinstantiate() noexcept	\
		{	\
			if constexpr (std::is_default_constructible_v<T>)	\
				return new T();	\
			else	\
				return nullptr;	\
		}

#define __RFK12037051384882068683u_RegisterArchetype	\
	private:	\
		static inline rfk::ArchetypeRegisterer __rfkArchetypeRegisterer;


#ifdef KODGEN_PARSING
#define Property_GENERATED
#else
#define Property_GENERATED	\
	friend rfk::Struct;	\
	friend rfk::hasField___rfkArchetypeRegisterer<Property, rfk::ArchetypeRegisterer>;	\
	__RFK12037051384882068683u_DefaultInstantiateDefinition	\
	__RFK12037051384882068683u_GetTypeDeclaration	\
	__RFK12037051384882068683u_RegisterArchetype	\
	private:

#endif

#ifdef File_GENERATED
	#undef File_GENERATED
#endif

#ifdef File_GENERATED
	#undef File_GENERATED
#endif

#define File_GENERATED	\
	__RFK12037051384882068683u_GetTypeDefinition	\
	__RFK6202377051882013391u_GENERATED	\


