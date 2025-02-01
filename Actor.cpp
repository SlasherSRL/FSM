#include "Actor.h"
#include <iomanip>
#include "EntityManager.h"
#include "MessageDispatcher.h"

Actor::Actor(int id, std::string myName): BaseGameEntity(id)
{
	
	stateMachine = new FSM<Actor>(this);
	name = myName;
	food = 0;
	sentMessage = false;
	currentLocation= Location::HOME;
	hunger = 0.0f;
	thirst=0.0f;
	energy=100.0f;
	money=0;
	socialized= 75;
	isDead = false;
	ChangeState(new State_Sleep());
}
void Actor::ChangeState(State* state)
{
	stateMachine->ChangeState(state);
}
State* Actor::GetPreviousState()
{
	return stateMachine->GetPreviousState();
}
void Actor::Update()
{
	
	//energy -= 1.0f / 20.0f; // happy with this rate while not working for now
	

	

	if (thirst>=100)
	{
		isDead = true;
		EntityManager::Instance()->RemoveEntity(GetID()); 
		cout << GetName() << " died from dehydration"<<endl;
	}
	if (hunger >= 100)
	{
		isDead = true;
		EntityManager::Instance()->RemoveEntity(GetID());
		cout << GetName() << " died from starvation"<<endl;
	}
	if (energy <= 0)
	{
		isDead = true;
		EntityManager::Instance()->RemoveEntity(GetID());
		cout << GetName() << " died from exhaustion"<<endl;
	}
	if (socialized <= 0)
	{
		isDead = true;
		EntityManager::Instance()->RemoveEntity(GetID());
		cout << GetName() << " died from depression"<<endl;
	}
	if (!isDead)
	{
		stateMachine->Update();
	}
	
	if (EntityManager::Instance()->GetTick() % 20 == 0)
	{
		PrintStatus();
	}


}
void Actor::RequestMeetup() //default message for meeting up at the park
{
	SentMessage(true);
	std::vector<int> friends = EntityManager::Instance()->GetOtherIDs(GetID());
	if (!friends.empty())
	{
		for (auto id : friends)
		{
			std::cout << GetName() << " sends message to " << EntityManager::Instance()->GetNameByID(id) << endl;
			std::string message = GetName() + ": Hello " + EntityManager::Instance()->GetNameByID(id) + " would you like to go to the " + LocationToString(Location::PARK);
			ExtraInfo info;
			info.Respond = true;
			info.spot = Location::PARK;
			MessageDispatcher::Instance()->DispatchMessage(0.0, GetID(), id, message, Messagetype::REQUEST_MEETUP, info);
		}
	}
}
void Actor::Greet()
{
	std::vector<int> actorsNearbyID = EntityManager::Instance()->AtLocation(GetCurrentLocation());
	if (!actorsNearbyID.empty())
	{
		for (auto peopleID : actorsNearbyID)
		{
			if (peopleID !=GetID())
			{
				std::string message = GetName() + ": Hello " + EntityManager::Instance()->GetNameByID(peopleID);
				ExtraInfo info;
				info.Respond = true;

				MessageDispatcher::Instance()->DispatchMessage(0.0, GetID(), peopleID, message, Messagetype::CONVERSATION, info);
			}
		}
	}
}
bool Actor::HandleMessage(const Telegram& msg)
{
	return stateMachine->ForwardMessage(msg);
}
bool Actor::IsDead()const
{
	return isDead;
}
void Actor::ChooseJob()
{
	if (energy >= 60)
	{
		job = CreateJob(JobType::PILOT);

	}
	else
	{
		job = CreateJob(JobType::OFFICE_WORKER);
	}
}
Job Actor::GetJob()const
{
	return job;
}
std::string Actor::GetName()const
{
	return name;
}
float Actor::GetHunger()const
{
	return hunger;
}
float Actor::GetEnergy()const
{
	return energy;
}
float Actor::GetThirst()const
{
	return thirst;
}
int Actor::GetMoney()const
{
	return money;
}
float Actor::GetSocialized()const
{
	return socialized;
}
int Actor::GetFood()const
{
	return food;
}
int Actor::GetGiftCards()const
{
	return giftCards;
}

void Actor::PrintStatus()const
{
	std::string locationName = LocationToString(currentLocation);

    	std::cout << "+------------------------------+\n";
    	std::cout << "|         Actor Status         |\n";
    	std::cout << "+------------------------------+\n";
    	std::cout << "| Name       : " << std::setw(15) << name << " |\n";
    	std::cout << "| Location   : " << std::setw(15) << locationName << " |\n";
    	std::cout << "| Thirst     : " << std::setw(9) << thirst << " / 100 |\n";
    	std::cout << "| Hunger     : " << std::setw(9) << hunger << " / 100 |\n";
    	std::cout << "| Energy     : " << std::setw(9) << energy << " / 100 |\n";
    	std::cout << "| Socialized : " << std::setw(9) << socialized << " / 100 |\n";
    	std::cout << "| Money      : $" << std::setw(14) << money << " |\n";
		std::cout << "| Food     : " << std::setw(17) << food << " |\n";
		std::cout << "| Giftcards      : " << std::setw(11) << giftCards << " |\n";
    	std::cout << "+------------------------------+\n";
}

void Actor::DecreaseFood(int amount)
{
	food -= amount;
	if (food <= 0)
	{
		food = 0;
	}
}
void Actor::IncreaseFood(int amount)
{
	food += amount;
}
void Actor::DecreaseGiftCards(int amount)
{
	
	giftCards -= amount;
	if (giftCards <= 0)
	{
		giftCards = 0;
	}
}
void Actor::IncreaseGiftCards(int amount)
{
	giftCards += amount;
}
void Actor::DecreaseHunger(float amount)
{
	hunger -= amount;
	if (hunger <= 0)
	{
		hunger = 0;
	}
}
void Actor::IncreaseHunger(float amount)
{
	hunger += amount;
}
void Actor::DecreaseThirst(float amount)
{
	thirst -= amount;
	if (thirst <= 0)
	{
		thirst = 0;
	}
}
void Actor::IncreaseThirst(float amount)
{
	thirst += amount;
}
void Actor::IncreaseEnergy(float amount)
{
	energy += amount;
}
void Actor::DecreaseEnergy(float amount)
{
	energy -= amount;
}
void Actor::DecreaseMoney(int amount)
{
	money -= amount;
	
}
void Actor::IncreaseMoney(int amount)
{
	money += amount;
}
void Actor::IncreaseSocialized(float amount)
{
	socialized += amount;
}
void Actor::DecreaseSocialized(float amount)
{
	socialized -= amount;
}
void Actor::SetLocation(Location location)
{
	currentLocation = location;
}
Location Actor::GetCurrentLocation()const
{
	return currentLocation;
}
bool Actor::HasSentMessage()
{
	return sentMessage;
}
void Actor::SentMessage(bool status)
{
	sentMessage = status;
}
