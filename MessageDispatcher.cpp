#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"

void MessageDispatcher::DispatchMessage(double delay, int senderID, int receiverID, std::string content, Messagetype type, ExtraInfo extraInfo)
{
    BaseGameEntity* receiver = EntityManager::Instance()->GetEntityByID(receiverID);
    if (!receiver)
    {
        std::cerr << "Was not able to find Entity with ID " << receiverID << endl;
        return;
    }
    //create telegram with correct information
    Telegram telegram;
    telegram.Sender = senderID;
    telegram.Receiver = receiverID;
    telegram.ExtraInfo = extraInfo; 
    telegram.MessageContent = content;
    telegram.MsgType = type;
    telegram.DispatchTime = currentTick + delay;
    telegram.ExtraInfo.timeTick = telegram.DispatchTime; 


    if (delay <= 0.0)
    {
        Discharge(receiver, telegram);

    }
    else
    {
        PriorityQueue.push(telegram);
    }

}
void MessageDispatcher::UpdateTick(int i)
{
    currentTick = i;
}
void MessageDispatcher::DispatchMessageDelayed() // no delayed message implementation yet
{
    double currentTime = currentTick;
  
    while (!PriorityQueue.empty()) { 

        Telegram telegram = PriorityQueue.top(); 
        if (telegram.DispatchTime > currentTime) //if next message is not ready to be sent
        {
            break;
        }
        PriorityQueue.pop(); 
  
        BaseGameEntity* receiver = EntityManager::Instance()->GetEntityByID(telegram.Receiver); 
        Discharge(receiver, telegram); 
    }
   
}
MessageDispatcher* MessageDispatcher::Instance() 
{
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