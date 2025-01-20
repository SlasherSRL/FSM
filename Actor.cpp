#include "Actor.h"

Actor::Actor(int id): BaseGameEntity(id)
{
	
}

void Actor::Update()
{
	hunger += 1;

}