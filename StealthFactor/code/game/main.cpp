#include <iostream>
#include <cli.hpp>
#include <platform/SetWorkingDirectory.hpp>
#include <engine/Engine.hpp>

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

	engine::Engine engine{};

	if (!engine.loadConfiguration())
	{
		return EXIT_FAILURE;
	}

	if (!engine.setUp())
	{
		engine.tearDown();
		return EXIT_FAILURE;
	}

	engine.run();
	engine.tearDown();

	return EXIT_SUCCESS;
}
