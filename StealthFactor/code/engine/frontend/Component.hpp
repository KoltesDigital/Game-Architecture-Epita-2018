#pragma once

namespace engine
{
	namespace frontend
	{
		class Entity;

		class Component
		{
		public:
			virtual ~Component() = default;

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
