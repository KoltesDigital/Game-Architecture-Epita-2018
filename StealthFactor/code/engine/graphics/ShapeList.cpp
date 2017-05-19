#include "ShapeList.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <engine/graphics/ShapeListDescriptor.hpp>

namespace engine
{
	namespace graphics
	{
		bool ShapeList::load(const std::string &name)
		{
		public:
			ShapeListInstantiater(ShapeList::Shapes &shapes)
				: _shapes{ shapes }
			{
			}

			void circle(CircleDescriptor &circleDescriptor) override
			{
				auto shape{ new sf::CircleShape{ circleDescriptor.radius } };
				shape->setOrigin(circleDescriptor.radius, circleDescriptor.radius);

				processShape(circleDescriptor, shape);
			}

			void rectangle(RectangleDescriptor &rectangleDescriptor) override
			{
				auto shape{ new sf::RectangleShape{ sf::Vector2f{ rectangleDescriptor.width, rectangleDescriptor.height } } };
				shape->setOrigin(rectangleDescriptor.width / 2.f, rectangleDescriptor.height / 2.f);

				processShape(rectangleDescriptor, shape);
			}

		private:
			ShapeList::Shapes &_shapes;

			void processShape(ShapeDescriptor &shapeDescriptor, sf::Shape *shape)
			{
				shape->setPosition(shapeDescriptor.x, shapeDescriptor.y);
				shape->setFillColor(shapeDescriptor.fillColor);
				shape->setOutlineColor(shapeDescriptor.outlineColor);
				shape->setOutlineThickness(shapeDescriptor.outlineThickness);

				_shapes.emplace_back(shape);
			}
		};

		ShapeList::ShapeList(ShapeListDescriptor &descriptor)
		{
			ShapeListInstantiater instantiater{ _shapes };

			for (auto &shapeDescriptor : descriptor.getShapeDescriptors())
			{
				shapeDescriptor->accept(instantiater);
			}
		}

		const ShapeList::Shapes &ShapeList::getShapes() const
		{
			return _shapes;
		}
	}
}
