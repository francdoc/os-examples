#pragma once

#include <vector>
#include "Routine.h"

class PumpDataProcess
{
public:

    typedef struct PumpStep_s
    {
        double duration_s;
        double turn_per_sec;
    } PumpStep_t;

    typedef struct PumpDataProcess_s
    {
        double vol_per_turn_ul;
        std::vector<PumpStep_t> pumpSteps;
    } PumpDataProcess_t;

    void add_pump_step(double flowrate_ul_min, double vol_ul);
    void add_pump_data_process(double vol_per_turn_ul);
    void print_pump_data_processes();

private:
    std::vector<PumpDataProcess_t> pumpDataProcesses;
};