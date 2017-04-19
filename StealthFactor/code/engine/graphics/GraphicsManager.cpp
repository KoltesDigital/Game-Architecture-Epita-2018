#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/graphics/ViewProvider.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager::Manager(EventListener &eventListener, ViewProvider &viewProvider)
			: eventListener{ eventListener }
			, viewProvider{ viewProvider }
		{
		}

		bool Manager::setUp()
		{
			window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");

			if (!window.isOpen())
			{
				return false;
			}

			window.setVerticalSyncEnabled(true);

			return true;
		}

		void Manager::tearDown()
		{
			window.close();
		}

		void Manager::update()
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				eventListener.onEvent(event);
			}
		}

		void Manager::clear()
		{
			window.clear(sf::Color::Black);

			sf::View view{ viewProvider.getViewCenter(), sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT} };
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
	}
}
