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
    Telegram telegram;
    telegram.Sender = senderID;
    telegram.Receiver = receiverID;
    telegram.ExtraInfo = extraInfo; 
    telegram.MessageContent = content;
    telegram.MsgType = type;
    telegram.DispatchTime = std::clock() + delay;

    if (delay <= 0.0)
    {
        Discharge(receiver, telegram);

    }
    else
    {
      
    }

}
void MessageDispatcher::DispatchMessageDelayed()
{
  //  double currentTime = std::clock();
  //
  //  while (!PriorityQueue.empty() && PriorityQueue.top().DispatchTime <= currentTime) {
  //      Telegram telegram = PriorityQueue.top();
  //      PriorityQueue.pop();
  //
  //      BaseGameEntity* receiver = EntityManager::Instance()->GetEntityByID(telegram.Receiver);
  //      Discharge(receiver, telegram);
  //  }
  // 
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