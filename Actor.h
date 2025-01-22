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
    bool isThirsty;

    float hunger;
    bool isHungry;

    float energy;
    bool isTired;

    float socialized;
    bool needsSocializing;
    
    

    int food;

    Location currentLocation;
    Job job;
    FSM<Actor>* stateMachine;
    std::string name;
public:
    Actor(int id, std::string myName);


    void Update();

    void ChangeState(State* state);

    void ChooseJob();

    Job GetJob()const;
    std::string GetName()const;
    float GetHunger()const; 
    float GetThirst()const; 
    float GetEnergy()const;
    int GetMoney()const;
    float GetSocialized()const;

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



   
    void SetLocation(Location location);
    Location GetCurrentLocation()const;
};

