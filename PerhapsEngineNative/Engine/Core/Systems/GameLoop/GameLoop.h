#ifndef PERHAPS_MANAGED_BINDING
#define PERHAPS_MANAGED_BINDING
#include "../../PerhapsPch.h"
#include "../MonoBindings/MonoHaps.h"

class GameLoop
{
public:

	static void Init()
	{
		MonoHaps::InitializeMono();
	}

	static void OnUpdate()
	{
		MonoHaps::UpdateManaged();
	}

	static void Cleanup()
	{

	}
private:

};

#endif