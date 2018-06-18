#pragma once

#include <vector>
#include <pugixml/pugixml.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace serialization
	{
		class TypeRegistry;

		class XMLLoader : public Serializer
		{
		public:
			XMLLoader(const std::string &filename, const TypeRegistry *registry = nullptr);

			bool isLoaded() const;

		protected:
			// Serializer
			bool beginName(const std::string &name) override;
			void endName() override;
			void process(void *value, const TypeInfo &typeInfo) override;

		private:
			const TypeRegistry *_registry;

			pugi::xml_document _doc;
			std::vector<pugi::xml_node> _nodes;
		};
	}
}
