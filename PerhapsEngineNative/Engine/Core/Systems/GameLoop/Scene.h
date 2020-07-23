#ifndef PERHAPS_SCENE
#define PERHAPS_SCENE
#include "../../PerhapsPch.h"
#include "ECS/ECSEngine.h"
#include "ECS/StandardComponents.h"

namespace Perhaps
{
	class Scene
	{
	public:

		void Initialize();
		void Update();

		const ECSEngine& GetEngine()
		{
			return ecs;
		}

		static Scene* CreateScene();
		static void DestroyScene(Scene* scene);

	private:
		static std::unordered_set<Scene*> activeScenes;
		ECSEngine ecs;


		Scene() {}
	};


	PAPI Scene* Scene_Create();
	PAPI void Scene_Delete(Scene* scene);
}


#endif