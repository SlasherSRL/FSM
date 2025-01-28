#pragma once
#include <chrono>
#include "Telegram.h"
#include <queue>
#include <iostream> 
class BaseGameEntity;

class MessageDispatcher
{
private:
 
	//std::priority_queue<Telegram> PriorityQueue;
  void Discharge(BaseGameEntity* pReceiver,const Telegram& msg);

  MessageDispatcher(){}

public:
	static MessageDispatcher* Instance();

	void DispatchMessage(double delay, int senderID, int receiverID, std::string content, Messagetype msg, ExtraInfo extrainfo);
  void DispatchMessageDelayed();

};
