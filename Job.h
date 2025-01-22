#pragma once
#include <iostream>
#include "Location.h"
enum class JobType
{
    OFFICE_WORKER, PILOT, //UNEMPLOYED
};

struct Job
{
    JobType type;
    std::string JobName;
    Location jobLocation;
    int incomeRate;
    float hungerRate;
    float thirstRate;
    float energyRate;

};
Job CreateJob(JobType type);


