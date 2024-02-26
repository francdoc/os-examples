// g++ -o PumpDataProcess PumpDataProcess.cpp

#include <cmath>
#include <iostream>

#include "PumpDataProcess.h"

void PumpDataProcess::add_pump_step(double flowrate_ul_min, double vol_ul)
{
    if (!pumpDataProcesses.empty())
    {
        // Assume adding steps to the first pump
        PumpDataProcess_t &currentPump = pumpDataProcesses.back();

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
    pumpDataProcesses.push_back(pumpDataProcess);
}

void PumpDataProcess::print_pump_data_processes()
{
    for (size_t i = 0; i < pumpDataProcesses.size(); ++i)
    {
        std::cout << "Pump " << i + 1 << " - Vol per Turn: " << pumpDataProcesses[i].vol_per_turn_ul << " ul" << std::endl;
        for (const auto &step : pumpDataProcesses[i].pumpSteps)
        {
            std::cout << "  Step - Duration: " << step.duration_s << " s, Turn per Sec: " << step.turn_per_sec << std::endl;
        }
        std::cout << std::endl;
    }
}


int main()
{
    PumpDataProcess pumpProcessor;

    // pump1
    pumpProcessor.add_pump_data_process(100.0);
    pumpProcessor.add_pump_step(4000.0, 200.0);
    pumpProcessor.add_pump_step(4000.0, 200.0);
    pumpProcessor.add_pump_step(4000.0, 200.0);

    // pump2
    pumpProcessor.add_pump_data_process(15.0);
    pumpProcessor.add_pump_step(4.0, 40.0);
    pumpProcessor.add_pump_step(5.0, 50.0);
    pumpProcessor.add_pump_step(5.0, 50.0);

    pumpProcessor.print_pump_data_processes();

    return 0;
}