#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace engine
{
	class EventListener;

	namespace graphics
	{
		class ShapeList;
		class ViewProvider;

		class Manager
		{
		public:
			Manager(EventListener &eventListener, ViewProvider &viewProvider);

			bool setUp();
			void tearDown();

			void update();

			void clear();
			void draw(const ShapeList &shapeList, const sf::Transform &transform);
			void display();

		private:
			EventListener &eventListener;
			ViewProvider &viewProvider;

			sf::RenderWindow window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;
		};
	}
}
