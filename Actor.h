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
            return{type,20,5,3,2};
        case JobType::PILOT:
            return{type,50,6,4,3};
        case JobType::UNEMPLOYED:
            return {type,0,2,2,1};
        default:
            std::cerr<<"Uknown Job type"<<std::endl;
    }
}

class Actor :
    public BaseGameEntity
{
private:
    
    int money;
    int thirst;
    int hunger;
    int energy;
    int happiness;
    Job job;

public:
    Actor(int id, JobType job);

    void Update();

    void ChangeState();
};

