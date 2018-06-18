#pragma once

#include <engine/backend/Archetype.hpp>
#include <engine/backend/Control.hpp>

namespace engine
{
	namespace backend
	{
		struct EnemyDescriptor;

		namespace controls
		{
			class Enemy : public Control
			{
			public:
				Enemy(Character &character, ControlContext &context, const EnemyDescriptor &descriptor, Character &playerCharacter);

				void update() override;

				std::string getPrefabName() const override;

			private:
				const Archetype *_archetype;
				int _shootDelayCounter{ 0 };

				Character &_playerCharacter;
			};
		}
	}
}
