#include "StringId.hpp"

namespace engine
{
	namespace util
	{
		std::hash<std::string> StringId::hasher;

		StringId::StringId()
			: hash{ 0 }
		{
			// empty
		}

		StringId::StringId(const std::string &str)
			: hash{ hasher(str) }
#ifdef DEBUG
			, str{ str }
#endif
		{
			// empty
		}

		bool StringId::operator ==(const StringId &other) const
		{
			return hash == other.hash;
		}

		bool StringId::operator <(const StringId &other) const
		{
			return hash < other.hash;
		}

#ifdef DEBUG
		StringId::operator const std::string &() const
		{
			return str;
		}
#else
		StringId::operator std::size_t() const
		{
			return hash;
		}
#endif
	}
}
