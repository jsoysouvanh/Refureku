/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	//Forward declarations
	class TemplateParameter;
	class TemplateArgument;
	class ClassTemplateInstantiation;
	class ClassTemplate;

	/* A struct template and a class template contain exactly the same data. Alias for convenience. */
	using StructTemplate = ClassTemplate;

	class ClassTemplate final : public Struct
	{
		public:
			REFUREKU_API ClassTemplate(char const*	name,
									   std::size_t	id,
									   bool			isClass)	noexcept;
			REFUREKU_API ~ClassTemplate()						noexcept;

			/**
			*	@brief	Retrieve the template parameter at the given index.
			*			If index is greater or equal to getTemplateParametersCount(), the behaviour is undefined.
			* 
			*	@param index Index of the template parameter to retrieve.
			* 
			*	@return The template parameter at the given index.
			*/
			RFK_NODISCARD REFUREKU_API 
				TemplateParameter const&			getTemplateParameterAt(std::size_t index)									const	noexcept;

			/**
			*	@brief Get the number of template parameters for this class template.
			*
			*	@return The number of template parameters for this class template.
			*/
			RFK_NODISCARD REFUREKU_API
				std::size_t							getTemplateParametersCount()												const	noexcept;

			/**
			*	@brief Get an existing template instantiation corresponding to the provided arguments.
			* 
			*	@param args Template arguments.
			* 
			*	@return The found class template instantiation corresponding to the provided arguments if it exists, else nullptr.
			*/
			template <std::size_t ArgsCount>
			RFK_NODISCARD 
				ClassTemplateInstantiation const*	getTemplateInstantiation(TemplateArgument const* (&args)[ArgsCount])		const	noexcept;

			/**
			*	@brief	Get an existing template instantiation corresponding to the provided arguments.
			* 
			*	@param args			Pointer to an array of argument pointers
			*	@param argsCount	Number of template arguments.
			* 
			*	@return The found class template instantiation corresponding to the provided arguments if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				ClassTemplateInstantiation const*	getTemplateInstantiation(TemplateArgument const**	args,
																			 std::size_t				argsCount)				const	noexcept;

			/**
			*	@brief Get the number of instantiations (with different template parameters) of this class template within the program.
			* 
			*	@return The number of instantiations of this class template within the program.
			*/
			RFK_NODISCARD REFUREKU_API
				std::size_t							getTemplateInstantiationsCount()											const	noexcept;

			/**
			*	@brief Execute the given visitor on all template instantiations of this class.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachTemplateInstantiation(Visitor<ClassTemplateInstantiation> visitor,
																				 void*								 userData)	const;

			/**
			*	@brief Append a template parameter to the list of template parameters.
			* 
			*	@param param Template parameter to add.
			*/
			REFUREKU_API void						addTemplateParameter(TemplateParameter const& param)								noexcept;

			/**
			*	@brief Register an instantiation of this class template.
			* 
			*	@param inst The instantiation to register.
			*/
			REFUREKU_API void						registerTemplateInstantiation(ClassTemplateInstantiation const& inst)				noexcept;

			/**
			*	@brief Unregister an instantiation of this class template.
			* 
			*	@param inst The instantiation to unregister.
			*/
			REFUREKU_API void						unregisterTemplateInstantiation(ClassTemplateInstantiation const& inst)				noexcept;

		private:
			//Forward declaration
			class ClassTemplateImpl;

			RFK_GEN_GET_PIMPL(ClassTemplateImpl, Entity::getPimpl())
	};

	#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplate.inl"
}