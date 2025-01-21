#include <iostream>
#include <chrono>
#include "Actor.h"

using namespace std;
int main()
{
	auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = lastTime;
	float TPS = 60.0f;
	const float timePerTick = 1.0f/TPS;
	float tick = 0.0;

	cout << timePerTick<<endl;
	Actor steve(1);
	//Actor Dave(2);
	
	
	//cout << steve.GetID()<<endl;
	
	while (true)
	{
		currentTime = std::chrono::high_resolution_clock::now(); 
		tick += std::chrono::duration<float>(currentTime-lastTime).count(); 
		lastTime = currentTime; 
		if (tick >= timePerTick) // activates per tick
		{
			//time based actions here
			float deltaTime = tick;
			tick -= timePerTick;
			steve.Update();
			
			
		}

		
		

	}
	return 0;
}
