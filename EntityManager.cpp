#include "EntityManager.h"
#include <iomanip>
EntityManager* EntityManager::Instance() 
{
	static EntityManager instance;
	return &instance;
}
std::vector<int> EntityManager::AtLocation(Location loc)
{
	std::vector<int> ids;

	for (auto& entity : Entities) {
		
		BaseGameEntity* ent = std::get<2>(entity);
		Actor* actor =(Actor*)(ent); // Entities are stored as BaseGameEntities. Cast to actor to get

		if (actor && actor->GetCurrentLocation() == loc) {
			ids.push_back(actor->GetID());
		}
	}

	return ids;
}
void EntityManager::RegisterEntity(BaseGameEntity* entity)
{
	Entities.emplace_back(entity->GetID(), entity->GetName(), entity);
}

void EntityManager::RemoveEntity(int id)
{
	auto it = std::find_if(Entities.begin(), Entities.end(),
		[id](const auto& entity) { return std::get<0>(entity) == id; });

	if (it != Entities.end()) {
		DeadEntities.emplace_back(GetNameByID(id), tickCounter);
		Entities.erase(it);
		
	}

}
void EntityManager::SetTickCounter(int tick)
{
	tickCounter = tick;
}
BaseGameEntity* EntityManager::GetEntityByID(int id)
{
	auto it = std::find_if(Entities.begin(), Entities.end(),
		[id](const auto& entity) { return std::get<0>(entity) == id; });
	
	
	return (it != Entities.end()) ? std::get<2>(*it) : nullptr;
}

int EntityManager::GetIDByName(std::string name)
{
	auto it = std::find_if(Entities.begin(), Entities.end(),
		[&name](const auto& entity) { return std::get<1>(entity) == name; });

	return (it != Entities.end()) ? std::get<0>(*it) : -1;
}

std::string EntityManager::GetNameByID(int id)
{
	auto it = std::find_if(Entities.begin(), Entities.end(),
		[id](const auto& entity) { return std::get<0>(entity) == id; });

	return (it != Entities.end()) ? std::get<1>(*it) : "Unknown";
}

bool EntityManager::EmptyList()
{
	if (Entities.size() == 0)
	{
		return true;
	}
	return false;
}

void EntityManager::UpdateAll()
{
	for (auto& entity : Entities) {
		if (std::get<2>(entity)) {
			std::get<2>(entity)->Update();
		}
	}
}
void EntityManager::PrintDeadEntities()
{
	for (const auto& deadEntity : DeadEntities) 
	{ 
		const auto& name = std::get<0>(deadEntity);
		int deathTick = std::get<1>(deadEntity);

		std::cout << "Entity: " << name << ", Died at Tick: " << deathTick << '\n';
	}
}

void EntityManager::ConvertTicksToTime(int tickCounter) {
	int hours = (tickCounter / 60)+6;
	int minutes = tickCounter % 60;
	int days = (hours / 24)+1;
	hours = hours % 24;


	std::cout << "Day " << days << " Time : [" <<std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0')<< minutes << "]" << "\n";

	std::cout << std::resetiosflags(std::ios::adjustfield)      // Reset alignment
		<< std::setfill(' ');
}

int EntityManager::GetTick()
{
	return tickCounter;
}
std::vector<int> EntityManager::GetOtherIDs(int id)
{
	std::vector<int> ids;
	for (auto& entity : Entities)
	{
		if (std::get<0>(entity) != id)
		{
			ids.push_back(std::get<0>(entity));
		}
		
	}

	return ids;
}
