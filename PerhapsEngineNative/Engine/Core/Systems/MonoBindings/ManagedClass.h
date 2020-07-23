#ifndef PERHAPS_MONO_CLASS
#define PERHAPS_MONO_CLASS
#include "../../PerhapsPch.h"

namespace Perhaps
{
	class ManagedClass
	{
	public:
		ManagedClass(MonoClass* monoKlass) : monoClass(monoKlass)
		{
			
		}

	private:
		MonoClass* monoClass;
	};
}

#endif