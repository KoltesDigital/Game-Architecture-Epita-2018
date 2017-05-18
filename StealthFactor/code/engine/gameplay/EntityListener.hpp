#pragma once

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class Player;
		}

		class EntityListener
		{
		public:
			virtual void loadNextMap() = 0;
			virtual void gameOver() = 0;
			virtual const components::Player &getPlayer() const = 0;
		};
	}
}