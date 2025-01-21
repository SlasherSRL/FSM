#include "Actor.h"

Actor::Actor(int id, JobType job=JobType::UNEMPLOYED): BaseGameEntity(id)
{
	job = CreateJob(job);
	hunger = 100.0f;
	thirst=100.0f;
	energy=100.0f;
	money=0;
	happniess= 75;
}

void Actor::Update()
{
	hunger -=job.hungerRate;
	thirst -=job.thirstRate;
	energy -=job.energyRate;

	money+= job.incomeRate;

	hunger = std::max(0, hunger); //make sure to not have values become negatives
    	thirst = std::max(0, thirst);
   	energy = std::max(0, energy);

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

