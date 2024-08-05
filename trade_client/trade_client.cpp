// test.cpp
// Linux: g++ -o trade_client.so --std c++17 -shared -fPIC trade_client.cpp
// OSX: g++ -o libtrade_client.dylib --std c++17 -shared -fPIC trade_client.cpp
#include "./trade_client.hpp"

namespace trade
{

TradeClient::TradeClient() {}

void TradeClient::Start(callback_functype callback)
{
    thread_ = std::thread(&TradeClient::Run, this);
    callback_ = callback;
}

void TradeClient::Join() { thread_.join(); }

void TradeClient::Stop() {}

void TradeClient::Run()
{
    while (true)
    {
        static int i = 0;
        // std::cout << i_ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        callback_(messages[i++]);
    }
}

};

