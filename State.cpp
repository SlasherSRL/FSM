#include "State.h"
#include "Actor.h"
#include <iostream>
using namespace std;
void State_Sleep::Enter(Actor* actor)
{
	actor->SetLocation(Location::HOME);
	cout << actor->GetName() << " goes home" << endl;

	cout << actor->GetName() << " goes to sleep" << endl;
}
void State_Sleep::Execute(Actor* actor)
{
	if (actor->GetEnergy() >= 95)
	{
		
		if(actor->GetHunger()>=65&&actor->GetMoney()>=150&&actor->GetFood()==0)
		{
			actor->DecreaseMoney(150); //eat at restaurant
			actor->SetLocation(Location::RESTAURANT);
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);

		}
		if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
		}
		else
		{
			if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Shopping);
			}
			else
			{
				
				actor->ChooseJob();
				
				if (actor->GetJob().type == JobType::PILOT)
				{
					actor->ChangeState(new State_PilotWork);
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
				}
			}
			
			
		}
	}
	else
	{
		cout << actor->GetName() << " is sleeping" << endl;
		actor->IncreaseEnergy(80.0f/480.0f);
		actor->IncreaseHunger(1.0f / 20.0f);
		actor->IncreaseThirst(1.0f / 30.0f);
		actor->DecreaseSocialized(1.0f/20.0f);
	}
	

}
void State_Sleep::Exit(Actor* actor)
{
	cout << actor->GetName() << " wakes up feeling good" << endl;
	
	cout << actor->GetName() << " decides to work as : " << actor->GetJob().JobName << endl;
	
}
bool State_Sleep::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}

void State_Eat::Enter(Actor* actor)
{
	if (LocationToString(actor->GetCurrentLocation()) == "Restaurant")
	{
		cout << actor->GetName() << " goes to the Restaurant" << endl; 
	}
	else
	{
		if (LocationToString(actor->GetCurrentLocation()) == "Home")
		{
			
		}
		else
		{
			actor->SetLocation(Location::HOME); 
			cout << actor->GetName() << " goes home" << endl;
		}
		

	}
	
	cout << actor->GetName() << " starts eating" << endl;

	
}
void State_Eat::Execute(Actor* actor)
{
	// faster to eat at a restaurant than going home
	if (LocationToString(actor->GetCurrentLocation()) == "Restaurant")
	{
		actor->DecreaseHunger(5.0f);
		actor->IncreaseSocialized(0.2f);
	}
	if (LocationToString(actor->GetCurrentLocation()) == "Home")
	{
		actor->DecreaseHunger(3.0f); 
		actor->DecreaseSocialized(1.0f / 8.0f);
	}
	actor->DecreaseThirst(1.0f);
	actor->DecreaseEnergy(0.05f);

	if (actor->GetHunger() <= 5.0f)
	{
		if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);

		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
		}
		else
		{
			if (actor->GetMoney() >= 2000 && actor->GetFood() <= 3)
			{
				actor->ChangeState(new State_Shopping);
			}
			else if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Walk);
			}
			else
			{
				Job oldJob = actor->GetJob();

				actor->ChooseJob();
				if (actor->GetJob().type != oldJob.type)
				{
					cout << actor->GetName() << " changes job to " << actor->GetJob().JobName << endl;
				}
				if (actor->GetJob().type == JobType::PILOT)
				{
					actor->ChangeState(new State_PilotWork);
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
				}
			}
		}
	}
	
}
void State_Eat::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops eating"<<endl;
}
bool State_Eat::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}

void State_PilotWork::Enter(Actor* actor) // to change. make seperate states for seperate jobs
{
	if (actor->GetCurrentLocation() != actor->GetJob().jobLocation)
	{
		actor->SetLocation(actor->GetJob().jobLocation);
		cout << actor->GetName() << " goes to the airport to work" << endl;
	}
	
	cout << actor->GetName() << " does work as a pilot"<<endl;
}
void State_PilotWork::Execute(Actor* actor)
{
	
	
	actor->IncreaseMoney(actor->GetJob().incomeRate);
	actor->DecreaseEnergy(actor->GetJob().energyRate);
	actor->IncreaseHunger(actor->GetJob().hungerRate);
	actor->IncreaseThirst(actor->GetJob().thirstRate);
	actor->DecreaseSocialized(1.0f / 16.0f);
	if(actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
	{
		actor->DecreaseMoney(150); //buys new food 
		actor->SetLocation(Location::RESTAURANT); 
		actor->ChangeState(new State_Eat); 
	}
	if (actor->GetHunger() >= 65 && actor->GetFood() > 0) 
	{
		actor->DecreaseFood(1); 
	
		actor->ChangeState(new State_Eat); 
	}
	if (actor->GetThirst() >= 50) 
	{
		actor->ChangeState(new State_Drink); 

	}
	if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200) 
	{
		actor->DecreaseMoney(200); 
		actor->ChangeState(new State_Party); 
	}
	if (actor->GetEnergy() <= 20)
	{
		actor->ChangeState(new State_Sleep);
	}
	else
	{

		actor->ChooseJob();
			
		if (actor->GetJob().type == JobType::OFFICE_WORKER)
		{
			actor->ChangeState(new State_OfficeWork);
		}
		
	}
	
}
void State_PilotWork::Exit(Actor* actor)
{
	
	cout << actor->GetName() << " stops working" << endl;
	if (actor->GetJob().type != JobType::PILOT)
	{
		cout << actor->GetName() << " changes job to " << actor->GetJob().JobName << endl;
	}
}
bool State_PilotWork::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}
void State_OfficeWork::Enter(Actor* actor) // to change. make seperate states for seperate jobs
{
	if (actor->GetCurrentLocation() != actor->GetJob().jobLocation)
	{
		actor->SetLocation(actor->GetJob().jobLocation);
		cout << actor->GetName() << " goes to the office to work" << endl;
	}
	
	cout << actor->GetName() << " Does work as an Office Worker" << endl;
}
void State_OfficeWork::Execute(Actor* actor)
{


	actor->IncreaseMoney(actor->GetJob().incomeRate);
	actor->DecreaseEnergy(actor->GetJob().energyRate);
	actor->IncreaseHunger(actor->GetJob().hungerRate);
	actor->IncreaseThirst(actor->GetJob().thirstRate);
	actor->DecreaseSocialized(1.0f / 16.0f);

	if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
	{
		actor->DecreaseMoney(150); //buys new food 
		actor->SetLocation(Location::RESTAURANT);
		actor->ChangeState(new State_Eat);
	}
	if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
	{
		actor->DecreaseFood(1);
		
		actor->ChangeState(new State_Eat);
	}
	if (actor->GetThirst() >= 50)
	{
		actor->ChangeState(new State_Drink);

	}
	if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
	{
		actor->DecreaseMoney(200);
		actor->ChangeState(new State_Party);
	}
	if (actor->GetEnergy() <= 20)
	{
		actor->ChangeState(new State_Sleep);
	}
	else
	{
		
		
		actor->ChooseJob();

		if (actor->GetJob().type == JobType::PILOT)
		{
			actor->ChangeState(new State_PilotWork);
		}
		

	}

}
void State_OfficeWork::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops working" << endl;
	if (actor->GetJob().type != JobType::OFFICE_WORKER)
	{
		cout << actor->GetName() << " changes job to " << actor->GetJob().JobName << endl;
	}
}
bool State_OfficeWork::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}
void State_Drink::Enter(Actor* actor)
{
	if (actor->GetCurrentLocation() != Location::HOME && actor->GetCurrentLocation() != actor->GetJob().jobLocation)
	{
		actor->SetLocation(Location::HOME);
		cout << actor->GetName() << " goes home" << endl;
	}
	cout << actor->GetName() << " gets something to drink" << endl;
}
void State_Drink::Execute(Actor* actor)
{
	actor->DecreaseEnergy(0.02f);
	actor->IncreaseHunger(0.05f);
	if (actor->GetThirst() >= 50)
	{
		actor->DecreaseThirst(30);
	}
	else
	{
		actor->DecreaseThirst(5);
	}

	actor->DecreaseSocialized(1.0f / 16.0f);

	if (actor->GetThirst() <= 10)
	{
		if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
		{
			actor->DecreaseMoney(150); //buys new food 
			actor->SetLocation(Location::RESTAURANT);
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
		}
		else
		{
			if (actor->GetMoney() >= 2000 && actor->GetFood() <= 3)
			{
				actor->ChangeState(new State_Shopping);
			}
			else if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Walk);
			}
			else
			{
				Job oldJob = actor->GetJob();

				actor->ChooseJob();
				if (actor->GetJob().type != oldJob.type)
				{
					cout << actor->GetName() << " changes job to " << actor->GetJob().JobName << endl;
				}
				if (actor->GetJob().type == JobType::PILOT)
				{
					actor->ChangeState(new State_PilotWork);
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
				}
			}
		}
	}
	
}
void State_Drink::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops drinking" << endl;
}
bool State_Drink::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}
void State_Walk::Enter(Actor* actor)
{
	actor->SetLocation(Location::OUTSIDE);
	cout << actor->GetName() << " goes outside" << endl;
	cout << actor->GetName() << " goes for a walk" << endl;
}
void State_Walk::Execute(Actor* actor)
{
	
	
	if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
	{
		actor->DecreaseMoney(150); //eat at restaurant
		actor->SetLocation(Location::RESTAURANT);
		actor->ChangeState(new State_Eat);
	}
	if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
	{
		actor->DecreaseFood(1);

		actor->ChangeState(new State_Eat);
	}
	if (actor->GetThirst() >= 50)
	{
		actor->ChangeState(new State_Drink);

	}
	if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
	{
		actor->DecreaseMoney(200);
		actor->ChangeState(new State_Party);
	}
	if (actor->GetEnergy() <= 20)
	{
		actor->ChangeState(new State_Sleep);
	}
	else
	{
		if (actor->GetMoney() >= 2000&& actor->GetFood() <= 3)
		{
			actor->ChangeState(new State_Shopping);
		}
		else if(actor->GetMoney()>=2000)
		{
			actor->DecreaseEnergy(0.15f);
			actor->IncreaseThirst(0.3f);
			actor->IncreaseHunger(0.1f);
			actor->DecreaseSocialized(0.02f);
		}
		else
		{

			actor->ChooseJob();

			if (actor->GetJob().type == JobType::PILOT)
			{
				actor->ChangeState(new State_PilotWork);
			}
			if (actor->GetJob().type == JobType::OFFICE_WORKER)
			{
				actor->ChangeState(new State_OfficeWork);
			}
		}


	}
}
void State_Walk::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops walking" << endl;
}
bool State_Walk::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}
void State_Party::Enter(Actor* actor)
{
	actor->SetLocation(Location::BAR);
	cout << actor->GetName() << " goes to party" << endl;
}
void State_Party::Execute(Actor* actor)
{
	actor->DecreaseEnergy(0.1f);
	actor->DecreaseThirst(0.2f);
	actor->IncreaseHunger(0.05f);
	actor->IncreaseSocialized(0.75f);
	actor->DecreaseMoney(5);
	if (actor->GetSocialized()>=75)
	{
		if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
		{
			actor->DecreaseMoney(150); //buys new food 
			actor->SetLocation(Location::RESTAURANT);
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);

		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
		}
		if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
		{

			//actor->DecreaseMoney(200);
			//actor->ChangeState(new State_Party);
		}
		else
		{
			if (actor->GetMoney() >= 2000&& actor->GetFood()<=3)
			{
				actor->ChangeState(new State_Shopping);
			}
			else if (actor->GetMoney()>=2000)
			{
				actor->ChangeState(new State_Walk);
			}
			else
			{
				Job oldJob = actor->GetJob();

				actor->ChooseJob();
				if (actor->GetJob().type != oldJob.type)
				{
					cout << actor->GetName() << " changes job to " << actor->GetJob().JobName << endl;
				}
				if (actor->GetJob().type == JobType::PILOT)
				{
					actor->ChangeState(new State_PilotWork);
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
				}
			}
		}
	}
}
void State_Party::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops partying" << endl;
}
bool State_Party::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}
void State_Shopping::Enter(Actor* actor)
{
	actor->SetLocation(Location::WALMART);
	cout << actor->GetName() << " goes to the store to shop" << endl;
}
void State_Shopping::Execute(Actor* actor)
{
	actor->DecreaseMoney(50);// each item is 50
	actor->IncreaseFood(1);
	actor->DecreaseMoney(100);// 100 per gift card
	actor->IncreaseGiftCards(1);

	actor->DecreaseEnergy(0.05f);
	actor->IncreaseThirst(0.2f);
	actor->IncreaseHunger(0.05f);
	


	if (actor->GetMoney()<=400||actor->GetFood()>8) // he doesnt have much money left or if he has bought enough
	{
		if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
		{
			actor->DecreaseMoney(150); //buys new food 
			actor->SetLocation(Location::RESTAURANT);
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);

		}
		if (actor->GetSocialized() < 40 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
		}
		else
		{
			
			if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Walk);
			}
			else
			{
				Job oldJob = actor->GetJob();

				actor->ChooseJob();
				if (actor->GetJob().type != oldJob.type)
				{
					cout << actor->GetName() << " changes job to " << actor->GetJob().JobName << endl;
				}
				if (actor->GetJob().type == JobType::PILOT)
				{
					actor->ChangeState(new State_PilotWork);
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
				}
			}
		}
	}
}
void State_Shopping::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops shopping" << endl;
}
bool State_Shopping::OnMessage(Actor* actor, const Telegram& msg)
{
	cout << "Message Received" << endl;
	return true;
}