#ifndef PERHAPS_MANAGED_ASSEMBLY
#define PERHAPS_MANAGED_ASSEMBLY
#include "../../PerhapsPch.h"
#include "ManagedClass.h"

namespace Perhaps
{
	class ManagedAssembly
	{
	public:
		ManagedAssembly(const char* assemblyPath, MonoDomain* domain, MonoAssembly* monoAsm) : path(assemblyPath), 
			belongDomain(domain), monoAssembly(monoAsm)
		{
			
		}

		MonoAssembly* GetMonoAssembly()
		{
			return monoAssembly;
		}


		/// <summary>
		/// I.E System.Collections.Generic.List
		/// </summary>
		/// <param name="fullClassName"></param>
		/// <returns></returns>
		ManagedClass GetClass(const std::string& nameSpace,  const std::string& className)
		{
			MonoImage* img = mono_assembly_get_image(monoAssembly);
			MonoClass* klass = mono_class_from_name(img, nameSpace.c_str(), className.c_str());
			
			if(klass == nullptr)
				return nullptr;
			
			return ManagedClass(klass);
		}

		const char* GetAssemblyPath()
		{
			return path;
		}

	private:
		const char* path;
		MonoAssembly* monoAssembly;
		MonoDomain* belongDomain;
	};
}

#endif