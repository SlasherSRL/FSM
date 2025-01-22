#include "Actor.h"

Actor::Actor(int id, std::string myName): BaseGameEntity(id)
{
	
	stateMachine = new FSM<Actor>(this);
	name = myName;

	currentLocation= Location::HOME;
	hunger = 0.0f;
	thirst=0.0f;
	energy=100.0f;
	money=0;
	socialized= 75;
	
	ChangeState(new State_Sleep());
}
void Actor::ChangeState(State* state)
{
	stateMachine->ChangeState(state);
}
void Actor::Update()
{
	
	//energy -= 1.0f / 20.0f; // happy with this rate while not working for now
	

	


	stateMachine->Update();


}
void Actor::ChooseJob()
{
	if (energy >= 85)
	{
		job = CreateJob(JobType::PILOT);

	}
	else
	{
		job = CreateJob(JobType::OFFICE_WORKER);
	}
}
Job Actor::GetJob()const
{
	return job;
}
std::string Actor::GetName()const
{
	return name;
}
float Actor::GetHunger()const
{
	return hunger;
}
float Actor::GetEnergy()const
{
	return energy;
}
float Actor::GetThirst()const
{
	return thirst;
}
int Actor::GetMoney()const
{
	return money;
}
float Actor::GetSocialized()const
{
	return socialized;
}

void Actor::DecreaseHunger(float amount)
{
	hunger -= amount;
}
void Actor::IncreaseHunger(float amount)
{
	hunger += amount;
}
void Actor::DecreaseThirst(float amount)
{
	thirst -= amount;
}
void Actor::IncreaseThirst(float amount)
{
	thirst += amount;
}
void Actor::IncreaseEnergy(float amount)
{
	energy += amount;
}
void Actor::DecreaseEnergy(float amount)
{
	energy -= amount;
}
void Actor::DecreaseMoney(int amount)
{
	money -= amount;
}
void Actor::IncreaseMoney(int amount)
{
	money += amount;
}
void Actor::IncreaseSocialized(float amount)
{
	socialized += amount;
}
void Actor::DecreaseSocialized(float amount)
{
	socialized -= amount;
}
void Actor::SetLocation(Location location)
{
	currentLocation = location;
}
Location Actor::GetCurrentLocation()const
{
	return currentLocation;
}


