#pragma once

#include <cstdint>
#include <thread>
#include <vector>

namespace trade
{
namespace trade_client_status
{
constexpr std::uint64_t inited{0};
constexpr std::uint64_t running{1};
constexpr std::uint64_t stopped{2};
};

struct Message
{
    std::uint32_t type;
    std::uint32_t length;
    char *data;
    std::uint32_t checksum;
};

#pragma pack(push,1)
struct PacketA  //24
{
    char field_1;  // 1
    std::int32_t field_2;  //4
    std::uint32_t field_3;  //4
    char field_4[5];  // 5
    std::uint64_t field_5;  // 8
    std::uint16_t field_6;  // 2
};
#pragma pack(pop)

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
    std::atomic_uint64_t status_{trade_client_status::inited};

    Message messages_list_[1024];
    PacketA packet_a_list_[1024];
    PacketB packet_b_list_[1024];

};

};