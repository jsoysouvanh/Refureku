#include "InfoStructures/TypeInfo.h"

#include <iostream>
#include <cassert>

#include "Misc/Helpers.h"

using namespace kodgen;

TypeInfo::TypeInfo(CXType cursorType) noexcept:
	qualifiers{false, false, false}
{
	assert(cursorType.kind != CXTypeKind::CXType_Invalid);

	initialize(cursorType);
}

void TypeInfo::initialize(CXType cursorType) noexcept
{
	CXType	canonicalType = clang_getCanonicalType(cursorType);

	assert(canonicalType.kind != CXTypeKind::CXType_Invalid);

	fullName			= Helpers::getString(clang_getTypeSpelling(cursorType));
	canonicalFullName	= Helpers::getString(clang_getTypeSpelling(canonicalType));

	long long size		= clang_Type_getSizeOf(cursorType);

	if (size == CXTypeLayoutError::CXTypeLayoutError_Invalid ||
		size == CXTypeLayoutError::CXTypeLayoutError_Incomplete ||
		size == CXTypeLayoutError::CXTypeLayoutError_Dependent)
	{
		sizeInBytes = 0;
	}
	else
	{
		sizeInBytes = static_cast<size_t>(size);
	}

	isPointer	= canonicalType.kind == CXTypeKind::CXType_Pointer;
	isReference = canonicalType.kind == CXTypeKind::CXType_LValueReference;

	assert(!(isPointer && isReference));

	qualifiers.isConst		= clang_isConstQualifiedType(canonicalType);
	qualifiers.isVolatile	= clang_isVolatileQualifiedType(canonicalType);
	qualifiers.isRestricted	= clang_isRestrictQualifiedType(canonicalType);

	//Remove class or struct keyword
	removeForwardDeclaredClassQualifier(fullName);

	if (isPointer || isReference)
	{
		//Fill the pointers vector
		CXType					prevType{ CXTypeKind::CXType_Invalid, { canonicalType.data } };
		CXType					currType = canonicalType;

		while (!clang_equalTypes(prevType, currType))
		{
			if (currType.kind == CXTypeKind::CXType_Pointer)
			{
				pointers.push_back(clang_isConstQualifiedType(currType) ? EPointerType::ConstPointer : EPointerType::Pointer);
			}

			prevType = currType;
			currType = clang_getPointeeType(prevType);
		}
	}
}

void TypeInfo::removeForwardDeclaredClassQualifier(std::string& parsingStr) const noexcept
{
	std::string expectedKeyword = parsingStr.substr(0, 7);

	//Check for the struct keyword
	if (expectedKeyword == _structQualifier)
	{
		parsingStr.erase(0, 7);
	}
	else
	{
		//Check for the class keyword
		expectedKeyword.pop_back();

		if (expectedKeyword == _classQualifier)
		{
			parsingStr.erase(0, 6);
		}
	}
}

void TypeInfo::removeNamespacesAndNestedClasses(std::string& typeString) const noexcept
{
	size_t	stringStart		= 0;
	uint8	templateLevel;

	//Here comes the actual type name, remove namespace / nested class name
	size_t charIndex;
	while ((charIndex = typeString.find_first_of("<:", stringStart, 2)) != typeString.npos)
	{
		if (typeString.at(charIndex) == ':')	// : implies ::
		{
			typeString.erase(0, charIndex + 2);		// +2 to remove the ::
			stringStart = 0;
		}
		else	//parsingCanonicalStr.at(charIndex) == '<'
		{
			templateLevel	= 1;
			stringStart		= charIndex + 1;

			while (templateLevel != 0)
			{
				charIndex = typeString.find_first_of("<>", stringStart, 2);

				if (charIndex == typeString.npos)
				{
					assert(false);	//If assert here, means a template type is never closed
				}
				else if (typeString.at(charIndex) == '<')
				{
					templateLevel++;
					stringStart = charIndex + 1;
				}
				else	//parsingCanonicalStr.at(charIndex) == '>'
				{
					templateLevel--;
					stringStart = charIndex + 1;
				}
			}
		}
	}
}

bool TypeInfo::removeConstQualifier(std::string& typeString) const noexcept
{
	if (qualifiers.isConst)
	{
		size_t charIndex = typeString.rfind(_constQualifier);

		if (charIndex != typeString.npos)
		{
			typeString.erase(charIndex, 5);

			return true;
		}
	}
	
	return false;
}

bool TypeInfo::removeVolatileQualifier(std::string& typeString) const noexcept
{
	if (qualifiers.isVolatile)
	{
		size_t charIndex = typeString.rfind(_volatileQualifier);

		if (charIndex != typeString.npos)
		{
			typeString.erase(charIndex, 8);

			return true;
		}
	}

	return false;
}

bool TypeInfo::removeRestrictQualifier(std::string& typeString) const noexcept
{
	if (qualifiers.isRestricted)
	{
		size_t charIndex = typeString.rfind(_restrictQualifier);

		if (charIndex != typeString.npos)
		{
			typeString.erase(charIndex, 8);

			return true;
		}
	}

	return false;
}

std::string TypeInfo::getName(bool removeQualifiers, bool shouldRemoveNamespacesAndNestedClasses) const noexcept
{
	std::string result = fullName;

	if (removeQualifiers)
	{
		removeConstQualifier(result);
		removeVolatileQualifier(result);
		removeRestrictQualifier(result);
	}

	if (shouldRemoveNamespacesAndNestedClasses)
	{
		removeNamespacesAndNestedClasses(result);
	}

	return result;
}

std::string TypeInfo::getCanonicalName(bool removeQualifiers, bool shouldRemoveNamespacesAndNestedClasses) const noexcept
{
	std::string result = canonicalFullName;

	if (removeQualifiers)
	{
		removeConstQualifier(result);
		removeVolatileQualifier(result);
		removeRestrictQualifier(result);
	}

	if (shouldRemoveNamespacesAndNestedClasses)
	{
		removeNamespacesAndNestedClasses(result);
	}

	return result;
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, TypeInfo const& typeInfo) noexcept
{
	out_stream << typeInfo.getName(false, false);

	return out_stream;
}