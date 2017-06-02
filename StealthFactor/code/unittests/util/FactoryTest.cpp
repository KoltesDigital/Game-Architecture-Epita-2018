#include <gtest/gtest.h>

#include <engine/util/Factory.hpp>

namespace engine
{
	namespace util
	{
		struct Parent
		{
			virtual ~Parent() = default;
		};

		struct SpeA : Parent
		{
		};

		struct SpeB : Parent
		{
		};

		TEST(FactoryTest, Create)
		{
			Factory<Parent> factory;

			factory.registerClass<SpeA>("a");
			factory.registerClass<SpeB>("b");

			auto a = factory.create("a");
			EXPECT_TRUE(a);
			EXPECT_TRUE(dynamic_cast<SpeA*>(a.get()));
			EXPECT_FALSE(dynamic_cast<SpeB*>(a.get()));

			auto b = factory.create("b");
			EXPECT_TRUE(b);
			EXPECT_FALSE(dynamic_cast<SpeA*>(b.get()));
			EXPECT_TRUE(dynamic_cast<SpeB*>(b.get()));

			auto c = factory.create("c");
			EXPECT_FALSE(c);
		}
	}
}
