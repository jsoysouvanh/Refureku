/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_map>

#include <Kodgen/CodeGen/GeneratedCodeTemplate.h>
#include <Kodgen/InfoStructures/EntityInfo.h>

namespace rfk
{
	class GeneratedEntityCodeTemplate : public kodgen::GeneratedCodeTemplate
	{
		private:
			/**
			*	@brief Add a property to the record.
			*	
			*	@param record	Record we add the property to.
			*	@param propName Name of the property to add.
			*	
			*	@return Number of occurences (after insert) of the added entity in the properties record.
			*/
			uint8_t		addToPropertiesRecord(std::unordered_map<std::string, uint8_t>&	record,
											  std::string const&						propName)					const	noexcept;

			/**
			*	@brief Get the rfk::EEntityKind corresponding to a kodgen::EEntityType.
			*	
			*	@param entityType kodgen::EEntityType to convert.
			*	
			*	@return The corresponding rfk::EEntityKind.
			*/
			std::string getRefurekuEntityKind(kodgen::EEntityType entityType)										const	noexcept;

			/**
			*	@brief Get the kind name of an entity.
			*	
			*	@param entityType kodgen::EEntityType to convert.
			*	
			*	@return The kind name of the provided entity type.
			*/
			std::string getEntityKindName(kodgen::EEntityType entityType)											const	noexcept;

			/**
			*	@brief Generate the variable name of a property.
			*	
			*	@param info			Entity the property is attached to.
			*	@param propName		Name of the property.
			*	@param propIndex	Index of the property in the list of all properties.
			*	
			*	@return A variable name for the property.
			*/
			std::string	generatePropertyVariableName(kodgen::EntityInfo const&	info,
													 std::string				propName, 
													 kodgen::uint8				propIndex)							const	noexcept;

			/**
			*	@brief Generate static asserts relative to a property.
			*	
			*	@param info								Entity the property is attached to.
			*	@param propName							Name of the property asserts are generated for.
			*	@param generateTargetEntityKindAssert	Should the targetEntityKind assert be generated?
			*	@param generateAllowMultipleAssert		Should the allowMultiple assert be generated?
			*	
			*	@return The static_assert generated code.
			*/
			std::string generateStaticAsserts(kodgen::EntityInfo const&	info,
											  std::string const&		propName,
											  bool						generateTargetEntityKindAssert,
											  bool						generateAllowMultipleAssert)				const	noexcept;

			/**
			*	@brief Generate static_assert code to make sure a property can be attached to a specific entity.
			*	
			*	@param info		Entity the property is attached to.
			*	@param propName	Name of the property.
			*
			*	@return The static_assert generated code.
			*/
			std::string generatePropertyTargetEntityKindAssert(kodgen::EntityInfo const&	info,
															   std::string const&			propName)				const	noexcept;

			/**
			*	@brief Generate static_assert code to make sure a property can be used multiple times in a single entity.
			*	
			*	@param info		Entity the property is attached to.
			*	@param propName	Name of the property.
			*
			*	@return The static_assert generated code.
			*/
			std::string generatePropertyAllowMultipleAssert(kodgen::EntityInfo const&	info,
															std::string const&			propName)					const	noexcept;

			/**
			*	@brief Generate a string which adds a simple property to an entity.
			*	
			*	@param info				Entity to to add the property to.
			*	@param entityVarName	Name of the entity variable in the generated code.
			*	@param prop				Simple property to add.
			*	@param propIndex		Index of the property in the list of properties of the entity.
			*	
			*	@return The generated code.
			*/
			std::string addSimplePropertyToEntity(kodgen::EntityInfo const&		info,
												  std::string const&			entityVarName,
												  kodgen::SimpleProperty const&	prop,
												  kodgen::uint8					propIndex,
												  bool							generateAllowMultipleAssert)		const	noexcept;

			/**
			*	@brief Generate a string which adds a complex property to an entity.
			*	
			*	@param info				Entity to to add the property to.
			*	@param entityVarName	Name of the entity variable in the generated code.
			*	@param prop				Complex property to add.
			*	@param propIndex		Index of the property in the list of properties of the entity.
			*	
			*	@return The generated code.
			*/
			std::string addComplexPropertyToEntity(kodgen::EntityInfo const&		info,
												  std::string const&				entityVarName,
												  kodgen::ComplexProperty const&	prop,
												  kodgen::uint8						propIndex,
												  bool								generateAllowMultipleAssert)	const	noexcept;

			/**
			*	@brief Generate a entity/property related code.
			*	
			*	@param propertyRule The detected property rule. It can be nullptr, in which case an empty string is returned immediately.
			*	@param entity		The entity the property is being added to.
			*	@param property		The property added to the entity
			*	@param isPreAdd		Should the PreAddProperty code be generated? If false, the PostAddProperty code will be generated.
			*	@param entityVar	Name of the entity variable in the generated code + its accessor.
			*	@param propertyVar	Name of the property variable in the generated code + its accessor.
			*
			*	@return The generated code.
			*/
			std::string	generatePropertyCode(kodgen::SimplePropertyRule const*	propertyRule,
											 kodgen::EntityInfo const&			entity,
											 kodgen::Property const&			property,
											 bool								isPreAdd,
											 std::string						entityVar,
											 std::string						propertyVar)						const	noexcept;

		protected:
			/** Prefix used to build internal macros. */
			static constexpr char const* const	internalPrefix = "__RFK";
			
			/** Prefix used to build user exposed macros. */
			static constexpr char const* const	externalPrefix = "";

			/** Class global string hasher. */
			static std::hash<std::string> const	stringHasher;

			/**
			*	@brief Get the provided entity id as string.
			*	
			*	@param entity Entity we retrieve the id from.
			*
			*	@return The provided entity id as string.
			*/
			static inline std::string	getEntityId(kodgen::EntityInfo const& entity)								noexcept;

			virtual void				generateCode(kodgen::GeneratedFile&			generatedFile,
													 kodgen::EntityInfo&			entityInfo,
													 kodgen::FileGenerationUnit&	fgu,
													 std::string&					out_errorDescription)	const	noexcept	override;

			/**
			*	@brief Generates a string containing the code which adds properties to an entity.
			*
			*	@param info				Source entity.
			*	@param entityVarName	Target entity variable name in the generated code.
			*	
			*	@return The generated code which adds the properties to the entity.
			*/
			std::string					fillEntityProperties(kodgen::EntityInfo const&	info,
															  std::string const&		entityVarName)	const	noexcept;

		public:
			GeneratedEntityCodeTemplate()									= default;
			GeneratedEntityCodeTemplate(GeneratedEntityCodeTemplate const&)	= default;
			GeneratedEntityCodeTemplate(GeneratedEntityCodeTemplate&&)		= default;
			virtual ~GeneratedEntityCodeTemplate()							= default;

			/**
			*	@brief Generate code for an entity native properties.
			*	
			*	@param entityInfo		EntityInfo containing properties
			*	@param propCodeGenData	User data to pass to the native properties generation code.
			*	
			*	@return The generated code as a string.
			*/
			static std::string generateNativePropertiesCode(kodgen::EntityInfo const&	entityInfo,
															void*						propCodeGenData)	noexcept;
	};

	#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.inl"
}
