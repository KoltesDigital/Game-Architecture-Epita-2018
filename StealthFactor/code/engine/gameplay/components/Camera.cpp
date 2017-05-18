#include "Camera.hpp"

#include <engine/graphics/GraphicsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/components/Transform.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Camera::Camera(Entity &entity)
				: Component{ entity }
			{
				_cameraId = getGraphicsManager().createCamera();
			}

			Camera::~Camera()
			{
				getGraphicsManager().destroyCamera(_cameraId);
			}

			void Camera::onTransformChange()
			{
				auto transform = getEntity().getComponent<Transform>();
				auto &position = transform->getPosition();
				getGraphicsManager().setCameraPosition(_cameraId, position);
			}

			void Camera::setActive()
			{
				getGraphicsManager().setCameraActive(_cameraId);
			}

			graphics::Manager &Camera::getGraphicsManager() const
			{
				return getEntity().getContext().graphicsManager;
			}
		}
	}
}
