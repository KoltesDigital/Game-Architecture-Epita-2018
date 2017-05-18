#pragma once

#include <engine/gameplay/Component.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class Player : public Component
			{
			public:
				Player(Entity &entity);

				void update() override;

				bool hasJustMoved() const;

			private:
				bool _justMoved{ false };
			};
		}
	}
}
