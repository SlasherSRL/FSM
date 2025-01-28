#pragma once
#include <vector>
#include <tuple>
#include "Actor.h"
class EntityManager
{
private:
	std::vector < std::tuple<int, std::string,BaseGameEntity*>> Entities;
	std::vector < std::tuple<std::string,int>> DeadEntities;
	EntityManager(){}
	int tickCounter;

public:

	static EntityManager* Instance();
	bool EmptyList();

	std::vector<int> AtLocation(Location loc);
	void RegisterEntity(BaseGameEntity* entity);
	void RemoveEntity(int id);

	void UpdateAll();
	void SetTickCounter(int tick);
	BaseGameEntity* GetEntityByID(int id);

	int GetIDByName(std::string name);	
	std::string GetNameByID(int id);

	void PrintDeadEntities();
	void ConvertTicksToTime(int tickCounter);
	int GetTick();

};

