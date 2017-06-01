#pragma once

#include <pugixml/pugixml.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace serialization
	{
		class XMLLoader : public Serializer
		{
		public:
			XMLLoader(const std::string &filename);

			// Serializer
			void declare(const std::string &name, float &value) override;
			void declare(const std::string &name, int &value) override;
			void declare(const std::string &name, std::string &value) override;

			bool isLoaded() const;

		private:
			pugi::xml_document doc;
			pugi::xml_node rootNode;
		};
	}
}
