#include "Routine.h"
#include <cstddef>
#include <ctime>

int Routine::iterationsCompleted(Routine_t *r)
{
    return r->step_idx % r->steps.size();
}

int Routine::currentIndex(Routine_t *r)
{
    return r->step_idx;
}

int Routine::totalSteps(Routine_t *r)
{
    return r->steps.size();
}

bool Routine::isDone(Routine_t *r)
{
    if (r->steps.empty())
    {
        return true;
    }
    if (r->iterations == -1)
    {
        return false;
    }

    bool iterationsDone = iterationsCompleted(r) >= r->iterations;
    return iterationsDone;
}

std::vector<PumpDataProcess::PumpDataProcess_t> Routine::currentAction(Routine_t *r)
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

void Routine::setTimer(Routine_t *r, double duration)
{
    r->timer_duration = duration;
    r->start_time = static_cast<double>(std::time(nullptr));
}

double Routine::elapsed(Routine_t *r)
{
    return static_cast<double>(std::time(nullptr)) - r->start_time;
}

double Routine::untilNext(Routine_t *r)
{
    return r->timer_duration - elapsed(r);
}

bool Routine::newActionDue(Routine_t *r)
{
    return untilNext(r) <= 0;
}

std::vector<PumpDataProcess::PumpDataProcess_t> Routine::getNextActionOrNone(Routine_t *r)
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

void Routine::addPumpDataProcessSteps(Routine_t *r, const PumpDataProcess::PumpDataProcess_t &pumpDataProcess)
{
    for (const auto &step : pumpDataProcess.pumpSteps)
    {
        // Create a PumpDataProcess_t object and set its properties
        PumpDataProcess::PumpDataProcess_t pumpData;
        pumpData.vol_per_turn_ul = pumpDataProcess.vol_per_turn_ul;
        pumpData.pumpSteps.push_back(step);

        // Add the new PumpDataProcess_t object to the steps vector
        r->steps.push_back(pumpData);
    }
}
