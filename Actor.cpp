#include "Actor.h"

Actor::Actor(int id, JobType job=UNEMPLOYED): BaseGameEntity(id)
{
	job = CreateJob(job);
}

void Actor::Update()
{
	hunger -=job.hungerRate;
	thirst -=job.thirstRate;
	energy -=job.energyRate;

	money+= job.incomeRate;

}
