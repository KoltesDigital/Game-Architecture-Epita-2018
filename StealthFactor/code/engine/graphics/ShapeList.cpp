#include "ShapeList.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace engine
{
	namespace graphics
	{
		bool ShapeList::load(const std::string &name)
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
					if (!std::strcmp(xmlShape.name(), "circle"))
					{
						float x = std::stof(xmlShape.child_value("x"));
						float y = std::stof(xmlShape.child_value("y"));
						float radius = std::stof(xmlShape.child_value("radius"));

						sf::Color fillColor{};
						fillColor.r = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("r"));
						fillColor.g = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("g"));
						fillColor.b = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("b"));

						sf::Color outlineColor{};
						outlineColor.r = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("r"));
						outlineColor.g = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("g"));
						outlineColor.b = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("b"));

						float outlineThickness = std::stof(xmlShape.child_value("outline_thickness"));

						auto shape = new sf::CircleShape{ radius };
						shape->setOrigin(radius, radius);
						shape->setPosition(x, y);
						shape->setFillColor(fillColor);
						shape->setOutlineColor(outlineColor);
						shape->setOutlineThickness(outlineThickness);

						_shapes.push_back(shape);
					}

					if (!std::strcmp(xmlShape.name(), "rectangle"))
					{
						float x = std::stof(xmlShape.child_value("x"));
						float y = std::stof(xmlShape.child_value("y"));
						float width = std::stof(xmlShape.child_value("width"));
						float height = std::stof(xmlShape.child_value("height"));

						sf::Color fillColor{};
						fillColor.r = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("r"));
						fillColor.g = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("g"));
						fillColor.b = (sf::Uint8)std::stoi(xmlShape.child("fill_color").child_value("b"));

						sf::Color outlineColor{};
						outlineColor.r = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("r"));
						outlineColor.g = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("g"));
						outlineColor.b = (sf::Uint8)std::stoi(xmlShape.child("outline_color").child_value("b"));

						float outlineThickness = std::stof(xmlShape.child_value("outline_thickness"));

						auto shape = new sf::RectangleShape{ sf::Vector2f{width, height} };
						shape->setOrigin(width / 2.f, height / 2.f);
						shape->setPosition(x, y);
						shape->setFillColor(fillColor);
						shape->setOutlineColor(outlineColor);
						shape->setOutlineThickness(outlineThickness);

						_shapes.push_back(shape);
					}
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

		const ShapeList::Shapes &ShapeList::getShapes() const
		{
			return _shapes;
		}
	}
}
