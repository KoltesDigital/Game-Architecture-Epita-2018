#include <iostream>
#include <cli.hpp>
#include <SFML/System/Thread.hpp>
#include <platform/SetWorkingDirectory.hpp>
#include <engine/Engine.hpp>

void launchGame()
{
	engine::Engine engine{};

	if (!engine.loadConfiguration())
	{
		return;
	}

	if (!engine.setUp())
	{
		engine.tearDown();
		return;
	}

	engine.run();
	engine.tearDown();
}

int main(int argc, const char **argv)
{
	cli::Parser parser(argc, argv);

	parser.help()
		<< R"(Stealth Factor)";

	auto dataPath = parser.option("data")
		.description("Path to data directory")
		.defaultValue("data")
		.getValue();

	if (!platform::SetWorkingDirectory(dataPath))
	{
		std::cerr << "Unable to set data directory." << std::endl;
		return EXIT_FAILURE;
	}

	sf::Thread t1{ &launchGame };
	t1.launch();

	sf::Thread t2{ &launchGame };
	// t2.launch();

	return EXIT_SUCCESS;
}
