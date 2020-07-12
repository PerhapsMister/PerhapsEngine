#ifndef PERHAPS_MANAGED_BINDING
#define PERHAPS_MANAGED_BINDING
#include "../../PerhapsPch.h"

class GameLoop
{
public:

	static void Init()
	{
		mono_set_dirs("C:\\Program Files (x86)\\Mono\\lib", "C:\\Program Files (x86)\\Mono\\etc");
		mainDomain = mono_jit_init("PerhapsEngineManaged_Domain");

#if _DEBUG
		engineAssembly = mono_domain_assembly_open(mainDomain,
			"D:\\Dev\\Dev\\PerhapsEngine\\native\\PerhapsEngineNative\\PerhapsEngineManaged\\bin\\Debug\\net461\\PerhapsEngineManaged.dll");
#else
		engineAssembly = mono_domain_assembly_open(mainDomain, "PerhapsEngineManaged.dll");
#endif

		if (!engineAssembly)
		{
			conlog("Failed to open domain assembly.");
		}
		else
		{
			int argc = 1;
			char* argv[1] = { (char*)"TestAssembly" };

			MonoImage* image = mono_assembly_get_image(engineAssembly);
			MonoClass* engineClass = mono_class_from_name(image, "Perhaps", "PerhapsEngine");
			engineObject = mono_object_new(mainDomain, engineClass);
			mono_runtime_object_init(engineObject);

			MonoMethodDesc* onInitDesc = mono_method_desc_new("Perhaps:OnInitialize()", false);
			MonoMethod* onInitializeMethod = mono_method_desc_search_in_class(onInitDesc, engineClass);

			MonoMethodDesc* onUpdateDesc = mono_method_desc_new("Perhaps:OnUpdate()", false);
			updateMethod = mono_method_desc_search_in_class(onUpdateDesc, engineClass);

			mono_runtime_invoke(onInitializeMethod, engineObject, NULL, NULL);
		}
	}

	static void OnUpdate()
	{
		if (engineObject != nullptr)
		{
			mono_runtime_invoke(updateMethod, engineObject, NULL, NULL);
		}
	}

private:
	static MonoDomain* mainDomain;
	static MonoAssembly* engineAssembly;
	static MonoObject* engineObject;
	static MonoMethod* updateMethod;

};

MonoDomain* GameLoop::mainDomain = nullptr;
MonoAssembly* GameLoop::engineAssembly = nullptr;
MonoObject* GameLoop::engineObject = nullptr;
MonoMethod* GameLoop::updateMethod = nullptr;

#endif