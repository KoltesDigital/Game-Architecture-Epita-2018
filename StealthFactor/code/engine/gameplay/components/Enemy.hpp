#pragma once

#include <string>
#include <engine/gameplay/Component.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class Enemy : public Component
			{
			public:
				Enemy(Entity &entity);

				void update() override;

				void setArchetypeName(const std::string &archetypeName);

			private:
				std::string _shapeListName;
				float _visionRadius{ 0.f };
				int _shootDelay{ 0 };
				int _shootDelayCounter{ 0 };

				bool _shapeListNameHasChanged{ false };
			};
		}
	}
}
