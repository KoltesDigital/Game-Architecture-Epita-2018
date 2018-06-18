#pragma once

#include <string>
#include <engine/EventListener.hpp>
#include <engine/assets/AssetsManager.hpp>
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
		assets::Manager _assetsManager;
		gameplay::Manager _gameplayManager;
		graphics::Manager _graphicsManager;
		input::Manager _inputManager;
		physics::Manager _physicsManager;

		bool _running;
		float _deltaTime;

		// Configuration
		std::string _startMap;
	};
}
