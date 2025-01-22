#include "State.h"
#include "Actor.h"
#include <iostream>
using namespace std;
void State_Sleep::Enter(Actor* actor)
{
	cout << actor->GetName() << " goes to sleep" << endl;
}
void State_Sleep::Execute(Actor* actor)
{
	if (actor->GetEnergy() >= 95)
	{
		
		if(actor->GetHunger()>=65&&actor->GetMoney()>=15)
		{
			actor->ChangeState(new State_Eat);
		}
		else
		{
			
			actor->ChangeState(new State_Work);
		}
	}
	else
	{
		cout << actor->GetName() << " is sleeping" << endl;
		actor->IncreaseEnergy((100 - actor->GetEnergy())/480.0f);
		actor->IncreaseHunger(1.0f / 20.0f);
		actor->IncreaseThirst(1.0f / 30.0f);
		
	}
	

}
void State_Sleep::Exit(Actor* actor)
{
	cout << actor->GetName() << " wakes up feeling good" << endl;

}

void State_Eat::Enter(Actor* actor)
{

}
void State_Eat::Execute(Actor* actor)
{

}
void State_Eat::Exit(Actor* actor)
{

}

void State_Work::Enter(Actor* actor) // to change. make seperate states for seperate jobs
{
	actor->ChooseJob();
	actor->SetLocation(actor->GetJob().jobLocation);
	cout << actor->GetName() << " Goes to work as a " << actor->GetJob().JobName<<endl;
}
void State_Work::Execute(Actor* actor)
{
	actor->ChooseJob();
	if (actor->GetJob().type == JobType::PILOT)
	{
		actor->IncreaseMoney(actor->GetJob().incomeRate);
		actor->DecreaseEnergy(actor->GetJob().energyRate);
		actor->IncreaseHunger(actor->GetJob().hungerRate);
		actor->IncreaseThirst(actor->GetJob().thirstRate);
		actor->DecreaseSocialized(1.0f / 10.0f);
		
	}
	if (actor->GetJob().type == JobType::OFFICE_WORKER)
	{

	}
}
void State_Work::Exit(Actor* actor)
{

}