#include <iostream>
#include <chrono>
#include "Actor.h"
#include "EntityManager.h"
using namespace std;
int main()
{
	auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = lastTime;
	float TPS = 5000.0f;
	const float timePerTick = 1.0f/TPS;
	float tick = 0.0;
	int tickCounter = 0;
	
	Actor steve(1,"Steve");
	EntityManager::Instance()->RegisterActor(&steve);
	Actor Dave(2,"Dave");
	EntityManager::Instance()->RegisterActor(&Dave);
	Dave.DecreaseEnergy(10);// he had a bad sleep

	Actor Meggan(3, "Meggan");
	EntityManager::Instance()->RegisterActor(&Meggan);
	Meggan.IncreaseFood(4);// meggan already has some food

	Actor Alice(4, "Alice");
	EntityManager::Instance()->RegisterActor(&Alice);
	Alice.DecreaseMoney(1000);// alice is in debt

	
	//cout << steve.GetID()<<endl;
	bool looping = true;
	while (looping)
	{
		currentTime = std::chrono::high_resolution_clock::now(); 
		tick += std::chrono::duration<float>(currentTime-lastTime).count(); 
		lastTime = currentTime; 
		if (tick >= timePerTick) // activates per tick
		{
			//time based actions here
			float deltaTime = tick;
			tick -= timePerTick;
			if (!EntityManager::Instance()->EmptyList())
			{
				EntityManager::Instance()->SetTickCounter(tickCounter); 
				EntityManager::Instance()->ConvertTicksToTime(tickCounter);
				EntityManager::Instance()->UpdateAll();
				cout << endl;
				
				tickCounter++;

			}
			else
			{
				looping = false;
			}
			

			
		}

		
		

	}
	EntityManager::Instance()->PrintDeadEntities();
	return 0;
}
