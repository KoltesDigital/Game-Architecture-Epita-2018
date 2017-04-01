#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager *Manager::instance = nullptr;

		Manager::Manager()
		{
			window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");

			window.setVerticalSyncEnabled(true);

			sf::View view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
			window.setView(view);
		}

		Manager::~Manager()
		{
			window.close();
		}

		void Manager::update()
		{
			input::Manager::getInstance().clear();

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					Engine::getInstance().exit();
					break;

				case sf::Event::KeyPressed:
					input::Manager::getInstance().onKeyPressed(event.key);
					break;

				case sf::Event::KeyReleased:
					input::Manager::getInstance().onKeyReleased(event.key);
					break;
				}
			}
		}

		void Manager::clear()
		{
			window.clear(sf::Color::Black);

			sf::View view{ gameplay::Manager::getInstance().getViewCenter(), sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT} };
			window.setView(view);
		}

		void Manager::draw(const ShapeList &shapeList, const sf::Transform &transform)
		{
			sf::RenderStates renderStates{ transform };
			for (auto shape : shapeList.getShapes())
			{
				window.draw(*shape, renderStates);
			}
		}

		void Manager::display()
		{
			window.display();
		}

		bool Manager::hasFocus() const
		{
			return window.hasFocus();
		}

		Manager &Manager::getInstance()
		{
			if (!instance)
				instance = new Manager();

			return *instance;
		}
	}
}
