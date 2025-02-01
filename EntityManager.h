#pragma once
#include <vector>
#include <tuple>
#include "Actor.h"
class EntityManager
{
private:
	//vectors for holding information related to Entities, alive or dead
	std::vector < std::tuple<int, std::string,BaseGameEntity*>> Entities; //Alive
	std::vector < std::tuple<std::string,int>> DeadEntities;//dead, this simply holds string(name) and int(tick they died on)
	EntityManager(); 
	int tickCounter;

public:

	static EntityManager* Instance();
	bool EmptyList();

	std::vector<int> AtLocation(Location loc);
	std::vector<int> GetOtherIDs(int id);
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

