// test.cpp
// Linux: g++ trade_client.cpp -o libtrade_client.so --std c++17 -shared -fPIC -Wl,-rpath ./
// OSX: g++ trade_client.cpp -o libtrade_client.dylib --std c++17 -shared -fPIC -Wl,-rpath ./
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

