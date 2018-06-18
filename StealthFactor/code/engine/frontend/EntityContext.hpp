#pragma once

namespace engine
{
	namespace assets
	{
		class Manager;
	}

	namespace graphics
	{
		class Manager;
	}

	namespace frontend
	{
		struct EntityContext
		{
			assets::Manager &assetsManager;
			graphics::Manager &graphicsManager;
		};
	}
}
