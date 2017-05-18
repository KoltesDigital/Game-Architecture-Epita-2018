#include "Transform.hpp"

#include <engine/gameplay/Entity.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Transform::Transform(Entity &entity)
				: Component{ entity }
			{
			}

			const sf::Vector2f & Transform::getPosition() const
			{
				return _position;
			}

			void Transform::setPosition(const sf::Vector2f &newPosition)
			{
				_position = newPosition;
				updateMatrix();
			}

			float Transform::getRotation() const
			{
				return _rotation;
			}

			void Transform::setRotation(float newRotation)
			{
				_rotation = newRotation;
				updateMatrix();
			}

			const sf::Transform & Transform::getMatrix() const
			{
				return _matrix;
			}

			void Transform::updateMatrix()
			{
				_matrix = sf::Transform::Identity;
				_matrix.translate(_position);
				_matrix.rotate(_rotation);

				getEntity().onTransformChange();
			}
		}
	}
}
