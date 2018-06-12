#include "ShapeListDescriptor.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>

namespace engine
{
	namespace graphics
	{
		void CircleDescriptor::accept(ShapeDescriptorVisitor &visitor)
		{
			visitor.circle(*this);
		}

		void RectangleDescriptor::accept(ShapeDescriptorVisitor &visitor)
		{
			visitor.rectangle(*this);
		}

		bool ShapeListDescriptor::load(const std::string & name)
		{
			std::stringstream filename;
			filename << "shapelists/" << name << ".xml";

			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

			if (result)
			{
				assert(!doc.empty());
				auto xmlShapeList = doc.first_child();

				for (auto &xmlShape : xmlShapeList.child("shapes").children())
				{
					ShapeDescriptorPtr shapeDescriptor;

					if (!std::strcmp(xmlShape.name(), "circle"))
					{
						auto circleDescriptor{ new CircleDescriptor };
						shapeDescriptor.reset(circleDescriptor);

						circleDescriptor->radius = std::stof(xmlShape.child_value("radius"));
					}

					if (!std::strcmp(xmlShape.name(), "rectangle"))
					{
						auto rectangleDescriptor{ new RectangleDescriptor };
						shapeDescriptor.reset(rectangleDescriptor);

						rectangleDescriptor->width = std::stof(xmlShape.child_value("width"));
						rectangleDescriptor->height = std::stof(xmlShape.child_value("height"));
					}

					shapeDescriptor->x = std::stof(xmlShape.child_value("x"));
					shapeDescriptor->y = std::stof(xmlShape.child_value("y"));

					shapeDescriptor->fillColor.r = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("r"));
					shapeDescriptor->fillColor.g = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("g"));
					shapeDescriptor->fillColor.b = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("b"));

					shapeDescriptor->outlineColor.r = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("r"));
					shapeDescriptor->outlineColor.g = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("g"));
					shapeDescriptor->outlineColor.b = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("b"));

					shapeDescriptor->outlineThickness = std::stof(xmlShape.child_value("outline_thickness"));

					_shapeDescriptors.push_back(std::move(shapeDescriptor));
				}

				return true;
			}
			else
			{
				std::cerr << "Shape list [" << name << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;

				return false;
			}
		}

		void ShapeListDescriptor::visit(ShapeDescriptorVisitor &visitor)
		{
			for (auto &shapeDesc : _shapeDescriptors)
			{
				shapeDesc->accept(visitor);
			}
		}

		const ShapeListDescriptor::ShapeDescriptors &ShapeListDescriptor::getShapeDescriptors() const
		{
			return _shapeDescriptors;
		}
	}
}
