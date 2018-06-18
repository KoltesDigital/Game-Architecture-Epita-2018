#pragma once

namespace engine
{
	namespace assets
	{
		class Manager;
	}

	namespace input
	{
		class Manager;
	}

	namespace backend
	{
		class ControlListener;

		struct ControlContext
		{
			assets::Manager &assetsManager;
			input::Manager &inputManager;
			ControlListener &controlListener;
		};
	}
}
