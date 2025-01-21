#include "Actor.h"

Actor::Actor(int id, JobType job=UNEMPLOYED): BaseGameEntity(id)
{
	job = CreateJob(job);
	hunger = 100;
	thirst=100;
	energy=100;
	money=0;
}

void Actor::Update()
{
	hunger -=job.hungerRate;
	thirst -=job.thirstRate;
	energy -=job.energyRate;

	money+= job.incomeRate;

}
