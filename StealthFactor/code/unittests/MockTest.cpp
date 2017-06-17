#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Listener
{
public:
	virtual void onFoo() = 0;
};

class FooCommand
{
public:
	FooCommand(Listener &listener)
		: _listener{ listener }
	{}

	void execute()
	{
		_listener.onFoo();
	}

private:
	Listener & _listener;
};

class MockListener : public Listener
{
public:
	MOCK_METHOD0(onFoo, void());
};

TEST(CommandTest, Execute)
{
	MockListener lst;
	EXPECT_CALL(lst, onFoo()).Times(1);

	FooCommand cmd{ lst };
	cmd.execute();
}
