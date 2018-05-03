#include "StringId.hpp"

namespace engine
{
	namespace util
	{
		std::hash<std::string> StringId::_hasher;

		StringId::StringId()
			: _hash{ 0 }
		{
			// empty
		}

		StringId::StringId(const std::string &str)
			: _hash{ _hasher(str) }
#ifdef DEBUG
			, _str{ str }
#endif
		{
			// empty
		}

		bool StringId::operator ==(const StringId &other) const
		{
			return _hash == other._hash;
		}

		bool StringId::operator <(const StringId &other) const
		{
			return _hash < other._hash;
		}

#ifdef DEBUG
		StringId::operator const std::string &() const
		{
			return _str;
		}
#else
		StringId::operator std::size_t() const
		{
			return _hash;
		}
#endif
	}
}
