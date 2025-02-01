#include "EntityManager.h"
#include <iomanip>
EntityManager* EntityManager::Instance() 
{
	static EntityManager instance;
	return &instance;
}
EntityManager::EntityManager()
{
	tickCounter = 0;
}
std::vector<int> EntityManager::AtLocation(Location loc)
{
	std::vector<int> ids;

	for (auto& entity : Entities) 
	{
		
		BaseGameEntity* ent = std::get<2>(entity);
		Actor* actor =(Actor*)(ent); // Entities are stored as BaseGameEntities. Cast to actor to get

		if (actor && actor->GetCurrentLocation() == loc) 
		{
			ids.push_back(actor->GetID());
		}
	}

	return ids;
}
//adds an entity to the alive entity vector (Entities)
void EntityManager::RegisterEntity(BaseGameEntity* entity)
{
	Entities.emplace_back(entity->GetID(), entity->GetName(), entity);
}
//removes entity from list of living entities, adds it to the dead enemies
void EntityManager::RemoveEntity(int id)
{
	auto it = std::find_if(Entities.begin(), Entities.end(), //goes through the vector to see if it contains the value we want.
		[id](const auto& entity) { return std::get<0>(entity) == id; });

	if (it != Entities.end()) { // if it didnt reach the end( meaning we found what we wanted), operate on that
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
	
	
	return (it != Entities.end()) ? std::get<2>(*it) : nullptr; // if it could not find the entity, return nullptr
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
	for (auto& entity : Entities) 
	{
		if (std::get<2>(entity)) 
		{
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
// The game runs on a tick timer. here we convert it into actual time.
void EntityManager::ConvertTicksToTime(int tickCounter) 
{ 
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
std::vector<int> EntityManager::GetOtherIDs(int id) // get every ID that isnt your own
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
