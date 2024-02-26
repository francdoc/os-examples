#include "PumpDataProcess.h"

#ifndef ROUTINE_H
#define ROUTINE_H

class Routine
{
public:
    typedef struct Routine_s
    {
        int iterations;
        int step_idx;
        double start_time;
        double timer_duration;
        std::vector<PumpDataProcess::PumpDataProcess_t> steps;
    } Routine_t;

    int iterationsCompleted(Routine_t *r);
    int currentIndex(Routine_t *r);
    int totalSteps(Routine_t *r);
    bool isDone(Routine_t *r);
    std::vector<PumpDataProcess::PumpDataProcess_t> currentAction(Routine_t *r);
    void setTimer(Routine_t *r, double duration);
    double elapsed(Routine_t *r);
    double untilNext(Routine_t *r);
    bool newActionDue(Routine_t *r);
    std::vector<PumpDataProcess::PumpDataProcess_t> getNextActionOrNone(Routine_t *r);
    void addPumpDataProcessSteps(Routine_t *r, const PumpDataProcess::PumpDataProcess_t &pumpDataProcess);
};

#endif // ROUTINE_H
