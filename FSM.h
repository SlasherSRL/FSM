#pragma once
#include "Actor.h"
using namespace std;

class State
{
public:
	virtual void Enter(Actor*) = 0;
	virtual void Execute(Actor*) = 0;
	virtual void Exit(Actor*) = 0;
};

class State_Sleep :public State
{

public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
};

class State_Eat :public State
{

public:
	virtual void Enter(Actor* actor);
	virtual void Execute(Actor* actor);
	virtual void Exit(Actor* actor);
};
