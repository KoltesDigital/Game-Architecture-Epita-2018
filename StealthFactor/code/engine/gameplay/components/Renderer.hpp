#pragma once

#include <string>
#include <engine/graphics/ShapeListId.hpp>
#include <engine/gameplay/Component.hpp>

namespace engine
{
	namespace graphics
	{
		class Manager;
	}

	namespace gameplay
	{
		namespace components
		{
			class Renderer : public Component
			{
			public:
				Renderer(Entity &entity);
				virtual ~Renderer();

				void onTransformChange() override;

				void setShapeListName(const std::string &name);

			protected:
				graphics::Manager &getGraphicsManager() const;

			private:
				graphics::ShapeListId _shapeListId{};

				void clear();
			};
		}
	}
}
