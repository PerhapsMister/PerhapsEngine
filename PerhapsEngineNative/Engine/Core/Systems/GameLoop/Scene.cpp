#include "Scene.h"

namespace Perhaps
{
	std::unordered_set<Scene*> Scene::activeScenes;

	Scene* Scene::CreateScene()
	{
		Scene* scene = new Scene();

		activeScenes.insert(scene);
		return scene;
	}

	void Scene::DestroyScene(Scene* scene)
	{
		activeScenes.erase(scene);
		delete(scene);
	}

	void Scene::Initialize()
	{
	/*
		registry.on_construct<FooComponent>().connect<&OnConstructFoo>();
		entt::entity entity = registry.create();

		uint32_t id = (uint32_t)entity;
		entity = (entt::entity)id;

		registry.emplace<FooComponent>(entity);
		

		if (registry.has<FooComponent>(entity))
		{
				FooComponent& fooComp = registry.get<FooComponent>(entity);

		}
		*/
	}

	void Scene::Update()
	{
		/*
		auto view = registry.view<FooComponent>();

		for (auto entity : view)
		{
			FooComponent& fooComp = registry.get<FooComponent>(entity);
			conlog(fooComp.age);
		}
		*/
	}

	Scene* Scene_Create()
	{
		return Scene::CreateScene();
	}

	void Scene_Delete(Scene* scene)
	{
		Scene::DestroyScene(scene);
	}
}