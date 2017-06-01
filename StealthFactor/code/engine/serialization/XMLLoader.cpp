#include "XMLLoader.hpp"

#include <iostream>

namespace engine
{
	namespace serialization
	{
		XMLLoader::XMLLoader(const std::string &filename)
		{
			auto result = doc.load_file(filename.c_str());
			if (result)
			{
				rootNode = doc.first_child();
			}
			else
			{
				std::cerr << "File [" << filename << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}
		}

		void XMLLoader::declare(const std::string &name, float &value)
		{
			value = std::stof(rootNode.child_value(name.c_str()));
		}

		void XMLLoader::declare(const std::string &name, int &value)
		{
			value = std::stoi(rootNode.child_value(name.c_str()));
		}

		void XMLLoader::declare(const std::string &name, std::string &value)
		{
			value = rootNode.child_value(name.c_str());
		}

		bool XMLLoader::isLoaded() const
		{
			return rootNode ? true : false;
		}
	}
}
