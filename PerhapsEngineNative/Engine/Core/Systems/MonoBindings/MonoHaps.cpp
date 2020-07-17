#include "MonoHaps.h"

namespace Perhaps
{
	MonoDomain* MonoHaps::mainDomain = nullptr;
	MonoAssembly* MonoHaps::engineAssembly = nullptr;
	MonoObject* MonoHaps::engineObject = nullptr;
	MonoMethod* MonoHaps::updateMethod = nullptr;
}