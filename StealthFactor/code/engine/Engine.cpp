#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>

namespace engine
{
	Engine::Engine()
		: _graphicsManager{ _assetsManager, *this }
		, _backendManager{ _frontendManager, _assetsManager, _inputManager }
		, _frontendManager{ _assetsManager, _graphicsManager }
	{
	}

	bool Engine::loadConfiguration()
	{
		serialization::XMLLoader loader{ "configuration.xml" };
		serialization::serialize(_configuration, loader);
		return loader.isLoaded();
	}

	bool Engine::setUp()
	{
		if (!_graphicsManager.setUp())
		{
			return false;
		}

		_frontendManager.setUp();

		return true;
	}

	void Engine::tearDown()
	{
		_frontendManager.tearDown();
		_graphicsManager.tearDown();
	}

	void Engine::run()
	{
		_running = true;

		_backendManager.loadMap(_configuration.startMap);

		sf::Clock clock;
		while (_running)
		{
			_deltaTime = clock.restart().asSeconds();

			_inputManager.clear();

			_graphicsManager.pollEvents();

			_backendManager.update();

			_graphicsManager.draw();
		}
	}

	float Engine::getDeltaTime() const
	{
		return _deltaTime;
	}

	void Engine::onEvent(const sf::Event &event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_running = false;
			break;

		case sf::Event::LostFocus:
			_inputManager.setActive(false);
			break;

		case sf::Event::GainedFocus:
			_inputManager.setActive(true);
			break;

		case sf::Event::KeyPressed:
			_inputManager.onKeyPressed(event.key);
			break;

		case sf::Event::KeyReleased:
			_inputManager.onKeyReleased(event.key);
			break;
		}
	}
}
