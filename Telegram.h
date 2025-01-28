#pragma once
#include <string>
enum class Messagetype
{
    REQUEST_MEETUP,
    ACCEPT_MEETUP,
    DECLINE_MEETUP,
    CANCEL_MEETUP,
    CONVERSATION,
    GENERIC_INFO
};

struct Telegram
{
    int Sender;
    int Receiver;
    Messagetype MsgType;
    double DispatchTime;
    std::string MessageContent;
    void* ExtraInfo;
};
