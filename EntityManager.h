#pragma once
#include <vector>
#include <tuple>
#include "Actor.h"
class EntityManager
{
private:
	std::vector < std::tuple<int, std::string,Actor*>> Entities;
	std::vector < std::tuple<std::string,int>> DeadEntities;
	EntityManager(){}
	int tickCounter;

public:

	static EntityManager* Instance();
	bool EmptyList();

	void RegisterActor(Actor* actor);
	void RemoveActor(int id);

	void UpdateAll();
	void SetTickCounter(int tick);
	Actor* GetActorByID(int id);

	int GetIDByName(std::string name);	
	std::string GetNameByID(int id);

	void PrintDeadEntities();
	void ConvertTicksToTime(int tickCounter);

};

