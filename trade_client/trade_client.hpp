#include <cstdint>
#include <thread>

namespace trade
{

struct Message
{
    std::uint32_t type;
    std::uint32_t length;
    char *data;
    std::uint32_t checksum;
};

using callback_functype = void (*)(Message messages);

class TradeClient
{
 public:
    TradeClient();

    void Start(callback_functype callback);

    void Join();

    void Stop();

    void Run();

 private:
    callback_functype callback_;
    std::thread thread_;

    Message messages[1024];
};

};