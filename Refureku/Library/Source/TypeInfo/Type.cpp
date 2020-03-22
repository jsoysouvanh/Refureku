#include "TypeInfo/Type.h"

namespace refureku
{
	class Type
	{
		private:

		protected:

		public:
			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= delete;
			virtual ~Type()		= default;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};
}