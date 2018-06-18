#pragma once

#include <engine/backend/Control.hpp>

namespace engine
{
	namespace backend
	{
		namespace controls
		{
			class Player : public Control
			{
			public:
				Player(Character &character, ControlContext &context);

				void update() override;

				std::string getPrefabName() const override;
			};
		}
	}
}
