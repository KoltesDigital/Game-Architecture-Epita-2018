#include <gtest/gtest.h>

#include <engine/serialization/TypeRegistry.h>

namespace engine
{
	namespace serialization
	{
		struct Foo
		{
		};

		template <>
		void serialize<Foo>(Foo &, Serializer &)
		{
		}

		TEST(TypeRegistryTest, Create)
		{
			TypeRegistry registry;

			registry.registerClass<Foo>("foo");

			auto fooInfo = registry.getInfo("foo");
			ASSERT_TRUE(fooInfo);
			EXPECT_EQ(Type::SerializablePtr, fooInfo->typeInfo.type);
			auto foo{ fooInfo->create() };
			ASSERT_TRUE(foo);
			delete foo;

			auto barInfo = registry.getInfo("bar");
			EXPECT_FALSE(barInfo);
		}
	}
}
