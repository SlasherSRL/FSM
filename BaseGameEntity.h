#pragma once
#include "Telegram.h"
class BaseGameEntity
{

private:
	int ID;

	static int nextEligibleID;

public:

	BaseGameEntity(int id);

	void SetID(int id);

	virtual ~BaseGameEntity();

	virtual void Update() = 0;
	virtual bool HandleMessage(const Telegram& msg)=0;
	int GetID()const;

};

