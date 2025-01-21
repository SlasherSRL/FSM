#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"

enum class JobType
{
    OFFICE_WORKER, PILOT,UNEMPLOYED
};

struct Job
{
    JobType type;
    int incomeRate;
    float hungerRate;
    float thirstRate;
    float energyRate;
    
};
Job CreateJob(JobType type)
{
    switch(type)
    {
        // job type, income rate, hunger rate, thirst rate, energy consumption rate
        case JobType::OFFICE_WORKER:
            return {type, 10, 1 / 10.0f, 1 / 3.0f, 1 / 2.0f};  // Hunger, Thirst, Energy rates
        case JobType::PILOT:
            return {type, 20, 1 / 8.0f, 1 / 2.0f, 1 / 3.0f};  // Pilots thirst more and tire faster
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

    Location currentLocation;
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

    void SetJob(Job& newJob);
    float GetHunger()const; 
    float GetThirst()const; 
    float GetEnergy()const;
};

