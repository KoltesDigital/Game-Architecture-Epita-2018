#include <gtest/gtest.h>

#include <iostream>
#include <platform/SetWorkingDirectory.hpp>

class EngineEnvironment : public ::testing::Environment
{
public:
	void SetUp() override
	{
		ASSERT_TRUE(platform::SetWorkingDirectory("../../../code/unittests/fixtures"));
	}
};

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new EngineEnvironment);
	return RUN_ALL_TESTS();
}
