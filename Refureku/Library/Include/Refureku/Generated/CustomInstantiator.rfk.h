#pragma once

/**
*	Source file: D:\Prog\GP3\PLA\Refureku\Refureku\Library\Include\Refureku\TypeInfo\Properties\CustomInstantiator.h
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


#define __RFK291713889535622996u_GenerateParentsMetadata	\
	type.directParents.reserve(1);	\
	type.__RFKaddToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));	\

#define __RFK291713889535622996u_GenerateFieldsMetadata	\
	__RFKregisterChild<CustomInstantiator>(&type);	\

#define __RFK291713889535622996u_GenerateFieldHelperMethods	\
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

#define __RFK291713889535622996u_GenerateMethodsMetadata	\
	type.__RFKaddRequiredMethods<CustomInstantiator>();	\

#define __RFK291713889535622996u_GenerateArchetypeProperties	\
	type.properties.reserve(1);static_assert(std::is_base_of_v<rfk::Property, CustomInstantiator>, "[Refureku] Can't attach PropertySettings property to CustomInstantiator as it doesn't inherit from rfk::Property.");static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Struct) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a struct");static PropertySettings property_CustomInstantiator_PropertySettings_0_291713889535622996{rfk::EEntityKind::Method};type.properties.emplace_back(&property_CustomInstantiator_PropertySettings_0_291713889535622996); 

#define __RFK291713889535622996u_GetTypeDeclaration	\
	__RFK291713889535622996u_GenerateFieldHelperMethods	\
	public:	\
		inline static rfk::Struct const& staticGetArchetype() noexcept;	\
		rfk::Struct const& getArchetype() const noexcept override { return CustomInstantiator::staticGetArchetype(); }

#ifdef KODGEN_PARSING
#define __RFK291713889535622996u_GetTypeDefinition
#else
#define __RFK291713889535622996u_GetTypeDefinition	\
		inline rfk::Struct const& CustomInstantiator::staticGetArchetype() noexcept	\
		{	\
			static bool			initialized = false;	\
			static rfk::Struct	type("CustomInstantiator", 291713889535622996u, sizeof(CustomInstantiator));	\
			\
			if (!initialized)	\
			{	\
				initialized = true;	\
			\
				__RFK291713889535622996u_GenerateArchetypeProperties	\
				__RFK291713889535622996u_GenerateParentsMetadata	\
					\
				__RFK291713889535622996u_GenerateFieldsMetadata	\
				__RFK291713889535622996u_GenerateMethodsMetadata	\
			}	\
			\
			return type;	\
		}

#endif
#define __RFK291713889535622996u_DefaultInstantiateDefinition	\
	private:	\
		template <typename T>	\
		static void* __RFKinstantiate() noexcept	\
		{	\
			if constexpr (std::is_default_constructible_v<T>)	\
				return new T();	\
			else	\
				return nullptr;	\
		}

#define __RFK291713889535622996u_RegisterArchetype	\
	private:	\
		static inline rfk::ArchetypeRegisterer __rfkArchetypeRegisterer = &staticGetArchetype();


#define __RFK291713889535622996u_NativeProperties	\
	public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Method;virtual rfk::EEntityKind getTargetEntityKind() const noexcept override { return targetEntityKind; }	\
	

#ifdef KODGEN_PARSING
#define CustomInstantiator_GENERATED
#else
#define CustomInstantiator_GENERATED	\
	friend rfk::Struct;	\
	friend rfk::hasField___rfkArchetypeRegisterer<CustomInstantiator, rfk::ArchetypeRegisterer>;	\
	__RFK291713889535622996u_DefaultInstantiateDefinition	\
	__RFK291713889535622996u_GetTypeDeclaration	\
	__RFK291713889535622996u_RegisterArchetype	\
	__RFK291713889535622996u_NativeProperties	\
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
	__RFK291713889535622996u_GetTypeDefinition	\
	__RFKNativeProperties_GENERATED	\


