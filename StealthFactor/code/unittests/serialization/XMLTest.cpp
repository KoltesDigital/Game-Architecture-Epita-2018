#include <gtest/gtest.h>

#include <engine/assets/AssetTypeRegistry.hpp>
#include <engine/backend/Archetype.hpp>
#include <engine/graphics/ShapeListDescriptor.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/XMLLoader.hpp>

namespace engine
{
	namespace serialization
	{
		TEST(XMLTest, LoadSimple)
		{
			XMLLoader loader{ "archetypes/boss.xml" };
			ASSERT_TRUE(loader.isLoaded());

			backend::Archetype boss;
			serialize(boss, loader);
			EXPECT_STREQ("boss_lvl_42", boss.prefabName.c_str());
			EXPECT_FLOAT_EQ(3.1f, boss.visionRadius);
			EXPECT_EQ(17, boss.shootDelay);
		}

		TEST(XMLTest, LoadCollection)
		{
			XMLLoader loader{ "shapelists/circle_2_rectangle_3_5.xml", &assets::AssetTypeRegistry<graphics::ShapeListDescriptor>::value };
			ASSERT_TRUE(loader.isLoaded());

			graphics::ShapeListDescriptor descriptor;
			serialize(descriptor, loader);

			auto &shapes = descriptor.shapeDescriptors;
			ASSERT_EQ(2, shapes.size());
		}
	}
}
