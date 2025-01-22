#include "Actor.h"

Actor::Actor(int id, JobType newJob): BaseGameEntity(id)
{
	job = CreateJob(newJob);
	currentLocation= Location::HOME;
	hunger = 0.0f;
	thirst=0.0f;
	energy=100.0f;
	money=0;
	socialized= 75;
}
void Actor::ChangeState(State* state)
{
	currentState->Exit(this);
	currentState = state;
	currentState->Enter(this);
}
void Actor::Update()
{
	hunger += 1.0f / 15.0f;
	thirst += 1.0f / 10.0f;
	energy -= 1.0f / 20.0f; // happy with this rate while not working for now
	

	if (thirst >= 30.0f)
	{
		isThirsty = true;
	}
	else
	{
		isThirsty = false;
	}

	if (hunger >= 30.0f)
	{
		isHungry = true;
	}
	else
	{
		isHungry = false;
	}

	if (energy<= 30)
	{
		isTired = true;
	}
	else
	{
		isTired = false;
	}



	/*if (thirst >= 100)
	{
		std::cout<<"Actor "<<GetID()<<" has died from dehydration"<<std::endl;
		
	}
	if(hunger>=100)
	{
		std::cout<<"Actor "<<GetID()<<" has died from starvation"<<std::endl;
	}
	if(energy<=0)
	{
		std::cout<<"Actor "<<GetID()<<" has died from sleep deprivation"<<std::endl;
	}
	if(money>=160)
	{
		std::cout<<"Actor "<<GetID()<<" is feeling wealthy. He wants to stop working for now"<<std::endl;
	}*/
	


}
void Actor::SetJob(Job& newJob)
{
	job = newJob;
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

void Actor::DecreaseHunger(float amount)
{
	hunger -= amount;
}
void Actor::DecreaseThirst(float amount)
{
	thirst -= amount;
}
void Actor::IncreaseEnergy(float amount)
{
	energy += amount;
}
void Actor::DecreaseMoney(int amount)
{
	money -= amount;
}
void Actor::IncreaseSocialized(int amount)
{
	socialized += amount;
}
Location Actor::GetCurrentLocation()const
{
	return currentLocation;
}


