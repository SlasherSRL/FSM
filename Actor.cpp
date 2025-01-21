#include "Actor.h"

Actor::Actor(int id, JobType job=UNEMPLOYED): BaseGameEntity(id)
{
	job = CreateJob(job);
}

void Actor::Update()
{
	hunger += 1;

}
