#pragma once

#include "clang-c/Index.h"
#include <string>
#include <vector>

#include "Misc/FundamentalTypes.h"
#include "InfoStructures/TypeDescriptor.h"

namespace kodgen
{
	class TypeInfo
	{
		private:
			static constexpr char const*	_classQualifier		= "class ";
			static constexpr char const*	_structQualifier	= "struct ";
			static constexpr char const*	_constQualifier		= "const";
			static constexpr char const*	_volatileQualifier	= "volatile";
			static constexpr char const*	_restrictQualifier	= "restrict";

			/**
			*	The full name represents the type name, containing all its qualifiers
			*	such as const, volatile or nested info (namespace, outer class)
			*
			*	i.e. const volatile ExampleNamespace::ExampleClass *const*&
			*/
			std::string					fullName			= "";

			/**
			*	The canonical full name is the full name simplified by unwinding
			*	all aliases / typedefs
			*/
			std::string					canonicalFullName	= "";

			/**
			*	Init all internal flags according to the provided type
			*/
			void initialize(CXType cursorType)											noexcept;

			void removeForwardDeclaredClassQualifier(std::string& parsingStr)	const	noexcept;
			void removeNamespacesAndNestedClasses(std::string& typeString)		const	noexcept;
			bool removeConstQualifier(std::string& typeString)					const	noexcept;
			bool removeVolatileQualifier(std::string& typeString)				const	noexcept;
			bool removeRestrictQualifier(std::string& typeString)				const	noexcept;

		public:
			/**
			*	This array contains info about each "part" of the type
			*
			*	If the type is SomeType const *const**const*&, the array would be
			*		{ LRef 0, Ptr 0, Const Ptr 0, Ptr 0, Const Ptr 0, Const Value 0 }	(read the type from right to left)
			*	If the type is float[2][3], the array would be
			*		{ CArray 2, CArray 3, Value }	/!\ Array parts ONLY are read from left to right (not right to left)
			*	One more: if the type is int*[2][3], the array would be
			*		{ CArray 2, CArray 3, Ptr, Value }
			*/
			std::vector<TypePart>	typeParts;

			/**
			*	Size of this type in bytes
			*/
			size_t					sizeInBytes			= 0u;

			TypeInfo()						= default;
			TypeInfo(CXType cursorType)		noexcept;
			TypeInfo(TypeInfo const&)		= default;
			TypeInfo(TypeInfo&&)			= default;
			~TypeInfo()						= default;

			/**
			*	@brief Get this type name by removing specified qualifiers / namespaces / nested classes
			*
			*	@param removeQualifiers Should the const and volatile qualifiers be removed from the type name
			*	@param removeNamespacesAndNestedClasses Should the namespaces and nested classes be removed from the type name
			*
			*	@return The cleaned type name
			*/
			std::string getName(bool removeQualifiers = false, bool shouldRemoveNamespacesAndNestedClasses = false)				const noexcept;

			/**
			*	@brief Get this type canonical name by removing specified qualifiers / namespaces / nested classes
			*	@brief The canonical name is the name simplified by unwinding all aliases and/or typedefs
			*
			*	@param removeQualifiers Should the const and volatile qualifiers be removed from the type name
			*	@param removeNamespacesAndNestedClasses Should the namespaces and nested classes be removed from the type name
			*
			*	@return The cleaned type name
			*/
			std::string getCanonicalName(bool removeQualifiers = false, bool shouldRemoveNamespacesAndNestedClasses = false)	const noexcept;

			TypeInfo& operator=(TypeInfo const&)	= default;
			TypeInfo& operator=(TypeInfo&&)			= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, TypeInfo const& typeInfo) noexcept;
}