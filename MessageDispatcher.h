#pragma once
#include <chrono>
#include "Telegram.h"
#include <queue>
#include <iostream> 
class BaseGameEntity;

class MessageDispatcher
{
private:
 
	std::priority_queue<Telegram, std::vector<Telegram>, CompareTelegram> PriorityQueue;
  void Discharge(BaseGameEntity* pReceiver,const Telegram& msg);

  MessageDispatcher(){}
  int currentTick;
public:
	static MessageDispatcher* Instance();

	void UpdateTick(int i);
	void DispatchMessage(double delay, int senderID, int receiverID, std::string content, Messagetype msg, ExtraInfo extrainfo);
  void DispatchMessageDelayed();

};
