#pragma once
#include <string>
#include "Job.h"
#include "Location.h"

enum class Messagetype
{
    REQUEST_MEETUP,
    ACCEPT_MEETUP,
    DECLINE_MEETUP,
    CANCEL_MEETUP,
    CONVERSATION,
    GENERIC_INFO
};

struct ExtraInfo
{
    int timeTick;
    Location spot;
    bool Respond;
};

struct Telegram
{
    int Sender;
    int Receiver;
    Messagetype MsgType;
    double DispatchTime;
    std::string MessageContent;
    ExtraInfo ExtraInfo;
};
