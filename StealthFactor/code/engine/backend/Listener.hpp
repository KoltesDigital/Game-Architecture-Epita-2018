#pragma once

namespace engine
{
	namespace backend
	{
		struct Character;
		struct Map;

		class Listener
		{
		public:
			virtual void onMapLoaded(Map &map) = 0;
			virtual void onCharacterMoved(const Character &character) = 0;
		};
	}
}
