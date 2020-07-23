#ifndef PERHAPS_MONO
#define PERHAPS_MONO
#include "../../PerhapsPch.h"
#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EngineEvents.h"
#include "../Graphics/RenderTexture.h"
#include "ManagedAssembly.h"

namespace Perhaps
{

	class MonoRuntime
	{
	public:
		static void InitializeMono(bool debug, const char* libDir, const char* etcDir);
		static ManagedAssembly* LoadAssembly(const char* assemblyPath);
		static void UnloadAssembly(ManagedAssembly* assembly);

	private:
		static std::unordered_set<ManagedAssembly*> loadedAssemblies;
		static MonoDomain* mainDomain;

	/*
		static MonoDomain* mainDomain;
		static MonoAssembly* engineAssembly;
		static MonoObject* engineObject;
		static MonoMethod* updateMethod;
		static MonoMethod* guiUpdateMethod;
		*/
	};
}
#endif