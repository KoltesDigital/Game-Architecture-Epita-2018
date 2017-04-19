#pragma once

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Player;
		}

		class EntityListener
		{
		public:
			virtual void loadNextMap() = 0;
			virtual void gameOver() = 0;
			virtual const entities::Player &getPlayer() const = 0;
		};
	}
}