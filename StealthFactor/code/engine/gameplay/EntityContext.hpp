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

	namespace input
	{
		class Manager;
	}

	namespace physics
	{
		class Manager;
	}

	namespace gameplay
	{
		class EntityListener;

		struct EntityContext
		{
			assets::Manager &assetsManager;
			graphics::Manager &graphicsManager;
			input::Manager &inputManager;
			physics::Manager &physicsManager;
			EntityListener &entityListener;
		};
	}
}
