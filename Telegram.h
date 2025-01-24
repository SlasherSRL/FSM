#pragma once

struct Telegram
{
    int Sender;
    int Receiver;
    int Msg;
    double DispatchTime;
    void* ExtraInfo;
};
