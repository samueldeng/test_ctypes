// test.cpp
// Linux: g++ trade_client.cpp -o libtrade_client.so --std c++17 -shared -fPIC -Wl,-rpath ./
// OSX: g++ trade_client.cpp -o libtrade_client.dylib --std c++17 -shared -fPIC -Wl,-rpath ./
#include "trade_client.hpp"

#include <iostream>

namespace trade
{

TradeClient::TradeClient()
{
    packet_a_list_[0] = {'a', 11, 21, {'a', 'b', 'c', ' ', ' '}, 41, 51};
    packet_a_list_[1] = {'b', 12, 22, {'e', 'e', 'f', ' ', ' '}, 42, 52};
    packet_a_list_[2] = {'c', 13, 23, {'g', 'h', 'i', ' ', ' '}, 43, 53};
    packet_a_list_[3] = {'d', 14, 24, {'j', 'k', 'l', ' ', ' '}, 44, 54};
    packet_a_list_[4] = {'e', 15, 25, {'m', 'n', 'o', ' ', ' '}, 45, 55};

    messages_list_[0] = {0, 0, reinterpret_cast<char*>(&packet_a_list_[0]), 0};
    messages_list_[1] = {1, 1, reinterpret_cast<char*>(&packet_a_list_[1]), 1};
    messages_list_[2] = {2, 2, reinterpret_cast<char*>(&packet_a_list_[2]), 2};
    messages_list_[3] = {3, 3, reinterpret_cast<char*>(&packet_a_list_[3]), 3};
    messages_list_[4] = {4, 4, reinterpret_cast<char*>(&packet_a_list_[4]), 4};
}

void TradeClient::Start(callback_functype callback)
{
    callback_ = callback;
    status_ = trade_client_status::running;
    thread_ = std::thread(&TradeClient::Run, this);
}

void TradeClient::Join() { thread_.join(); }

void TradeClient::Stop() 
{
    status_ = trade_client_status::stopped;
}

std::uint64_t trade::TradeClient::Send(Message message)
{
    if (message.data == nullptr) 
    {
        return error_code::failed;
    }

    if (message.type == 0)
    {
        return error_code::failed2;
    }

    std::cout << "-----trade::TradeClient::Send: " << message.type << " " << message.length << " " << message.data << " " <<  message.checksum << std::endl;
    return error_code::success;
}

void TradeClient::Run()
{
    while (status_ == trade_client_status::running)
    {
        static int i = 0;
        // std::cout << i_ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        callback_(messages_list_[(i++) % 5 ]);
    }
}

};

