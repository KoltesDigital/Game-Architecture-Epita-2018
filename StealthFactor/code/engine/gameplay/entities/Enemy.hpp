#pragma once

#include <string>
#include <engine/gameplay/entities/Character.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Enemy : public Character
			{
			public:
				Enemy(EntityContext &context, const std::string &archetypeName);

				virtual void update() override;

			private:
				float _visionRadius{ 0 };
				int _shootDelay{ 0 };
				int _shootDelayCounter{ 0 };

				void loadArchetype(const std::string &archetypeName);
			};
		}
	}
}
