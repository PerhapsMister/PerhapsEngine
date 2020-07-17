#ifndef PERHAPS_RENDERER
#define PERHAPS_RENDERER
#include "../../PerhapsPch.h"
#include "RenderTexture.h"

namespace Perhaps
{
	class Renderer
	{
	public:

		/// <summary>
		/// Lowest priority gets rendererd first.
		/// </summary>
		/// <param name="renderer"></param>
		/// <param name="priority"></param>
		static void RegisterRenderer(Renderer* renderer, int priority)
		{
			if (registeredRenderers.find(priority) != registeredRenderers.end())
			{
				conlog("Renderer with priority " << priority << " Already registered!");
				return;
			}

			registeredRenderers.insert(std::make_pair(priority, renderer));
			registeredPriorities.push_back(priority);
			renderer->Initialize();
			std::sort(registeredPriorities.begin(), registeredPriorities.end());
		}

		/// <summary>
		/// Run the render loop. iterates over every registered renderer.
		/// </summary>
		static void RunRenderers(RenderTexture& buffer)
		{
			for (size_t i = 0; i < registeredPriorities.size(); i++)
			{
				int priority = registeredPriorities[i];
				Renderer* renderer = registeredRenderers[priority];
				renderer->Render(buffer);
			}
		}

		static void Cleanup()
		{
			for (size_t i = 0; i < registeredPriorities.size(); i++)
			{
				int priority = registeredPriorities[i];
				Renderer* renderer = registeredRenderers[priority];
				renderer->OnCleanup();
			}

			registeredRenderers.clear();
			registeredPriorities.clear();
		}

		virtual void Initialize() {};
		virtual void Render(RenderTexture& mainTexture /*Camera, RenderTargets, RenderTexture*/) {};
		virtual void OnCleanup() {};

	private:
		static std::unordered_map<int, Renderer*> registeredRenderers;
		static std::vector<int> registeredPriorities;
	};

}


#endif