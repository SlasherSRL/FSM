#include "Job.h"
Job CreateJob(JobType type)
{
    Job newJob;
    switch (type)
    {
        // job type, income rate, hunger rate, thirst rate, energy consumption rate
    case JobType::OFFICE_WORKER:
        newJob.type = type;
        newJob.JobName = "Office Worker";
        newJob.jobLocation = Location::OFFICE;
        newJob.incomeRate = 10;
        newJob.hungerRate = 1 / 10.0f;
        newJob.thirstRate = 1 / 5.0f;
        newJob.energyRate = 1 / 10.0f;
        break;
        
    case JobType::PILOT:
        newJob.type = type;
        newJob.JobName = "Pilot";
        newJob.jobLocation = Location::AIRPORT;
        newJob.incomeRate = 20;
        newJob.hungerRate = 1 / 8.0f;
        newJob.thirstRate = 1 / 4.0f;
        newJob.energyRate = 1 / 6.0f;
        break;
    //case JobType::UNEMPLOYED:
    //    return { type, "Unemployed",0, 1 / 15.0f, 1 / 5.0f, 1 / 8.0f};  //
    default:
        std::cerr << "Uknown Job type" << std::endl;
    }
    return newJob;
}