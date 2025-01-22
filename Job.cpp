#include "Job.h"
Job CreateJob(JobType type)
{
    switch (type)
    {
        // job type, income rate, hunger rate, thirst rate, energy consumption rate
    case JobType::OFFICE_WORKER:
        return { type, 10, 1 / 10.0f, 1 / 3.0f, 1 / 10.0f };  //
    case JobType::PILOT:
        return { type, 20, 1 / 8.0f, 1 / 2.0f, 1 / 9.0f };  //
    case JobType::UNEMPLOYED:
        return { type, 0, 1 / 15.0f, 1 / 5.0f, 1 / 8.0f };  //
    default:
        std::cerr << "Uknown Job type" << std::endl;
    }
}