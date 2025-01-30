#include "State.h"
#include "Actor.h"
#include <iostream>
#include "EntityManager.h"
#include "MessageDispatcher.h"

using namespace std;
void State_Sleep::Enter(Actor* actor)
{
	actor->SetLocation(Location::HOME);
	cout << actor->GetName() << " goes home" << endl;

	cout << actor->GetName() << " goes to sleep" << endl;
	actor->SentMessage(false); 
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
			return;
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
			return;
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);
			return;

		}
		if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
		{
			actor->RequestMeetup();
			return;
		}
		if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
			return;
		}
		else
		{
			if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Shopping);
				return;
			}
			else
			{
				
				actor->ChooseJob();
				
				if (actor->GetJob().type == JobType::PILOT)
				{
					actor->ChangeState(new State_PilotWork);
					return;
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
					return;
				}
			}
			
			
		}
	}
	else
	{
		//cout << actor->GetName() << " is sleeping" << endl;
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
	actor->SentMessage(false); 
	
}
bool State_Sleep::OnMessage(Actor* actor, const Telegram& msg)
{

	cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
	if (actor->HasSentMessage())
	{
		cout << msg.MessageContent << endl;
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}
	}
	else
	{
		cout << actor->GetName() << " is sleeping" << endl;
	}
	
	
	return true;
}


void State_Eat::Enter(Actor* actor)
{
	if (LocationToString(actor->GetCurrentLocation()) == "Restaurant")
	{
		cout << actor->GetName() << " goes to the Restaurant" << endl; 
		actor->Greet();
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
		if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
		{
			actor->RequestMeetup();
			return;
		}
		if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
			return;
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);
			return;
		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
			return;
		}
		else
		{
			if (actor->GetMoney() >= 2000 && actor->GetFood() <= 3)
			{
				actor->ChangeState(new State_Shopping);
				return;
			}
			else if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Walk);
				return;
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
					return;
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
					return;
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
	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2);
		cout << msg.MessageContent << endl;
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
		cout << msg.MessageContent << endl;
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{
			if (msg.ExtraInfo.Respond)
			{
				std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I am eating food";
				ExtraInfo info;
				info.Respond = false;
				MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
			}
		
		}
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP&&actor->GetHunger()<=15.0f)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}
		else if(msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			if (msg.ExtraInfo.Respond)
			{
				std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " something came up I can't make it";
				ExtraInfo info;
				info.Respond = false;
				MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::CANCEL_MEETUP, info);
			}
		}

	}
	
	
	return true;
}


void State_PilotWork::Enter(Actor* actor) // to change. make seperate states for seperate jobs
{
	if (actor->GetCurrentLocation() != actor->GetJob().jobLocation)
	{
		actor->SetLocation(actor->GetJob().jobLocation);
		cout << actor->GetName() << " goes to the airport to work" << endl;
		actor->Greet();
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
		return;
	}
	if (actor->GetHunger() >= 65 && actor->GetFood() > 0) 
	{
		actor->DecreaseFood(1); 
	
		actor->ChangeState(new State_Eat); 
		return;
	}
	if (actor->GetThirst() >= 50) 
	{
		actor->ChangeState(new State_Drink); 
		return;

	}
	if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
	{
		actor->RequestMeetup();
		return;
	}
	if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200) 
	{
		actor->DecreaseMoney(200); 
		actor->ChangeState(new State_Party); 
		return;
	}
	if (actor->GetEnergy() <= 20)
	{
		actor->ChangeState(new State_Sleep);
		return;
	}
	else
	{

		actor->ChooseJob();
			
		if (actor->GetJob().type == JobType::OFFICE_WORKER)
		{
			actor->ChangeState(new State_OfficeWork);
			return;
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
	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2);
		cout << msg.MessageContent << endl;
		if (msg.ExtraInfo.Respond)
		{
			std::string message = actor->GetName() + ": Hello " + EntityManager::Instance()->GetNameByID(msg.Sender); 
			ExtraInfo info;
			info.Respond = false;
			MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::CONVERSATION, info); 
			
		}
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
		cout << msg.MessageContent << endl; 
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{

			
			if (msg.ExtraInfo.Respond)
			{
				if (actor->GetMoney() > 2000 && actor->GetSocialized() <= 70)
				{
					std::string message = actor->GetName() + ": Yeah sure, on my way now.";
					ExtraInfo info;
					info.Respond = true;
					info.spot = msg.ExtraInfo.spot; 
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info);
					actor->SetLocation(msg.ExtraInfo.spot);
					actor->ChangeState(new State_Socialize);

				}
				else
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I can't go. I am busy working";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
				}

			}
		}
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}

	}
	
	
	
	return true;
}


void State_OfficeWork::Enter(Actor* actor) // to change. make seperate states for seperate jobs
{
	if (actor->GetCurrentLocation() != actor->GetJob().jobLocation)
	{
		actor->SetLocation(actor->GetJob().jobLocation);
		cout << actor->GetName() << " goes to the office to work" << endl;
		actor->Greet();
	}
	
	cout << actor->GetName() << " does work as an Office Worker" << endl;
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
		return;
	}
	if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
	{
		actor->DecreaseFood(1);
		
		actor->ChangeState(new State_Eat);
		return;
	}
	if (actor->GetThirst() >= 50)
	{
		actor->ChangeState(new State_Drink);
		return;

	}
	if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
	{
		actor->RequestMeetup();
		return;
	}
	if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200)
	{
		actor->DecreaseMoney(200);
		actor->ChangeState(new State_Party);
		return;
	}
	if (actor->GetEnergy() <= 20)
	{
		actor->ChangeState(new State_Sleep);
		return;
	}
	else
	{
		
		
		actor->ChooseJob();

		if (actor->GetJob().type == JobType::PILOT)
		{
			actor->ChangeState(new State_PilotWork);
			return;
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

	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2); 
		cout << msg.MessageContent << endl;
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl; 
		cout << msg.MessageContent << endl; 
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{

			
			if (msg.ExtraInfo.Respond)
			{
				if (actor->GetMoney() > 2000 && actor->GetSocialized() <= 70)
				{
					std::string message = actor->GetName() + ": Yeah sure, on my way now.";
					ExtraInfo info;
					info.Respond = true;
					info.spot = msg.ExtraInfo.spot; 
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info);
					actor->SetLocation(msg.ExtraInfo.spot); 
					actor->ChangeState(new State_Socialize);

				}
				else
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I can't go. I am busy working";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
				}

			}
		}
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}
		
	}
	
	
	
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
			return;
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
			return;
		}
		if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
		{
			actor->RequestMeetup();
			return;
		}
		if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
			return;
		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
			return;
		}
		else
		{
			if (actor->GetMoney() >= 2000 && actor->GetFood() <= 3)
			{
				actor->ChangeState(new State_Shopping);
				return;
			}
			else if (actor->GetMoney() >= 2000)
			{
				actor->ChangeState(new State_Walk);
				return;
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
					return;
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
					return;
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
	cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
	cout << msg.MessageContent << endl; 
	if (msg.MsgType == Messagetype::REQUEST_MEETUP)
	{
		
		if (msg.ExtraInfo.Respond)
		{
			if (actor->GetMoney() > 2000 && actor->GetSocialized() <= 70)
			{
				std::string message = actor->GetName() + ": Yeah sure, on my way now.";
				ExtraInfo info;
				info.Respond = true;
				info.spot = msg.ExtraInfo.spot; 
				MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info);
				actor->SetLocation(msg.ExtraInfo.spot); 
				actor->ChangeState(new State_Socialize);

			}
			else
			{
				std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I can't go. I don't feel too good";
				ExtraInfo info;
				info.Respond = false;
				MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
			}

		}
	}
	if (msg.MsgType == Messagetype::ACCEPT_MEETUP&&actor->GetThirst()<=10.0f)
	{
		actor->SetLocation(msg.ExtraInfo.spot);
		actor->ChangeState(new State_Socialize);
	}
	else if(msg.MsgType==Messagetype::ACCEPT_MEETUP)
	{
		std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " something came up I can't go";
		ExtraInfo info;
		info.Respond = false;
		MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::CANCEL_MEETUP, info);
	}
	
	
	
	
	return true;
}


void State_Walk::Enter(Actor* actor)
{
	actor->SetLocation(Location::OUTSIDE);

	cout << actor->GetName() << " goes outside" << endl;
	cout << actor->GetName() << " goes for a walk" << endl;
	actor->Greet();
}
void State_Walk::Execute(Actor* actor)
{
	
	
	if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
	{
		actor->DecreaseMoney(150); //eat at restaurant
		actor->SetLocation(Location::RESTAURANT);
		actor->ChangeState(new State_Eat);
		return;
	}
	if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
	{
		actor->DecreaseFood(1);

		actor->ChangeState(new State_Eat);
		return;
	}
	if (actor->GetThirst() >= 50)
	{
		actor->ChangeState(new State_Drink);
		return;

	}
	if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
	{
		actor->RequestMeetup();
	}
	if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200)
	{
		actor->DecreaseMoney(200);
		actor->ChangeState(new State_Party);
		return;
	}
	if (actor->GetEnergy() <= 20)
	{
		actor->ChangeState(new State_Sleep);
		return;
	}
	else
	{
		if (actor->GetMoney() >= 2000&& actor->GetFood() <= 3)
		{
			actor->ChangeState(new State_Shopping);
			return;
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
				return;
			}
			if (actor->GetJob().type == JobType::OFFICE_WORKER)
			{
				actor->ChangeState(new State_OfficeWork);
				return;
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
	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2);
		cout << msg.MessageContent << endl;
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
		cout << msg.MessageContent << endl;
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{


			if (msg.ExtraInfo.Respond)
			{
				if (actor->GetMoney() > 2000 && actor->GetSocialized() <= 70)
				{
					std::string message = actor->GetName() + ": Yeah sure, on my way now.";
					ExtraInfo info;
					info.Respond = true;
					info.spot = msg.ExtraInfo.spot; 
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info);
					actor->SetLocation(msg.ExtraInfo.spot); 
					actor->ChangeState(new State_Socialize);

				}
				else
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I can't go. I gotta do something";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
				}

			}
		}
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}


	}
	return true;
}


void State_Party::Enter(Actor* actor)
{
	actor->SetLocation(Location::BAR);
	actor->Greet();
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
			return;
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
			return;
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);
			return;
		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
			return;
		}
		else
		{
			if (actor->GetMoney() >= 2000&& actor->GetFood()<=3)
			{
				actor->ChangeState(new State_Shopping);
				return;
			}
			else if (actor->GetMoney()>=2000)
			{
				actor->ChangeState(new State_Walk);
				return;
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
					return;
				}
				if (actor->GetJob().type == JobType::OFFICE_WORKER)
				{
					actor->ChangeState(new State_OfficeWork);
					return;
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
	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2);
		cout << msg.MessageContent << endl;
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
		cout << msg.MessageContent << endl;
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{


			if (msg.ExtraInfo.Respond)
			{
				if (actor->GetMoney() > 2000 && actor->GetSocialized() <= 70)
				{
					std::string message = actor->GetName() + ": Yeah sure, on my way now.";
					ExtraInfo info;
					info.Respond = true;
					info.spot = msg.ExtraInfo.spot; 
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info);
					actor->SetLocation(msg.ExtraInfo.spot); 
					actor->ChangeState(new State_Socialize);

				}
				else
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I can't go. I am busy working";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
				}

			}
		}
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}


	}
	
	
	return true;
}


void State_Shopping::Enter(Actor* actor)
{
	actor->SetLocation(Location::WALMART);

	cout << actor->GetName() << " goes to the store to shop" << endl;
	actor->Greet();
	
}
void State_Shopping::Execute(Actor* actor)
{
	if (actor->GetFood() <= 8)
	{
		actor->DecreaseMoney(50);// each item is 50 
		actor->IncreaseFood(1); 
	}
	
	actor->DecreaseMoney(100);// 100 per gift card
	actor->IncreaseGiftCards(1);

	actor->DecreaseEnergy(0.05f);
	actor->IncreaseThirst(0.2f);
	actor->IncreaseHunger(0.05f);
	


	if (actor->GetMoney()<=400) // he doesnt have much money left
	{
		if (actor->GetHunger() >= 65 && actor->GetMoney() >= 150 && actor->GetFood() == 0)
		{
			actor->DecreaseMoney(150); //buys new food 
			actor->SetLocation(Location::RESTAURANT);
			actor->ChangeState(new State_Eat);
			return;
		}
		if (actor->GetHunger() >= 65 && actor->GetFood() > 0)
		{
			actor->DecreaseFood(1);
			
			actor->ChangeState(new State_Eat);
			return;
		}
		if (actor->GetThirst() >= 50)
		{
			actor->ChangeState(new State_Drink);
			return;
		}
		if (actor->GetSocialized() < 40 && !actor->HasSentMessage())
		{
			actor->RequestMeetup();
			return;
		}
		if (actor->GetSocialized() < 30 && actor->GetMoney() >= 200)
		{
			actor->DecreaseMoney(200);
			actor->ChangeState(new State_Party);
			return;
		}
		if (actor->GetEnergy() <= 20)
		{
			actor->ChangeState(new State_Sleep);
			return;
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
				return;
			}
			if (actor->GetJob().type == JobType::OFFICE_WORKER)
			{
				actor->ChangeState(new State_OfficeWork);
				return;
			
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
	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2);
		cout << msg.MessageContent << endl;
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
		cout << msg.MessageContent << endl;
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{


			if (msg.ExtraInfo.Respond)
			{
				if (actor->GetMoney() > 2000 && actor->GetSocialized() <= 70)
				{
					std::string message = actor->GetName() + ": Yeah sure, on my way now.";
					ExtraInfo info;
					info.Respond = true;
					info.spot = msg.ExtraInfo.spot;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info);
					actor->SetLocation(msg.ExtraInfo.spot);
					actor->ChangeState(new State_Socialize);

				}
				else
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(msg.Sender) + " I can't go. I am busy working";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::DECLINE_MEETUP, info);
				}

			}
		}
		if (msg.MsgType == Messagetype::ACCEPT_MEETUP)
		{
			actor->SetLocation(msg.ExtraInfo.spot);
			actor->ChangeState(new State_Socialize);
		}


	}
	
	return true;
}

void State_Socialize::Enter(Actor* actor)
{
	cout << actor->GetName() << " starts socializing at the " << LocationToString(actor->GetCurrentLocation())<<endl;
}
void State_Socialize::Execute(Actor* actor)
{

	actor->DecreaseEnergy(0.15f);
	actor->IncreaseThirst(0.3f);
	actor->IncreaseHunger(0.1f);
	actor->IncreaseSocialized(0.4f);
	if (actor->GetHunger()>=60)
	{
		std::vector<int> actorsNearbyID = EntityManager::Instance()->AtLocation(actor->GetCurrentLocation());
		if (!actorsNearbyID.empty())
		{
			for (auto peopleID : actorsNearbyID)
			{
				if (peopleID != actor->GetID())
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(peopleID) + " something came up I can't stay ";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), peopleID, message, Messagetype::CANCEL_MEETUP, info);
				}
			}
		}
		actor->ChangeState(new State_Eat);
	}
	if (actor->GetThirst() >= 60)
	{
		std::vector<int> actorsNearbyID = EntityManager::Instance()->AtLocation(actor->GetCurrentLocation());
		if (!actorsNearbyID.empty())
		{
			for (auto peopleID : actorsNearbyID)
			{
				if (peopleID != actor->GetID())
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(peopleID) + " something came up I can't stay ";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), peopleID, message, Messagetype::CANCEL_MEETUP, info);
				}
			}
		}
		actor->ChangeState(new State_Drink);
	}
	if (actor->GetEnergy() <= 20)
	{
		std::vector<int> actorsNearbyID = EntityManager::Instance()->AtLocation(actor->GetCurrentLocation());
		if (!actorsNearbyID.empty())
		{
			for (auto peopleID : actorsNearbyID)
			{
				if (peopleID != actor->GetID())
				{
					std::string message = actor->GetName() + ": Sorry " + EntityManager::Instance()->GetNameByID(peopleID) + "I'm tired I gotta go ";
					ExtraInfo info;
					info.Respond = false;
					MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), peopleID, message, Messagetype::CANCEL_MEETUP, info);
				}
			}
		}
		actor->ChangeState(new State_Sleep);
	}
	if (actor->GetSocialized() >= 80)
	{

		if (actor->GetMoney() >= 2000) 
		{
			actor->ChangeState(new State_Walk); 
			return;
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
				return;
			}
			if (actor->GetJob().type == JobType::OFFICE_WORKER) 
			{
				actor->ChangeState(new State_OfficeWork); 
				return;
			}
		}
		
		
	}
}
void State_Socialize::Exit(Actor* actor)
{
	cout << actor->GetName() << " stops socializing at the " << LocationToString(actor->GetCurrentLocation()) << endl;
}
bool State_Socialize::OnMessage(Actor* actor, const Telegram& msg)
{
	if (msg.MsgType == Messagetype::CONVERSATION)
	{
		actor->IncreaseSocialized(2);
		cout << msg.MessageContent << endl;
	}
	else
	{
		cout << actor->GetName() << " has received message  from " << EntityManager::Instance()->GetNameByID(msg.Sender) << endl;
		cout << msg.MessageContent << endl;
		if (msg.MsgType == Messagetype::CANCEL_MEETUP)
		{
			State* state = actor->GetPreviousState();
			actor->ChangeState(state); // if meetup is canceled. go back to what you were doing before
				
			
		}
		if (msg.MsgType == Messagetype::REQUEST_MEETUP)
		{
			std::string message = actor->GetName() + ": Yeah, I'm already there"; 
			ExtraInfo info; 
			info.Respond = true; 
			info.spot = msg.ExtraInfo.spot; 
			MessageDispatcher::Instance()->DispatchMessage(0.0, actor->GetID(), msg.Sender, message, Messagetype::ACCEPT_MEETUP, info); 
		}
		
	}
	return true;
}