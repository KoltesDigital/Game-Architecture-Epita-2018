#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>

namespace engine
{
	Engine::Engine()
		: _graphicsManager{ *this }
		, _gameplayManager{ _graphicsManager, _inputManager, _physicsManager }
	{
	}

	bool Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			_startMap = configuration.child_value("start_map");

			return true;
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;

			return false;
		}
	}

	bool Engine::setUp()
	{
		if (!_graphicsManager.setUp())
		{
			return false;
		}

		if (!_physicsManager.setUp())
		{
			return false;
		}

		_gameplayManager.setUp();

		return true;
	}

	void Engine::tearDown()
	{
		_gameplayManager.tearDown();
		_physicsManager.tearDown();
		_graphicsManager.tearDown();
	}

	void Engine::run()
	{
		_running = true;

		_gameplayManager.loadMap(_startMap);

		sf::Clock clock;
		while (_running)
		{
			_deltaTime = clock.restart().asSeconds();

			_inputManager.clear();

			_physicsManager.update();
			_graphicsManager.pollEvents();
			_gameplayManager.update();

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
