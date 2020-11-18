#pragma once

/**
*	Source file: D:\Prog\GP3\PLA\Refureku\Refureku\Library\Include\Refureku\TypeInfo\Properties\PropertySettings.h
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


#define __RFK2708994343965683583u_GenerateParentsMetadata	\
	type.directParents.reserve(1);	\
	type.addToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));	\

#define __RFK2708994343965683583u_GenerateFieldsMetadata	\
	registerChild<PropertySettings>(&type);	\

#define __RFK2708994343965683583u_GenerateFieldHelperMethods	\
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

#define __RFK2708994343965683583u_GenerateMethodsMetadata	\

#define __RFK2708994343965683583u_GenerateArchetypeProperties	\
	type.properties.reserve(1);static_assert(std::is_base_of_v<rfk::Property, PropertySettings>, "[Refureku] Can't attach PropertySettings property to PropertySettings as it doesn't inherit from rfk::Property.");static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Struct) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a struct");static PropertySettings property_PropertySettings_PropertySettings_0_2708994343965683583{rfk::EEntityKind::Struct | rfk::EEntityKind::Class};type.properties.emplace_back(&property_PropertySettings_PropertySettings_0_2708994343965683583); 

#define __RFK2708994343965683583u_GenerateDefaultInstantiatorSetup	\
	type.setDefaultInstantiator(&rfk::defaultInstantiator<PropertySettings>);

#define __RFK2708994343965683583u_GetTypeDeclaration	\
	__RFK2708994343965683583u_GenerateFieldHelperMethods	\
	public:	\
		inline static rfk::Struct const& staticGetArchetype() noexcept;	\
		rfk::Struct const& getArchetype() const noexcept override { return PropertySettings::staticGetArchetype(); }

#ifdef KODGEN_PARSING
#define __RFK2708994343965683583u_GetTypeDefinition
#else
#define __RFK2708994343965683583u_GetTypeDefinition	\
		inline rfk::Struct const& PropertySettings::staticGetArchetype() noexcept	\
		{	\
			static bool			initialized = false;	\
			static rfk::Struct	type("PropertySettings", 2708994343965683583u, sizeof(PropertySettings));	\
			\
			if (!initialized)	\
			{	\
				initialized = true;	\
			\
				__RFK2708994343965683583u_GenerateArchetypeProperties	\
				__RFK2708994343965683583u_GenerateParentsMetadata	\
					\
				__RFK2708994343965683583u_GenerateFieldsMetadata	\
				__RFK2708994343965683583u_GenerateDefaultInstantiatorSetup	\
				__RFK2708994343965683583u_GenerateMethodsMetadata	\
			}	\
			\
			return type;	\
		}

#endif
#define __RFK2708994343965683583u_RegisterArchetype	\
	private:	\
		static inline rfk::ArchetypeRegisterer __rfkArchetypeRegisterer = &staticGetArchetype();


#define __RFK2708994343965683583u_NativeProperties	\
	public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Struct | rfk::EEntityKind::Class;virtual rfk::EEntityKind getTargetEntityKind() const noexcept override { return targetEntityKind; }	\
	

#ifdef KODGEN_PARSING
#define PropertySettings_GENERATED
#else
#define PropertySettings_GENERATED	\
	friend rfk::Struct;	\
	friend rfk::hasField___rfkArchetypeRegisterer<PropertySettings, rfk::ArchetypeRegisterer>;	\
	__RFK2708994343965683583u_GetTypeDeclaration	\
	__RFK2708994343965683583u_RegisterArchetype	\
	__RFK2708994343965683583u_NativeProperties	\
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
	__RFK2708994343965683583u_GetTypeDefinition	\
	__RFKNativeProperties_GENERATED	\


