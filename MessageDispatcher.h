#pragma once
#include <chrono>
#include "Telegram.h"
class BaseGameEntity;

class MessageDispatcher
{
private:
 

  void Discharge(BaseGameEntity* pReceiver,const Telegram& msg);

  MessageDispatcher(){}

public:
	static MessageDispatcher* Instance();

  void DispatchMessage(double delay,int senderID,int receiverID,Messagetype msg,void* Extrainfo);
  void DispatchMessageDelayed();

};
