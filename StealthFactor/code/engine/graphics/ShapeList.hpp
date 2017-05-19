#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics/Shape.hpp>

namespace engine
{
	namespace graphics
	{
		struct ShapeListDescriptor;

		class ShapeList
		{
		public:
			using ShapePtr = std::unique_ptr<sf::Shape>;
			using Shapes = std::vector<ShapePtr>;

			ShapeList(ShapeListDescriptor &descriptor);

			const Shapes &getShapes() const;

		private:
			Shapes _shapes;
		};
	}
}
