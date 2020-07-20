#ifndef PERHAPS_MONO
#define PERHAPS_MONO
#include "../../PerhapsPch.h"
#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EngineEvents.h"
#include "../Graphics/RenderTexture.h"

namespace Perhaps
{

	class MonoHaps
	{
	public:
		

		static void InitializeMono();
		static void UpdateManaged();
		static void UpdateManagedGui(const Event& e);

	private:
		static MonoDomain* mainDomain;
		static MonoAssembly* engineAssembly;
		static MonoObject* engineObject;
		static MonoMethod* updateMethod;
		static MonoMethod* guiUpdateMethod;
	};
}
#endif