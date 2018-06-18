#include "XMLLoader.hpp"

#include <iostream>
#include <engine/serialization/TypeRegistry.h>

namespace engine
{
	namespace serialization
	{
		XMLLoader::XMLLoader(const std::string &filename, const TypeRegistry *registry)
			: _registry{ registry }
		{
			auto result = _doc.load_file(filename.c_str());
			if (result)
			{
				_nodes.push_back(_doc.first_child());
			}
			else
			{
				std::cerr << "File [" << filename << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}
		}

		bool XMLLoader::isLoaded() const
		{
			return !_nodes.empty();
		}

		bool XMLLoader::beginName(const std::string & name)
		{
			auto currentNode{ _nodes.back() };

			auto node{ currentNode.child(name.c_str()) };
			if (!node)
			{
				return false;
			}

			_nodes.push_back(node);
			return true;
		}

		void XMLLoader::endName()
		{
			_nodes.pop_back();
		}

		void XMLLoader::process(void *value, const TypeInfo &typeInfo)
		{
			auto currentNode{ _nodes.back() };

			switch (typeInfo.type)
			{
			case Type::UnsignedChar:
				*reinterpret_cast<unsigned char *>(value) = (unsigned char)std::stoi(currentNode.child_value());
				break;

			case Type::Int:
				*reinterpret_cast<int *>(value) = std::stoi(currentNode.child_value());
				break;

			case Type::Float:
				*reinterpret_cast<float *>(value) = std::stof(currentNode.child_value());
				break;

			case Type::String:
				*reinterpret_cast<std::string *>(value) = currentNode.child_value();
				break;

			case Type::Vector:
			{
				auto methods{ reinterpret_cast<VectorMethods *>(typeInfo.methods) };
				auto &itemTypeInfo{ methods->getItemTypeInfo() };

				auto childNodes{ currentNode.children() };
				methods->setSize(value, std::distance(std::cbegin(childNodes), std::cend(childNodes)));

				std::size_t i{ 0 };
				for (auto &childNode : childNodes)
				{
					_nodes.push_back(childNode);
					process(methods->getValueAt(value, i), itemTypeInfo);
					_nodes.pop_back();
					++i;
				}
				break;
			}

			case Type::SerializablePtr:
			{
				if (_registry)
				{
					auto info{ _registry->getInfo(currentNode.name()) };
					if (info)
					{
						*reinterpret_cast<void **>(value) = info->create();
						Serializer::process(value, info->typeInfo);
					}
				}
				else
				{
					auto methods{ reinterpret_cast<SerializableMethods *>(typeInfo.methods) };
					*reinterpret_cast<void **>(value) = methods->create();
					Serializer::process(value, typeInfo);
				}
				break;
			}

			default:
				Serializer::process(value, typeInfo);
				break;
			}
		}
	}
}
