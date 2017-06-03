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

		template <>
		std::string getClassName<Foo>()
		{
			return "foo";
		}

		TEST(TypeRegistryTest, Create)
		{
			TypeRegistry registry;

			registry.registerClass<Foo>();

			auto fooInfo = registry.getInfo(getClassName<Foo>());
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
