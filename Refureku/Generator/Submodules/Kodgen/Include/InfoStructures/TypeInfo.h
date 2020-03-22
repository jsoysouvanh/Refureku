#pragma once

#include "clang-c/Index.h"
#include <string>
#include <vector>

#include "Misc/FundamentalTypes.h"

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
			enum class EPointerType : uint8
			{
				Pointer,
				ConstPointer
			};

			struct TypeQualifiers
			{
				bool isConst		: 1;
				bool isRestricted	: 1;
				bool isVolatile		: 1;
			}							qualifiers;
			
			/**
			*	This array contains info about the "pointer depth" of the canonical type
			*
			*	If the type is SomeType *const**const*, the pointers array would be
			*	{ Pointer, ConstPointer, Pointer, ConstPointer }	(right to left)
			*/
			std::vector<EPointerType>	pointers;

			/**
			*	Is this type a pointer ?
			*	If true, you can check the pointers array for more info
			*/
			bool						isPointer			= false;

			/**
			*	Is this type a reference
			*/
			bool						isReference			= false;

			/**
			*	Size of this type in bytes
			*/
			size_t						sizeInBytes			= 0u;

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