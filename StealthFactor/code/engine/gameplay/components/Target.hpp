#pragma once

#include <engine/gameplay/Component.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class Target : public Component
			{
			public:
				Target(Entity &entity);
			};
		}
	}
}
