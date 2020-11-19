#pragma once

/**
*	Source file: D:\Prog\GP3\PLA\Refureku\Refureku\Library\Include\Refureku\TypeInfo\Properties\ParseAllNested.h
*/

#include "EntityMacros.h"

#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Class.h>
#include <Refureku/TypeInfo/Archetypes/Enum.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>


#define __RFK17636175816175907530u_GenerateParentsMetadata	\
	type.directParents.reserve(1);	\
	type.addToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));	\

#define __RFK17636175816175907530u_GenerateFieldsMetadata	\
	registerChild<ParseAllNested>(&type);	\

#define __RFK17636175816175907530u_GenerateFieldHelperMethods	\
private:	\
	template <typename ParentType, typename ChildType>	\
	static constexpr void recurseRegisterChild([[maybe_unused]] rfk::Struct* childArchetype)	\
	{	\
		if constexpr (rfk::isReflectedClass<ParentType>)	\
		{	\
			ParentType::template registerChild<ChildType>(childArchetype);	\
		}	\
	}	\
public:	\
	template <typename ChildType>	\
	static void registerChild(rfk::Struct* childArchetype) noexcept	\
	{	\
		recurseRegisterChild<rfk::Property, ChildType>(childArchetype);	\
		rfk::Struct const& thisArchetype = staticGetArchetype();	\
		if (childArchetype != &thisArchetype)	\
		{	\
			const_cast<rfk::Struct&>(thisArchetype).children.insert(childArchetype);	\
		}	\
	}

#define __RFK17636175816175907530u_GenerateMethodsMetadata	\

#define __RFK17636175816175907530u_GenerateArchetypeProperties	\
	type.properties.reserve(1);static_assert(std::is_base_of_v<rfk::Property, ParseAllNested>, "[Refureku] Can't attach PropertySettings property to ParseAllNested as it doesn't inherit from rfk::Property.");static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Struct) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a struct");static PropertySettings property_ParseAllNested_PropertySettings_0_17636175816175907530{rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct};type.properties.emplace_back(&property_ParseAllNested_PropertySettings_0_17636175816175907530); 

#define __RFK17636175816175907530u_GenerateDefaultInstantiatorSetup	\
	type.setDefaultInstantiator(&rfk::defaultInstantiator<ParseAllNested>);

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
				__RFK17636175816175907530u_GenerateDefaultInstantiatorSetup	\
				__RFK17636175816175907530u_GenerateMethodsMetadata	\
			}	\
			\
			return type;	\
		}

#endif
#define __RFK17636175816175907530u_RegisterArchetype	\
	private:	\
		static inline rfk::ArchetypeRegisterer __rfkArchetypeRegisterer = &staticGetArchetype();


#define __RFK17636175816175907530u_NativeProperties	\
	public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct;virtual rfk::EEntityKind getTargetEntityKind() const noexcept override { return targetEntityKind; }	\
	

#ifdef KODGEN_PARSING
#define ParseAllNested_GENERATED
#else
#define ParseAllNested_GENERATED	\
	friend rfk::Struct;	\
	friend rfk::hasField___rfkArchetypeRegisterer<ParseAllNested, rfk::ArchetypeRegisterer>;	\
	__RFK17636175816175907530u_GetTypeDeclaration	\
	__RFK17636175816175907530u_RegisterArchetype	\
	__RFK17636175816175907530u_NativeProperties	\
	private:

#endif

#ifdef __RFKNativeProperties_GENERATED
	#undef __RFKNativeProperties_GENERATED
#endif

#define __RFKNativeProperties_GENERATED	\
	

#ifdef File_GENERATED
	#undef File_GENERATED
#endif
#define File_GENERATED	\
	__RFK17636175816175907530u_GetTypeDefinition	\
	__RFKNativeProperties_GENERATED	\


