#pragma once

#include <memory>
#include <set>
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/graphics/CameraId.hpp>
#include <engine/graphics/ShapeListId.hpp>

namespace engine
{
	class EventListener;

	namespace assets
	{
		class Manager;
	}

	namespace graphics
	{
		class Camera;
		struct ShapeListInstance;

		class Manager
		{
		public:
			Manager(assets::Manager &assetsManager, EventListener &eventListener);
			~Manager();

			bool setUp();
			void tearDown();

			void pollEvents();

			void draw();

			// Cameras

			CameraId createCamera();
			void destroyCamera(CameraId id);

			void setCameraActive(CameraId id);
			void setCameraPosition(CameraId id, const sf::Vector2f &position);

			// ShapeListInstance

			ShapeListId createShapeListInstance(const std::string &name);
			void destroyShapeListInstance(ShapeListId id);

			void setShapeListInstanceMatrix(ShapeListId id, const sf::Transform &matrix);

		private:
			using CameraPtr = std::unique_ptr<Camera>;
			using ShapeListInstancePtr = std::unique_ptr<ShapeListInstance>;

			assets::Manager &_assetsManager;
			EventListener &_eventListener;

			sf::RenderWindow _window;

			std::set<CameraPtr> _cameras;
			Camera *_activeCamera{};

			std::set<ShapeListInstancePtr> _shapeListInstances;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;
		};
	}
}
