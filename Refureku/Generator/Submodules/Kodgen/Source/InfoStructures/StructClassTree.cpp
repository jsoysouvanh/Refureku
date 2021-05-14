#include "Kodgen/InfoStructures/StructClassTree.h"

#include <cassert>
#include <algorithm> //std::none_of
#include <queue>

using namespace kodgen;

bool StructClassTree::addInheritanceLink(std::string const& childStructClassName, std::string const& parentStructClassName, EAccessSpecifier inheritanceAccess) noexcept
{
	//Create child and parent structs entries if they don't exist yet
	entries.emplace(parentStructClassName, std::vector<StructClassTree::InheritanceLink>());
	std::vector<StructClassTree::InheritanceLink>& childInheritanceLinks = entries.emplace(childStructClassName, std::vector<StructClassTree::InheritanceLink>()).first->second;

	//If the inheritance link doesn't exist yet, create it
	if (std::none_of(childInheritanceLinks.begin(), childInheritanceLinks.end(), [&parentStructClassName](StructClassTree::InheritanceLink const& link){ return link.inheritedStructClassName == parentStructClassName; }))
	{
		childInheritanceLinks.emplace_back(StructClassTree::InheritanceLink{ parentStructClassName, inheritanceAccess });

		return true;
	}
	
	return false;
}

bool StructClassTree::isBaseOf(std::string const& baseStructClassName, std::string const& childStructClassName, EAccessSpecifier* out_inheritanceAccess) const noexcept
{
	decltype(entries)::const_iterator childEntry = entries.find(childStructClassName);

	//Make sure the childStruct is registered to the tree
	if (childEntry != entries.cend())
	{
		//If the base class is the same as the child class, it is a valid base
		if (baseStructClassName == childStructClassName)
		{
			//Fill out_inheritanceAccess if possible
			if (out_inheritanceAccess != nullptr)
			{
				*out_inheritanceAccess = EAccessSpecifier::Invalid;
			}

			return true;
		}
		//Make sure the base class exists in the tree before we continue any further
		else if (entries.find(baseStructClassName) != entries.cend())
		{
			std::queue<decltype(entries)::const_iterator> toCheck;
			toCheck.push(childEntry);

			decltype(entries)::const_iterator currentEntry;

			//Traverse the parents of childStruct recursively until we find the base class
			while (!toCheck.empty())
			{
				currentEntry = toCheck.front();
				toCheck.pop();

				for (StructClassTree::InheritanceLink const& inheritanceLink : currentEntry->second)
				{
					//All inheritance links should point to a valid struct/class.
					assert(entries.find(inheritanceLink.inheritedStructClassName) != entries.cend());

					//If the name matches baseStructClass is a valid base class
					if (inheritanceLink.inheritedStructClassName == baseStructClassName)
					{
						//Fill out_inheritanceAccess if possible
						if (out_inheritanceAccess != nullptr)
						{
							*out_inheritanceAccess = inheritanceLink.inheritanceAccess;
						}

						return true;
					}
					else
					{
						//Recurse on the tested entry parents
						toCheck.push(entries.find(inheritanceLink.inheritedStructClassName));
					}
				}
			}
		}
	}

	return false;
}

std::unordered_map<std::string, std::vector<StructClassTree::InheritanceLink>> const& StructClassTree::getEntries() const noexcept
{
	return entries;
}