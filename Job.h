#pragma once
#include <iostream>
enum class JobType
{
    OFFICE_WORKER, PILOT, UNEMPLOYED
};

struct Job
{
    JobType type;
    int incomeRate;
    float hungerRate;
    float thirstRate;
    float energyRate;

};
Job CreateJob(JobType type);


