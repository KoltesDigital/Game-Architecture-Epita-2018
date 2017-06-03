#include "ShapeListDescriptor.hpp"

#include <engine/assets/AssetTypeRegistry.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace graphics
	{
		void ShapeDescriptor::accept(ShapeDescriptorVisitor &)
		{
			assert(false);
		}

		void CircleDescriptor::accept(ShapeDescriptorVisitor &visitor)
		{
			visitor.circle(*this);
		}

		void RectangleDescriptor::accept(ShapeDescriptorVisitor &visitor)
		{
			visitor.rectangle(*this);
		}

		void ShapeListDescriptor::visit(ShapeDescriptorVisitor &visitor) const
		{
			for (auto &shapeDesc : shapeDescriptors)
			{
				shapeDesc->accept(visitor);
			}
		}
	}

	namespace assets
	{
		template <>
		struct AssetTypeRegistry<graphics::ShapeListDescriptor>
		{
			static serialization::TypeRegistry value;

			static struct Init
			{
				Init()
				{
					value.registerClass<graphics::CircleDescriptor>();
					value.registerClass<graphics::RectangleDescriptor>();
				}
			} init;
		};

		serialization::TypeRegistry AssetTypeRegistry<graphics::ShapeListDescriptor>::value;
		AssetTypeRegistry<graphics::ShapeListDescriptor>::Init AssetTypeRegistry<graphics::ShapeListDescriptor>::init;
	}

	namespace serialization
	{
		template <>
		void serialize<graphics::ShapeDescriptor>(graphics::ShapeDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serializer.declare("x", descriptor.x);
			serializer.declare("y", descriptor.y);
			serializer.declare("fill_color", descriptor.fillColor);
			serializer.declare("outline_color", descriptor.outlineColor);
			serializer.declare("outline_thickness", descriptor.outlineThickness);
		}

		template <>
		std::string getClassName<graphics::ShapeDescriptor>()
		{
			assert(false);
			return "";
		}

		template <>
		void serialize<graphics::CircleDescriptor>(graphics::CircleDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serialize(static_cast<graphics::ShapeDescriptor &>(descriptor), serializer);
			serializer.declare("radius", descriptor.radius);
		}

		template <>
		std::string getClassName<graphics::CircleDescriptor>()
		{
			return "circle";
		}

		template <>
		void serialize<graphics::RectangleDescriptor>(graphics::RectangleDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serialize(static_cast<graphics::ShapeDescriptor &>(descriptor), serializer);
			serializer.declare("width", descriptor.width);
			serializer.declare("height", descriptor.height);
		}

		template <>
		std::string getClassName<graphics::RectangleDescriptor>()
		{
			return "rectangle";
		}

		template <>
		void serialize<graphics::ShapeListDescriptor>(graphics::ShapeListDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serializer.declare("shapes", descriptor.shapeDescriptors);
		}
	}
}
