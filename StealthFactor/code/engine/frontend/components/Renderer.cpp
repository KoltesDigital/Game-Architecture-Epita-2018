#include "Renderer.hpp"

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
			Renderer::Renderer(Entity &entity)
				: Component{ entity }
			{
			}

			Renderer::~Renderer()
			{
				clear();
			}

			void Renderer::onTransformChange()
			{
				if (_shapeListId)
				{
					auto transform = getEntity().getComponent<Transform>();
					getGraphicsManager().setShapeListInstanceMatrix(_shapeListId, transform->getMatrix());
				}
			}

			void Renderer::setShapeListName(const std::string &name)
			{
				clear();

				if (!name.empty())
				{
					_shapeListId = getGraphicsManager().createShapeListInstance(name);
					onTransformChange();
				}
			}

			void Renderer::clear()
			{
				if (_shapeListId)
				{
					getGraphicsManager().destroyShapeListInstance(_shapeListId);
					_shapeListId = 0;
				}
			}

			graphics::Manager &Renderer::getGraphicsManager() const
			{
				return getEntity().getContext().graphicsManager;
			}
		}
	}
}
