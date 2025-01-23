#include <iostream>
#include <chrono>
#include "Actor.h"

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
	//Actor Dave(2);
	
	
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
			if (!steve.IsDead())
			{
				steve.Update();
				tickCounter++;
				std::cout << "Tick" << tickCounter << "| Hunger: " << steve.GetHunger()
					<< "| Thirst: " << steve.GetThirst()
					<< "| Energy: " << steve.GetEnergy() << "| Socialized:" << steve.GetSocialized() << "| Money:" << steve.GetMoney() << '\n';
				std::cout << steve.GetName() << " is at " << LocationToString(steve.GetCurrentLocation()) << endl;

			}
			else
			{
				looping = false;
			}
			

			
		}

		
		

	}
	return 0;
}
