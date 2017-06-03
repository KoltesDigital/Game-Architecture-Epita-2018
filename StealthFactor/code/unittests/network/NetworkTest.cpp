#include <gtest/gtest.h>

#include <string>
#include <engine/network/NetworkManager.hpp>
#include <engine/network/messages/Chat.hpp>

namespace engine
{
	namespace network
	{
		TEST(NetworkTest, SendAndReceive)
		{
			Manager mgr1, mgr2;

			messages::Chat sentMessage;
			sentMessage.text = "hello";
			mgr1.broadcast(sentMessage);

			auto receivedMessage = mgr2.receive();
			ASSERT_TRUE(receivedMessage);
			ASSERT_TRUE(dynamic_cast<messages::Chat *>(receivedMessage.get()));
			EXPECT_STREQ("hello", dynamic_cast<messages::Chat *>(receivedMessage.get())->text.c_str());

			EXPECT_FALSE(mgr1.receive());
			EXPECT_FALSE(mgr2.receive());
		}
	}
}
