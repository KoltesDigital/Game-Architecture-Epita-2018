#pragma once

#include <string>
#include <engine/assets/AssetsManager.hpp>
#include <engine/backend/BackendManager.hpp>
#include <engine/frontend/FrontendManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/Configuration.hpp>
#include <engine/EventListener.hpp>

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
		backend::Manager _backendManager;
		frontend::Manager _frontendManager;
		graphics::Manager _graphicsManager;
		input::Manager _inputManager;

		bool _running;
		float _deltaTime;

		// Configuration
		Configuration _configuration;
	};
}
