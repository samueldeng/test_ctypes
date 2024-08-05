// g++ main.cpp -o main --std c++17 -I./ -L./trade_client/ -Wl,-rpath ./trade_client -ltrade_client -lpthread
#include <trade_client/trade_client.hpp>
#include <iostream>

void my_func(trade::Message messages)
{
    std::cout << "call my_func" << std::endl;
}

int main()
{
    trade::TradeClient trade_client;
    trade_client.Start(&my_func);
    trade_client.Join();
}
