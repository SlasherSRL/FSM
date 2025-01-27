#pragma once
#include "Telegram.h"
using namespace std;
class Actor;


class State
{
public:
	virtual void Enter(Actor*) = 0;
	virtual void Execute(Actor*) = 0;
	virtual void Exit(Actor*) = 0;
	virtual bool OnMessage(Actor*, const Telegram& msg) = 0;
};




class State_Sleep :public State
{

public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_Eat :public State
{

public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_PilotWork :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};
class State_OfficeWork :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_Drink :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_Walk :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_Party :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_Socialize :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

class State_Shopping :public State
{
public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
	virtual bool OnMessage(Actor* actor, const Telegram& msg);
};

