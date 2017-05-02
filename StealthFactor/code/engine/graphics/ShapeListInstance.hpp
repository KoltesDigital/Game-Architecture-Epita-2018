#pragma once

#include <engine/graphics/ShapeList.hpp>

namespace engine
{
	namespace graphics
	{
		struct ShapeListInstance
		{
			ShapeList shapeList;
			sf::Transform transform;
		};
	}
}
