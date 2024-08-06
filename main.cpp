// Linux: g++ main.cpp -o main --std c++17 -I./ -L./trade_client/ -Wl,-rpath ./trade_client -ltrade_client -lpthread
// ./main

// 
// OSX Run: DYLD_LIBRARY_PATH=$PWD/trade_client ./main

#include <trade_client/trade_client_api.hpp>
#include <iostream>

#include <unistd.h>

void my_func(Message messages)
{
    std::cout << "call my_func" << std::endl;
}

int main()
{
    start_trade_client(&my_func);
    sleep(5);
    stop_trade_client();
}
