#pragma once

#include <string>

namespace engine
{
	namespace backend
	{
		struct Character;
		struct ControlContext;

		class Control
		{
		public:
			Control(Character &character, ControlContext &context);
			virtual ~Control() = default;

			virtual void update() = 0;

			virtual std::string getPrefabName() const = 0;

		protected:
			Character &getCharacter() const;
			ControlContext &getContext() const;

		private:
			Character &_character;
			ControlContext &_context;
		};
	}
}
