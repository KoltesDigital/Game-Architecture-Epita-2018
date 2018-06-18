#pragma once

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <engine/serialization/TypeInfo.hpp>

namespace engine
{
	namespace serialization
	{
		class TypeRegistry
		{
		public:
			using CreateFunction = std::function<void *()>;

			struct Info
			{
				CreateFunction create;
				const TypeInfo &typeInfo;
			};

			template <typename T>
			void registerClass(const std::string &name)
			{
				auto pair = _infoByNames.insert(std::make_pair(name, Info
				{
					[]() -> void *
					{
						return new T;
					},
					TypeInfoValue<T *>::value
				}));
				assert(pair.second); // fails if name was already registered
			}

			const Info *getInfo(const std::string &name) const
			{
				auto it = _infoByNames.find(name);
				if (it != std::cend(_infoByNames))
				{
					return &it->second;
				}
				return nullptr;
			}

		private:
			using CreateFunction = std::function<void *()>;

			std::map<std::string, Info> _infoByNames;
		};
	}
}
