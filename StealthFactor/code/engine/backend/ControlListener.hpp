#pragma once

namespace engine
{
	namespace backend
	{
		struct Character;

		class ControlListener
		{
		public:
			virtual void characterMoved(Character &character) = 0;
			virtual void characterSkipped(Character &character) = 0;
			virtual void gameOver() = 0;
		};
	}
}
