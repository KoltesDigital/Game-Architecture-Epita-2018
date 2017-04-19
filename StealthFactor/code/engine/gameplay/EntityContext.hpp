#pragma once

namespace engine
{
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
			graphics::Manager &graphicsManager;
			input::Manager &inputManager;
			physics::Manager &physicsManager;
			EntityListener &entityListener;
		};
	}
}
