#pragma once

#include <memory>
#include <string>
#include <vector>
#include <engine/backend/CharacterId.hpp>
#include <engine/backend/Control.hpp>
#include <engine/backend/Orientation.hpp>
#include <engine/backend/Position.hpp>

namespace engine
{
	namespace backend
	{
		struct Character
		{
			CharacterId id;
			Position position;
			Orientation orientation{ Orientation::Right };

			std::unique_ptr<Control> control;
		};
	}
}
