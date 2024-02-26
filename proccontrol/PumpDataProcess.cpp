// g++ -o PumpDataProcess PumpDataProcess.cpp

#include <cmath>
#include <ctime>
#include <iostream>
#include <cstddef>
#include <cstdio>

#include "PumpDataProcess.h"

void PumpDataProcess::add_pump_step(double flowrate_ul_min, double vol_ul)
{
    if (!pumpDataProcessList.empty())
    {
        // Assume adding steps to the first pump
        PumpDataProcess_t &currentPump = pumpDataProcessList.back();

        double flowrate_per_sec = flowrate_ul_min / 60.0;
        double duration_s = std::abs(vol_ul / flowrate_per_sec);
        double turns = std::abs(vol_ul / currentPump.vol_per_turn_ul);
        double turn_per_sec = turns / duration_s;

        // Create a PumpStep_t element
        PumpStep_t step;
        step.duration_s = duration_s;
        step.turn_per_sec = turn_per_sec;

        // Add the PumpStep_t element to the current pump
        currentPump.pumpSteps.push_back(step);
    }
    else
    {
        std::cerr << "No pumps available to add steps." << std::endl;
    }
}

void PumpDataProcess::add_pump_data_process(double vol_per_turn_ul)
{
    PumpDataProcess_t pumpDataProcess;
    pumpDataProcess.vol_per_turn_ul = vol_per_turn_ul;

    // Add the new pump data process to the collection
    pumpDataProcessList.push_back(pumpDataProcess);
}

void PumpDataProcess::loadStepsIntoRoutine(Routine_t *r, int iterations)
{
    r->iterations=iterations;
    // Check if there are pump data processes to load
    if (!pumpDataProcessList.empty())
    {
        // Clear existing steps in the routine
        r->steps.clear();

        // Iterate through each pump data process
        for (const auto &pumpDataProcess : pumpDataProcessList)
        {
            // Print information about the pump data process
            printf("Pump - Vol per Turn: %f ul\n", pumpDataProcess.vol_per_turn_ul);

            // Iterate through each step in the pump data process
            for (const auto &step : pumpDataProcess.pumpSteps)
            {
                // Print information about each step
                printf("  Step - Duration: %f s, Turn per Sec: %f\n", step.duration_s, step.turn_per_sec);

                // Add the step to the routine
                r->steps.push_back(pumpDataProcess); // Add the whole pump data process
            }
        }
    }
    else
    {
        std::cerr << "No pump data processes available to load into the routine." << std::endl;
    }
}

void PumpDataProcess::print_pump_data_processes()
{
    for (size_t i = 0; i < pumpDataProcessList.size(); ++i)
    {
        std::cout << "Pump " << i + 1 << " - Vol per Turn: " << pumpDataProcessList[i].vol_per_turn_ul << " ul" << std::endl;
        for (const auto &step : pumpDataProcessList[i].pumpSteps)
        {
            std::cout << "  Step - Duration: " << step.duration_s << " s, Turn per Sec: " << step.turn_per_sec << std::endl;
        }
        std::cout << std::endl;
    }
}

int PumpDataProcess::iterationsCompleted(Routine_t *r)
{
    int iterations_completed = r->step_idx % r->steps.size();
    printf("Iterations Completed: %d\n", iterations_completed);
    return iterations_completed;
}

int PumpDataProcess::currentIndex(Routine_t *r)
{
    return r->step_idx;
}

int PumpDataProcess::totalSteps(Routine_t *r)
{
    int totalSteps = r->steps.size();
    printf("Total Steps: %d\n", totalSteps);
    return totalSteps;
}

bool PumpDataProcess::isDone(Routine_t *r)
{
    if (r->steps.empty())
    {
        printf("Steps empty!");
        return true;
    }
    if (r->iterations == -1)
    {
        printf("Iterations equal to -1");
        return false;
    }

    int iterations = r->iterations;
    printf("Total iterations: %d\n", iterations);
    bool iterationsDone = iterationsCompleted(r) >= iterations;
    return iterationsDone;
}

std::vector<PumpDataProcess::PumpDataProcess_t> PumpDataProcess::currentAction(Routine_t *r)
{
    std::vector<PumpDataProcess::PumpDataProcess_t> noneVector;

    if (isDone(r) || r->step_idx == -1)
    {
        return noneVector;
    }
    else
    {
        if (r->step_idx >= 0 && static_cast<size_t>(r->step_idx) < r->steps.size())
        {
            return {r->steps[static_cast<size_t>(r->step_idx)]};
        }
        else
        {
            return noneVector;
        }
    }
}

void PumpDataProcess::setTimer(Routine_t *r, double duration)
{
    r->timer_duration = duration;
    r->start_time = static_cast<double>(std::time(nullptr));
}

double PumpDataProcess::elapsed(Routine_t *r)
{
    return static_cast<double>(std::time(nullptr)) - r->start_time;
}

double PumpDataProcess::untilNext(Routine_t *r)
{
    return r->timer_duration - elapsed(r);
}

bool PumpDataProcess::newActionDue(Routine_t *r)
{
    return untilNext(r) <= 0;
}

std::vector<PumpDataProcess::PumpDataProcess_t> PumpDataProcess::getNextActionOrNone(Routine_t *r)
{
    if (!newActionDue(r) || isDone(r))
    {
        return {};
    }

    r->step_idx += 1;

    if (r->step_idx != 0 && r->step_idx % r->steps.size() == 0)
    {
        if (iterationsCompleted(r) == r->iterations)
        {
            return {};
        }
    }

    std::vector<PumpDataProcess::PumpDataProcess_t> action = currentAction(r);

    return action;
}

int main()
{
    PumpDataProcess pumpProcessor;
    pumpProcessor.add_pump_data_process(100.0);
    pumpProcessor.add_pump_step(4000.0, 200.0);
    pumpProcessor.add_pump_step(4000.0, 200.0);
    pumpProcessor.add_pump_step(4000.0, 200.0);
    pumpProcessor.print_pump_data_processes();

    PumpDataProcess::Routine_t routine;
    pumpProcessor.loadStepsIntoRoutine(&routine,2);
    pumpProcessor.totalSteps(&routine);
    bool done_flag = pumpProcessor.isDone(&routine);
    printf("Done flag: %s\n", done_flag ? "true" : "false");

    return 0;
}