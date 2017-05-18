#pragma once

namespace engine
{
	namespace gameplay
	{
		class Entity;

		class Component
		{
		public:
			virtual ~Component() = default;

			virtual void update();
			virtual void onTransformChange();

			Entity &getEntity();
			const Entity &getEntity() const;

		protected:
			Component(Entity &entity);

		private:
			Entity &_entity;
		};
	}
}
