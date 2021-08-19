/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#include <functional>	//std::hash
#include <string>
#include <unordered_map>
#include <vector>

#include "Kodgen/Misc/EAccessSpecifier.h"

namespace kodgen
{
	class StructClassTree
	{
		public:
			struct InheritanceLink
			{
				/** Name of the inherited struct/class. */
				std::string			inheritedStructClassName;

				/** Inheritance access. */
				EAccessSpecifier	inheritanceAccess;
			};

		private:
			/** Collection mapping a struct/class name to its inherited structs/classes. */
			std::unordered_map<std::string, std::vector<InheritanceLink>> entries;

		public:
			StructClassTree()						= default;
			StructClassTree(StructClassTree const&)	= default;
			StructClassTree(StructClassTree&&)		= default;
			~StructClassTree()						= default;

			/**
			*	@brief	Add an inheritance link between currentClass and parentClass.
			*			If entries corresponding to currentClass and parentClass don't exist yet, they are created.
			* 
			*	@param childStructClassName		Name of the child struct/class.
			*	@param parentStructClassName	Name of the parent struct/class.
			*	@param inheritanceAccess		Inheritance specifier.
			* 
			*	@return true if the inheritance link was added, else false (the link already existed before).
			*/
			bool	addInheritanceLink(std::string const&	childStructClassName,
									   std::string const&	parentStructClassName,
									   EAccessSpecifier		inheritanceAccess)				noexcept;

			/**
			*	@brief	Check whether baseStructClass is a base of childStructClass (parent class or the class itself).
			*			Canonical names must be used.
			*			Ex: isBaseOf("EntityInfo", "StructClassInfo") is unvalid.
			*				isBaseOf("kodgen::EntityInfo", "kodgen::StructClassInfo") is valid.
			*
			*	@param baseStructClassName	Canonical name of the base class.
			*	@param childStructClassName	Canonical name of the child class.
			*	@param inheritanceAccess	Optional inheritance access filled if true is returned. In the case baseStruct is childStruct, EAccessSpecifier::Invalid is used.
			*
			*	@return true if baseClass is a parent of childClass, or if baseClass is childClass, else false.
			*			If names are incorrect (non-canonical for example), return false.
			*/
			bool	isBaseOf(std::string const& baseStructClassName,
							 std::string const& childStructClassName,
							 EAccessSpecifier*	out_inheritanceAccess = nullptr)	const	noexcept;

			/**
			*	@brief Getter for entries field.
			*
			*	@return entries.
			*/
			std::unordered_map<std::string, std::vector<InheritanceLink>> const&	getEntries()	const	noexcept;

			StructClassTree& operator=(StructClassTree const&)	= default;
			StructClassTree& operator=(StructClassTree&&)		= default;
	};
}