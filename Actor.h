#pragma once
#include "BaseGameEntity.h"
#include "Job.h"
#include "Location.h"
#include "FSM.h"
#include<iostream>

class Actor :
    public BaseGameEntity
{
private:

    Location currentLocation=Location::OUTSIDE; 

    State* currentState;
    int money;
    float thirst;
    bool isThirsty;

    float hunger;
    bool isHungry;

    float energy;
    bool isTired;

    int socialized;
    bool needsSocializing;
    Job job;

public:
    Actor(int id, JobType newJob = JobType::UNEMPLOYED);


    void Update();

    void ChangeState(State* state);

    void SetJob(Job& newJob);
    float GetHunger()const; 
    float GetThirst()const; 
    float GetEnergy()const;
    int GetMoney()const;

    void DecreaseHunger(float amount);
    void DecreaseThirst(float amount);
    void IncreaseEnergy(float amount);
    void DecreaseMoney(int amount);
    void IncreaseSocialized(int amount);

    Location GetCurrentLocation()const;
};

