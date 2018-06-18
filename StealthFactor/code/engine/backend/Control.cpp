#include "Control.hpp"

namespace engine
{
	namespace backend
	{
		Control::Control(Character &character, ControlContext &context)
			: _character{ character }
			, _context{ context }
		{
		}

		Character &Control::getCharacter() const
		{
			return _character;
		}

		ControlContext &Control::getContext() const
		{
			return _context;
		}
	}
}
