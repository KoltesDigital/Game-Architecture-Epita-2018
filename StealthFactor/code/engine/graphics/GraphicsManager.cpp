#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeListInstance.hpp>
#include <engine/graphics/ViewProvider.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager::Manager(EventListener &eventListener, ViewProvider &viewProvider)
			: _eventListener{ eventListener }
			, _viewProvider{ viewProvider }
		{
		}

		Manager::~Manager()
		{
		}

		bool Manager::setUp()
		{
			_window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");

			if (!_window.isOpen())
			{
				return false;
			}

			_window.setVerticalSyncEnabled(true);

			return true;
		}

		void Manager::tearDown()
		{
			assert(_shapeListInstances.size() == 0);

			_window.close();
		}

		void Manager::pollEvents()
		{
			sf::Event event;
			while (_window.pollEvent(event))
			{
				_eventListener.onEvent(event);
			}
		}

		ShapeListId Manager::createShapeListInstance(const std::string &name)
		{
			auto instance{ new ShapeListInstance() };
			ShapeListInstancePtr instanceUPtr{ instance };

			if (!instance->shapeList.load(name))
			{
				return nullptr;
			}

			_shapeListInstances.insert(std::move(instanceUPtr));
			return instance;
		}

		void Manager::destroyShapeListInstance(ShapeListId id)
		{
			auto it = std::find_if(std::begin(_shapeListInstances), std::end(_shapeListInstances), [id](auto &instance)
			{
				return instance.get() == id;
			});
			assert(it != std::end(_shapeListInstances));
			_shapeListInstances.erase(it);
		}

		void Manager::setShapeListInstanceMatrix(ShapeListId id, const sf::Transform &matrix)
		{
			// TODO Optimize (kd-tree...)
			ShapeListInstance *instance = id;
			instance->transform = matrix;
		}

		void Manager::draw()
		{
			_window.clear(sf::Color::Black);

			sf::View view{ _viewProvider.getViewCenter(), sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT} };
			_window.setView(view);

			for (auto &instance : _shapeListInstances)
			{
				sf::RenderStates renderStates{ instance->transform };
				for (auto &shape : instance->shapeList.getShapes())
				{
					_window.draw(*shape, renderStates);
				}
			}

			_window.display();
		}
	}
}
