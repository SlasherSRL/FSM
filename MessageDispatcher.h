#pragma once
#include "Telegram.h"

class MessageDispatcher
{
private:
  std::set<Telegram> Priority();

  void Discharge(Entity* pReceiver,const Telegram& msg);
  MessageDispatcher(){}

public:
  static MessageDispatcher* Instance();

  void DispatchMessage(double delay,int senderID,int receiverID,int msg,void* Extrainfo);
  void DispatchMessageDelayed();

};
