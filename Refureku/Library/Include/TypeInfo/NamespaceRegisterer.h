/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace rfk
{
	class Namespace;	//Forward declaration

	class NamespaceRegisterer
	{
		private:
			/** Prototype of a method which fills namespace information. */
			typedef void (*NamespaceFillerPrototype)(Namespace* toFillNamespace) noexcept;

			/** Namespace influenced by this registerer. */
			Namespace*	_namespaceInstance	= nullptr;

			/** Whether or not _generatedNamespace has been instantiated by this registerer. */
			bool		_isNamespaceOwner	= false;

		public:
			NamespaceRegisterer()											= default;
			NamespaceRegisterer(char const*					name,
								uint64						id,
								NamespaceFillerPrototype	fillerMethod)	noexcept;
			NamespaceRegisterer(NamespaceRegisterer const&)					= delete;
			NamespaceRegisterer(NamespaceRegisterer&&)						= delete;
			~NamespaceRegisterer()											noexcept;

			/**
			*	@brief Getter for _namespaceInstance.
			*	
			*	@return _namespaceInstance
			*/
			Namespace const* getNamespaceInstance()	const	noexcept;

			NamespaceRegisterer& operator=(NamespaceRegisterer const&)	= delete;
			NamespaceRegisterer& operator=(NamespaceRegisterer&&)		= delete;
	};
}