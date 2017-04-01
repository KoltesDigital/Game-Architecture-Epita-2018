#pragma once

#include <string>

namespace engine
{
	class Engine
	{
	public:
		void loadConfiguration();

		void run();
		float getDeltaTime() const;

		void exit();

		static Engine &getInstance();

	private:
		bool running;
		float deltaTime;

		// Configuration
		std::string startMap;

		static Engine *instance;
	};
}
