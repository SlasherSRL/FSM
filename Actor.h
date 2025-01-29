#pragma once
#include "BaseGameEntity.h"
#include "Job.h"
#include "FSM.h"
#include "Location.h"

#include<iostream>

class Actor :
    public BaseGameEntity
{
private:

    

  
    int money;

    float thirst;
 
    float hunger;
    
    float energy;
 
    float socialized;

    int food; // amount of food the actor has available to eat
    int giftCards;

    bool isDead;
    bool sentMessage;

    Location currentLocation;
    Job job;
    FSM<Actor>* stateMachine;
    std::string name;
public:
    Actor(int id, std::string myName);


    void Update();

    void ChangeState(State* state);
    State* GetPreviousState();
    virtual bool HandleMessage(const Telegram& msg);

    void RequestMeetup();
    void Greet();
    void ChooseJob();

    Job GetJob()const;
    std::string GetName()const override;
    float GetHunger()const; 
    float GetThirst()const; 
    float GetEnergy()const;
    int GetMoney()const;
    float GetSocialized()const;
    int GetFood()const;
    int GetGiftCards()const;
    bool IsDead()const;

    void PrintStatus()const;

    void DecreaseFood(int amount);
    void IncreaseFood(int amount);

    void DecreaseGiftCards(int amount);
    void IncreaseGiftCards(int amount);

    void DecreaseHunger(float amount);
    void IncreaseHunger(float amount);

    void DecreaseThirst(float amount);
    void IncreaseThirst(float amount);

    void IncreaseEnergy(float amount);
    void DecreaseEnergy(float amount);

    void DecreaseMoney(int amount);
    void IncreaseMoney(int amount);

    void IncreaseSocialized(float amount);
    void DecreaseSocialized(float amount);

    bool HasSentMessage();
    void SentMessage(bool status);
   
    void SetLocation(Location location);
    Location GetCurrentLocation()const;
};

