#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <engine/frontend/Component.hpp>

namespace engine
{
	namespace frontend
	{
		namespace components
		{
			class Transform : public Component
			{
			public:
				Transform(Entity &entity);

				const sf::Vector2f &getPosition() const;
				void setPosition(const sf::Vector2f &newPosition);

				float getRotation() const;
				void setRotation(float newRotation);

				const sf::Transform &getMatrix() const;

			private:
				sf::Vector2f _position{};
				float _rotation{ 0.f };
				sf::Transform _matrix;

				void updateMatrix();
			};
		}
	}
}
