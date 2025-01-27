#include "MessageDispatcher.h"
#include "Actor.h"

void MessageDispatcher::DispatchMessage(double delay, int senderID, int receiverID, Messagetype type, void* ExtraInfo)
{
	
}
MessageDispatcher* MessageDispatcher::Instance() {
    static MessageDispatcher instance;
    return &instance;
}

void MessageDispatcher::Discharge(BaseGameEntity* pReceiver, const Telegram& msg)
{
    if (pReceiver)
    {
        pReceiver->HandleMessage(msg);
    }
}