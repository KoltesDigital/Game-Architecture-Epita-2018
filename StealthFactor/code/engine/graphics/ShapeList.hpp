#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics/Shape.hpp>

namespace engine
{
	namespace graphics
	{
		class ShapeList
		{
		public:
			using ShapePtr = std::unique_ptr<sf::Shape>;
			using Shapes = std::vector<ShapePtr>;

			bool load(const std::string &name);

			const Shapes &getShapes() const;

		private:
			Shapes _shapes;
		};
	}
}
