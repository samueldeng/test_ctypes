// OSX: g++ trade_client_api.cpp -o libtrade_client_api.dylib --std c++17 -shared -fPIC -L./ -ltrade_client
// Linux: g++ trade_client_api.cpp -o libtrade_client_api.so --std c++17 -shared -fPIC -L./ -ltrade_client -Wl,-rpath ./
#include <stdint.h>

struct Message
{
    uint32_t type;
    uint32_t length;
    char *data;
    uint32_t checksum;
};

using callback_functype = void (*)(Message messages);

extern "C" void start_trade_client(callback_functype callback);

extern "C" void stop_trade_client();

extern "C" void join_trade_client();

extern "C" void send_message(Message message);
