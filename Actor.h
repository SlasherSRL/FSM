#pragma once
#include "BaseGameEntity.h"

enum class JobType
{
    OFFICE_WORKER, PILOT,UNEMPLOYED
};

struct Job
{
    JobType type;
    int incomeRate;
    int hungerRate;
    int thirstRate;
    int energyRate;
    
};
Job CreateJob(JobType type)
{
    switch(type)
    {
        case JobType::OFFICE_WORKER:
            return {type, 10, 1 / 10.0f, 1 / 3.0f, 1 / 2.0f};  // Hunger, Thirst, Energy rates
        case JobType::PILOT:
            return {type, 15, 1 / 8.0f, 1 / 2.0f, 1 / 3.0f};  // Pilots thirst more and tire faster
        case JobType::UNEMPLOYED:
            return {type, 0, 1 / 15.0f, 1 / 5.0f, 1 / 4.0f};  // Unemployed have slower rates
        default:
            std::cerr<<"Uknown Job type"<<std::endl;
    }
}

class Actor :
    public BaseGameEntity
{
private:
    
    int money;
    float thirst;
    float hunger;
    float energy;
    int happiness;
    Job job;

public:
    Actor(int id, JobType job);

    void Update();

    void ChangeState();

    float GetHunger()const; 
    float GetThirst()const; 
    float GetEnergy()const;
};

