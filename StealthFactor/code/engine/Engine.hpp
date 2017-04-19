#pragma once

#include <string>
#include <engine/EventListener.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>

namespace engine
{
	class Engine : public EventListener
	{
	public:
		Engine();

		bool loadConfiguration();

		bool setUp();
		void tearDown();

		void run();
		float getDeltaTime() const;

		// EventListener
		void onEvent(const sf::Event &event) override;

	private:
		gameplay::Manager gameplayManager;
		graphics::Manager graphicsManager;
		input::Manager inputManager;
		physics::Manager physicsManager;

		bool running;
		float deltaTime;

		// Configuration
		std::string startMap;
	};
}
