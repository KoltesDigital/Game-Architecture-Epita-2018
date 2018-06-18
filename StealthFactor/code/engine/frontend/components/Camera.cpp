#include "Camera.hpp"

#include <engine/graphics/GraphicsManager.hpp>
#include <engine/frontend/Entity.hpp>
#include <engine/frontend/EntityContext.hpp>
#include <engine/frontend/components/Transform.hpp>

namespace engine
{
	namespace frontend
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
