#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>

namespace engine
{
	namespace graphics
	{
		class ShapeDescriptorVisitor;

		struct ShapeDescriptor
		{
			float x;
			float y;
			sf::Color fillColor;
			sf::Color outlineColor;
			float outlineThickness;

			virtual void accept(ShapeDescriptorVisitor &visitor) = 0;
		};

		struct CircleDescriptor : ShapeDescriptor
		{
			float radius;

			void accept(ShapeDescriptorVisitor &visitor) override;
		};

		struct RectangleDescriptor : ShapeDescriptor
		{
			float width;
			float height;

			void accept(ShapeDescriptorVisitor &visitor) override;
		};

		class ShapeDescriptorVisitor
		{
		public:
			virtual void circle(CircleDescriptor &circleDescriptor) = 0;
			virtual void rectangle(RectangleDescriptor &rectangleDescriptor) = 0;
		};

		struct ShapeListDescriptor
		{
		public:
			using ShapeDescriptorPtr = std::unique_ptr<ShapeDescriptor>;
			using ShapeDescriptors = std::vector<ShapeDescriptorPtr>;

			bool load(const std::string &name);

			void visit(ShapeDescriptorVisitor &visitor);

			const ShapeDescriptors &getShapeDescriptors() const;

		private:
			ShapeDescriptors _shapeDescriptors;
		};
	}
}
