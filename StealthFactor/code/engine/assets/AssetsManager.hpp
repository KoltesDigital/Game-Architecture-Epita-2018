#pragma once

#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <engine/assets/AssetTypeRegistry.hpp>
#include <engine/serialization/XMLLoader.hpp>

namespace engine
{
	namespace assets
	{
		struct Asset;

		class Manager
		{
		public:
			Manager();
			~Manager();

			template <typename Type,
				typename = std::enable_if_t<std::is_base_of<Asset, Type>::value>>
			const Type *getAsset(const std::string &name)
			{
				auto it = _assetByNames.find(name);
				if (it != std::cend(_assetByNames))
				{
					return reinterpret_cast<const Type *>(it->second.get());
				}

				serialization::XMLLoader loader{ name, &AssetTypeRegistry<Type>::value };
				if (!loader.isLoaded())
				{
					return nullptr;
				}

				auto asset{ new Type() };
				serialization::serialize(*asset, loader);

				_assetByNames.insert(std::make_pair(name, AssetPtr{ asset }));
				return asset;
			}

		private:
			using AssetPtr = std::unique_ptr<Asset>;

			std::map<std::string, AssetPtr> _assetByNames;
		};
	}
}
