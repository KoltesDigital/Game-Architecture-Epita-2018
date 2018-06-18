#include <gtest/gtest.h>

#include <memory>
#include <engine/backend/ControlContext.hpp>
#include <engine/backend/Map.hpp>
#include <engine/backend/MapDescriptor.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/XMLLoader.hpp>

namespace engine
{
	namespace backend
	{
		class MapTest : public ::testing::Test
		{
		protected:
			// ControlContext context;

			std::unique_ptr<Map> map;

			void SetUp() override
			{
				serialization::XMLLoader loader{ "maps/map.xml" };
				ASSERT_TRUE(loader.isLoaded());

				MapDescriptor descriptor;
				serialization::serialize(descriptor, loader);

				//map.reset(new Map{ descriptor, context });
			}
		};

		TEST(MapTest, Move)
		{

		}
	}
}
