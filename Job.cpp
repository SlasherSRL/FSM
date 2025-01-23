#include "Job.h"
Job CreateJob(JobType type)
{
    Job newJob;
    switch (type)
    {
        
    case JobType::OFFICE_WORKER:
        newJob.type = type;
        newJob.JobName = "Office Worker";
        newJob.jobLocation = Location::OFFICE;
        newJob.incomeRate = 3;
        newJob.hungerRate = 1 / 5.0f;
        newJob.thirstRate = 1 / 3.0f;
        newJob.energyRate = 1 / 15.0f;
        break;
        
    case JobType::PILOT:
        newJob.type = type;
        newJob.JobName = "Pilot";
        newJob.jobLocation = Location::AIRPORT;
        newJob.incomeRate = 8;
        newJob.hungerRate = 1 / 9.0f;
        newJob.thirstRate = 1 / 4.0f;
        newJob.energyRate = 1 / 9.0f;
        break;
    default:
        std::cerr << "Uknown Job type" << std::endl;
    }
    return newJob;
}