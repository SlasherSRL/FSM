#pragma once
#include "State.h"

template <typename ActorType>
class FSM
{
private: 
	ActorType* owner;
	State* currentState;
	State* previousState;
public:
	FSM(ActorType* owner) : owner(owner), currentState(nullptr), previousState(nullptr){}

	void ChangeState(State* newState)
	{
		if (currentState)
		{
			currentState->Exit(owner);
		}
		delete previousState; //if previous state is not needed. delete it before assigning the state we are moving away from
		//as the new previouState
		previousState = currentState;
		currentState = newState;
		if (currentState)
		{
			currentState->Enter(owner);
		}
	}
	void Update()
	{
		if (currentState)
		{
			currentState->Execute(owner);
		}
	}
	//bool IsInState()
};