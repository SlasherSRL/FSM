#include "EntityManager.h"
#include <iomanip>
EntityManager* EntityManager::Instance() 
{
	static EntityManager instance;
	return &instance;
}

void EntityManager::RegisterActor(Actor* actor)
{
	Entities.emplace_back(actor->GetID(), actor->GetName(), actor);
}

void EntityManager::RemoveActor(int id)
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
Actor* EntityManager::GetActorByID(int id)
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
