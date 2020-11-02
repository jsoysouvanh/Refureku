#pragma once

/**
*	Source file: D:\Prog\GP3\PLA\Refureku\Refureku\Library\Include\Refureku\TypeInfo\Properties\ParseAllNested.h
*/

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Class.h>
#include <Refureku/TypeInfo/Archetypes/Enum.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/Misc/DisableWarningMacros.h>


#define __RFK17636175816175907530u_GenerateParentsMetadata	\
	type.directParents.reserve(1);	\
	type.__RFKaddToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));	\

#define __RFK17636175816175907530u_GenerateFieldsMetadata	\
	__RFKregisterChild<ParseAllNested>(&type);	\

#define __RFK17636175816175907530u_GenerateFieldHelperMethods	\
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
		__RFKrecurseRegisterChild<rfk::Property, ChildType>(childArchetype);	\
		rfk::Struct const& thisArchetype = staticGetArchetype();	\
		if (childArchetype != &thisArchetype)	\
		{	\
			const_cast<rfk::Struct&>(thisArchetype).children.insert(childArchetype);	\
		}	\
	}

#define __RFK17636175816175907530u_GenerateMethodsMetadata	\
	type.__RFKaddRequiredMethods<ParseAllNested>();	\

#define __RFK17636175816175907530u_GenerateArchetypeProperties	\
	

#define __RFK17636175816175907530u_GetTypeDeclaration	\
	__RFK17636175816175907530u_GenerateFieldHelperMethods	\
	public:	\
		inline static rfk::Struct const& staticGetArchetype() noexcept;	\
		rfk::Struct const& getArchetype() const noexcept override { return ParseAllNested::staticGetArchetype(); }

#ifdef KODGEN_PARSING
#define __RFK17636175816175907530u_GetTypeDefinition
#else
#define __RFK17636175816175907530u_GetTypeDefinition	\
		inline rfk::Struct const& ParseAllNested::staticGetArchetype() noexcept	\
		{	\
			static bool			initialized = false;	\
			static rfk::Struct	type("ParseAllNested", 17636175816175907530u, sizeof(ParseAllNested));	\
			\
			if (!initialized)	\
			{	\
				initialized = true;	\
			\
				__RFK17636175816175907530u_GenerateArchetypeProperties	\
				__RFK17636175816175907530u_GenerateParentsMetadata	\
					\
				__RFK17636175816175907530u_GenerateFieldsMetadata	\
				__RFK17636175816175907530u_GenerateMethodsMetadata	\
			}	\
			\
			return type;	\
		}

#endif
#define __RFK17636175816175907530u_DefaultInstantiateDefinition	\
	private:	\
		template <typename T>	\
		static void* __RFKinstantiate() noexcept	\
		{	\
			if constexpr (std::is_default_constructible_v<T>)	\
				return new T();	\
			else	\
				return nullptr;	\
		}

#define __RFK17636175816175907530u_RegisterArchetype	\
	private:	\
		static inline rfk::ArchetypeRegisterer __rfkArchetypeRegisterer = &staticGetArchetype();


#ifdef KODGEN_PARSING
#define ParseAllNested_GENERATED
#else
#define ParseAllNested_GENERATED	\
	friend rfk::Struct;	\
	friend rfk::hasField___rfkArchetypeRegisterer<ParseAllNested, rfk::ArchetypeRegisterer>;	\
	__RFK17636175816175907530u_DefaultInstantiateDefinition	\
	__RFK17636175816175907530u_GetTypeDeclaration	\
	__RFK17636175816175907530u_RegisterArchetype	\
	private:

#endif

#ifdef File_GENERATED
	#undef File_GENERATED
#endif

#ifdef File_GENERATED
	#undef File_GENERATED
#endif

#define File_GENERATED	\
	__RFK17636175816175907530u_GetTypeDefinition	\


