#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/Camera.hpp>
#include <engine/graphics/ShapeListInstance.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager::Manager(EventListener &eventListener)
			: _eventListener{ eventListener }
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

		void Manager::draw()
		{
			_window.clear(sf::Color::Black);

			assert(_activeCamera);
			sf::View view{ _activeCamera->getPosition(), sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT } };
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

		CameraId Manager::createCamera()
		{
			auto camera{ new Camera() };
			_cameras.insert(CameraPtr{ camera });
			return camera;
		}

		void Manager::destroyCamera(CameraId id)
		{
			auto it = std::find_if(std::begin(_cameras), std::end(_cameras), [id](auto &camera)
			{
				return camera.get() == id;
			});
			assert(it != std::end(_cameras));
			_cameras.erase(it);
		}

		void Manager::setCameraActive(CameraId id)
		{
			assert(id);
			_activeCamera = id;
		}

		void Manager::setCameraPosition(CameraId id, const sf::Vector2f &position)
		{
			assert(id);
			auto camera = id;
			camera->setPosition(position);
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
	}
}
