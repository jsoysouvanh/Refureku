#pragma once

#include "Generated/ExampleClass.refureku.h"

#include <iostream>

namespace exnamespace
{
	class RFKClass() ParentParentParentClass
	{
		RFKField()
		double pppDouble;

		RFKParentParentParentClass_GENERATED
	};

	class RFKClass() ParentParentClass : private ParentParentParentClass
	{
		RFKField()
		float ppFloat;

		RFKParentParentClass_GENERATED
	};

	class RFKClass() ParentClass : protected ParentParentClass
	{
		private:
			RFKMethod()
			void parentClassMethod1() noexcept { };

		public:
			RFKField()
			uint64_t pInt64 = 666;

			RFKMethod()
			virtual void method1() const { };

			ParentClass()					= default;
			ParentClass(ParentClass const&)	= default;
			ParentClass(ParentClass&& o)	= default;

			//	GENERATED

			template <typename ChildType>
			static void __RFKregisterChild(refureku::Struct* childArchetype) noexcept
			{
				refureku::Struct const& thisArchetype = staticGetArchetype();

				//TODO: Recursive call to parents classes later here

				//Add to list of children
				if (childArchetype != &thisArchetype)
				{
					//TODO
				}

				//Add fields
				childArchetype->fields.emplace_back("pInt64", 12635385505303968848u, static_cast<refureku::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, pInt64), 0);
			}

		RFKParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ExampleClass : public ParentClass
	{
		public:
			RFKField()
			static inline int	someStaticInt = 69;

			RFKField()
			static inline ParentClass	someStaticParentClass;

			RFKField()
			mutable int		someInt			= 42;

			RFKField()
			ParentClass		someParentClass;

			RFKField()
			int*			somePtrToInt	= nullptr;

			RFKField()
			float			someFloat		= 42.42f;

			RFKMethod()
			int				method4(void* ptr);

			RFKMethod()
			virtual void	method1() const noexcept override;

		protected:
			RFKMethod()
			void			method2() const;

			RFKMethod()
			int				method3();

			RFKMethod()
			static	int		staticMethod3(char const* param);

		private:
			RFKMethod()
			static	int		staticMethod2();

			RFKMethod()
			static void		staticMethod1();

			RFKMethod()
			static	float	staticMethod3(int param)	noexcept;

			RFKMethod()
			float			method3(int i)				noexcept;

		public:
			ExampleClass()						= default;
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		//GENERATED

		template <typename ChildType>
		static void __RFKregisterChild(refureku::Struct* childArchetype) noexcept
		{
			refureku::Struct const& thisArchetype = staticGetArchetype();

			//TODO: Recursive call to parents classes later here

			//Add to list of children
			if (childArchetype != &thisArchetype)
			{
				//TODO
			}

			//Add fields
			childArchetype->fields.emplace_back("somePtrToInt", 12635385505303968848u, static_cast<refureku::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, somePtrToInt), 0);
		}

		static refureku::Class const& staticGetArchetype() noexcept	
		{	
			static bool				initialized = false;	
			static refureku::Class	type("ExampleClass", 6613751926088865067, static_cast<refureku::Archetype::ECategory>(0), sizeof(ExampleClass));	
			
			if (!initialized)	
			{
				__RFKExampleClass_GenerateParentsMetadata

				//Get total fields count
				size_t fieldsCount = 0; std::vector<refureku::Struct::Parent> currParents; std::vector<refureku::Struct::Parent> nextParents = type.directParents; while (!nextParents.empty()) { std::swap(currParents, nextParents); nextParents.clear(); for (refureku::Struct::Parent const& parent : currParents) { nextParents.insert(nextParents.end(), parent.type->directParents.begin(), parent.type->directParents.end()); fieldsCount += parent.type->fields.size(); } }

				type.fields.reserve(fieldsCount);

				//TODO here register to all direct parents
				type.__RFKregisterToParent<ParentClass, ExampleClass>();

				//Call self register child
				__RFKregisterChild<ExampleClass>(&type);
				
				initialized = true;
			}	
				
			return type;	
		}	
			
		refureku::Class const& getArchetype() const noexcept	
		{	
			return ExampleClass::staticGetArchetype();
		}

		//RFKExampleClass_GENERATED
	};
}