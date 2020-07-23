#ifndef PERHAPS_ECS_ENGINE
#define PERHAPS_ECS_ENGINE
#include "../../../PerhapsPch.h"

namespace Perhaps
{
	class ECSEngine
	{
		public:

			const entt::registry& GetRegistry()
			{
				return registry;
			}
		private:
			entt::registry registry;
	};
}

#endif