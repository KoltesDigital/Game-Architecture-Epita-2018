#include <gtest/gtest.h>

#include <engine/serialization/XMLLoader.hpp>
#include <engine/gameplay/Archetype.hpp>

namespace engine
{
	namespace serialization
	{
		TEST(SerializationTest, LoadXML)
		{
			XMLLoader loader{ "archetypes/boss.xml" };
			ASSERT_TRUE(loader.isLoaded());

			gameplay::Archetype boss;
			boss.serialize(loader);
			EXPECT_STREQ("boss_lvl_42", boss.shapeListName.c_str());
			EXPECT_FLOAT_EQ(3.1f, boss.visionRadius);
			EXPECT_EQ(17, boss.shootDelay);
		}
	}
}
