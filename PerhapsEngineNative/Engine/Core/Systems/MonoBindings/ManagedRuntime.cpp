#include "ManagedRuntime.h"
#include "ManagedGui.h"
#include "../../Application.h"


namespace Perhaps
{
	MonoDomain* MonoRuntime::mainDomain = nullptr;
	std::unordered_set<ManagedAssembly*> MonoRuntime::loadedAssemblies;
/*
	MonoDomain* MonoHaps::mainDomain = nullptr;
	MonoAssembly* MonoHaps::engineAssembly = nullptr;
	MonoObject* MonoHaps::engineObject = nullptr;
	MonoMethod* MonoHaps::updateMethod = nullptr;
	MonoMethod* MonoHaps::guiUpdateMethod = nullptr;
	*/

	ManagedAssembly* MonoRuntime::LoadAssembly(const char* assemblyPath)
	{
		MonoAssembly* monoAsm = mono_domain_assembly_open(mainDomain, assemblyPath);

		ManagedAssembly* managedAsm = new ManagedAssembly(assemblyPath, mainDomain, monoAsm);
		loadedAssemblies.insert(managedAsm);
		
		return managedAsm;
	}

	void MonoRuntime::UnloadAssembly(ManagedAssembly* assembly)
	{
		mono_assembly_close(assembly->GetMonoAssembly());
		delete(assembly);
	}

	void MonoRuntime::InitializeMono(bool debug, const char* libDir, const char* etcDir)
	{
		mono_set_dirs(libDir, etcDir);
		if (debug)
		{
			const char* options[]
			{
				"--debugger-agent=transport=dt_socket,server=y,suspend=y,timeout=20000,address=127.0.0.1:24040 --debug",
			};

			mono_debug_init(MONO_DEBUG_FORMAT_MONO);
			mono_jit_parse_options(1, (char**)options);
			conlog("awaiting managed debugger.");
		}

		const char* runtime_version = "v4.0.30319";
		mainDomain = mono_jit_init_version("Perhaps.Engine", runtime_version);
		mono_thread_set_main(mono_thread_current());

		const std::string appDir = Application::GetInstance()->GetAppDirectory();
		const std::string editorDllPath = appDir + "\\PerhapsEngineEditor.dll";

		ManagedAssembly* editorDll = LoadAssembly(editorDllPath.c_str());



	/*
		mono_set_dirs("C:\\Program Files (x86)\\Mono\\lib", "C:\\Program Files (x86)\\Mono\\etc");

		const char* options[]
		{
			"--debugger-agent=transport=dt_socket,server=y,suspend=n,timeout=20000,address=127.0.0.1:24040 --debug",
		};
		mono_debug_init(MONO_DEBUG_FORMAT_MONO);
		mono_jit_parse_options(1, (char**)options);

		const char* runtime_version = "v4.0.30319";
		conlog("awaiting managed debugger.");
		mainDomain = mono_jit_init_version("Perhaps.Domain", runtime_version);
		mono_thread_set_main(mono_thread_current());

		//std::string path = std::filesystem::current_path().string();
		//path = path + "\\Build-Debug-Bin\\" + editorDll;
		std::string path = "D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineNative\\Build-Debug-Bin\\";

		const char* editorDll = "PerhapsEngineEditor.dll";
		path = path + editorDll;
		conlog(path);

		engineAssembly = mono_domain_assembly_open(mainDomain, path.c_str());

		if (!engineAssembly)
		{
			conlog("Failed to open domain assembly.");
		}
		else
		{
			int argc = 1;
			char* argv[1] = { (char*)"TestAssembly" };

			MonoImage* image = mono_assembly_get_image(engineAssembly);
			MonoClass* engineClass = mono_class_from_name(image, "Perhaps.Engine.Editor", "EditorApplication");
			engineObject = mono_object_new(mainDomain, engineClass);
			MonoMethod* constructorMethod = mono_class_get_method_from_name(engineClass, ".ctor", 1);

			Application* app = Application::GetInstance();
			void* args[1];
			args[0] = &app;

			mono_runtime_invoke(constructorMethod, engineObject, args, NULL);

			updateMethod = mono_class_get_method_from_name(engineClass, "Update", 0);
			guiUpdateMethod = mono_class_get_method_from_name(engineClass, "OnEditorGuiRender", 1);

		}

		EventDispatcher::Subscribe(ImGuiRenderEvent::descriptor, UpdateManagedGui);
		*/
	}

	/*
	void MonoRuntime::UpdateManaged()
	{
	
		mono_runtime_invoke(updateMethod, engineObject, NULL, NULL);
		
	}

	void MonoRuntime::UpdateManagedGui(const Event& e)
	{
	
		ImGuiRenderEvent& renderEvent = (ImGuiRenderEvent&)e;

		void* args[1];
		args[0] = &renderEvent.rt;

		mono_runtime_invoke(guiUpdateMethod, engineObject, args, NULL);
		
	}
	*/
}