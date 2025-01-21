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

]

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

