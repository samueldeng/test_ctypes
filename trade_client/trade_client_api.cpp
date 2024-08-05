// g++ -o libtrade_client_api.dylib --std c++17 -shared -fPIC trade_client_api.cpp -L./ -ltrade_client 

#include "./trade_client.hpp"

extern "C"
{
    trade::TradeClient *get_trade_client_instance()
    {
        static trade::TradeClient trade_client;
        return &trade_client;
    }

    void start_trade_client(trade::callback_functype callback) { get_trade_client_instance()->Start(callback); }

    void join_trade_client() { get_trade_client_instance()->Join(); }
}
