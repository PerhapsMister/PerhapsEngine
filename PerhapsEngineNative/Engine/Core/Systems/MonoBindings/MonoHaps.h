#ifndef PERHAPS_MONO
#define PERHAPS_MONO
#include "../../PerhapsPch.h"


class MonoHaps
{
public:
	static void InitializeMono()
	{
		mono_set_dirs("C:\\Program Files (x86)\\Mono\\lib", "C:\\Program Files (x86)\\Mono\\etc");

		const char* options[]
		{
			"--debugger-agent=transport=dt_socket,server=y,suspend=y,timeout=20000,address=127.0.0.1:24040",
		};

		mono_debug_init(MONO_DEBUG_FORMAT_MONO);
		mono_jit_parse_options(1, (char**)options);

		const char* runtime_version = "v4.0.30319";
		conlog("Waiting for managed debugger...");

		mainDomain = mono_jit_init_version("Perhaps.Domain", runtime_version);
		conlog("Managed debugger connection established!");

		mono_thread_set_main(mono_thread_current());
		mono_debug_domain_create(mainDomain);

		std::string assemblyDirectory = "D:\\Dev\\Dev\\PerhapsEngine\\native\\PerhapsEngineNative\\PerhapsEngineManaged\\bin\\Debug\\net461\\";
		std::string assemblyFilepath(assemblyDirectory);
		assemblyFilepath.append("PerhapsEngineManaged.dll");

		engineAssembly = mono_domain_assembly_open(mainDomain, assemblyFilepath.c_str());

		if (!engineAssembly)
		{
			conlog("Failed to open domain assembly.");
		}
		else
		{
			int argc = 1;
			char* argv[1] = { (char*)"TestAssembly" };

			MonoImage* image = mono_assembly_get_image(engineAssembly);
			MonoClass* engineClass = mono_class_from_name(image, "Perhaps.Engine", "PerhapsEngine");
			engineObject = mono_object_new(mainDomain, engineClass);
			mono_runtime_object_init(engineObject);

			MonoMethodDesc* onInitDesc = mono_method_desc_new("Perhaps.Engine:OnInitialize()", false);
			MonoMethod* onInitializeMethod = mono_method_desc_search_in_class(onInitDesc, engineClass);

			MonoMethodDesc* onUpdateDesc = mono_method_desc_new("Perhaps.Engine:OnUpdate()", false);
			updateMethod = mono_method_desc_search_in_class(onUpdateDesc, engineClass);

			mono_runtime_invoke(onInitializeMethod, engineObject, NULL, NULL);
		}
	}

	static void UpdateManaged()
	{
		mono_runtime_invoke(updateMethod, engineObject, NULL, NULL);
	}

private:
	static MonoDomain* mainDomain;
	static MonoAssembly* engineAssembly;
	static MonoObject* engineObject;
	static MonoMethod* updateMethod;
};

MonoDomain* MonoHaps::mainDomain = nullptr;
MonoAssembly* MonoHaps::engineAssembly = nullptr;
MonoObject* MonoHaps::engineObject = nullptr;
MonoMethod* MonoHaps::updateMethod = nullptr;

#endif