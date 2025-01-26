#pragma once
enum class Messagetype
{
    REQUEST_MEETUP,
    ACCEPT_MEETUP,
    DECLINE_MEETUP,
    CANCEL_MEETUP,
    GENERIC_INFO
};

struct Telegram
{
    int Sender;
    int Receiver;
    int Msg;
    double DispatchTime;
    void* ExtraInfo;
};
