#include "BaseGameEntity.h"
#include <iostream>
BaseGameEntity::BaseGameEntity(int id)
{
	SetID(id);

}
int BaseGameEntity::nextEligibleID = 1;

void BaseGameEntity::SetID(int id)
{
	if (id >= nextEligibleID)
	{
		ID = id;
		std::cout << nextEligibleID<<std::endl;
		nextEligibleID= id+1;
	}
	else
	{
		std::cerr << "Error: ID " << id << " is not valid (must be >= " << nextEligibleID << ")\n";
		terminate();
	}
}

BaseGameEntity::~BaseGameEntity()
{

}

int BaseGameEntity::GetID()const
{
	return ID;
}