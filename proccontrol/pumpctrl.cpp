// g++ -o pumpctrl pumpctrl.cpp

#include <thread>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstddef>
#include <cstdio>

#include "pumpctrl.h"

void PumpDataProcess::add_pump_step(PumpDataProcess_t* pdp, double flowrate_ul_min, double vol_ul)
{
	PumpStep_t step;

	double flowrate_per_sec = flowrate_ul_min / 60.0;
	double duration_s = std::abs(vol_ul / flowrate_per_sec);
	double turns = std::abs(vol_ul / pdp->vol_per_turn_ul);
	double turn_per_sec = turns / duration_s;

	step.duration_s = duration_s;
	step.turn_per_sec = turn_per_sec;

	(pdp->pumpSteps).push_back(step);
}

std::size_t PumpDataProcess::get_pump_steps_size(PumpDataProcess_t* pdp)
{
	return pdp->pumpSteps.size();
}

std::vector<PumpDataProcess::PumpStep_t> PumpDataProcess::get_pump_steps(PumpDataProcess_t* pdp)
{
	return pdp->pumpSteps;
}

PumpDataProcess::Routine_t PumpDataProcess::load_into_routine(PumpDataProcess_t* pdp,
															  int iterations)
{
	Routine_t routine;
	routine.iterations = iterations;

	if ((routine.iterations == 1) || ((pdp->pumpSteps).size() % 2 == 0)) {
		routine.step_idx = -1;
		if ((pdp->pumpSteps).size() == 1) {
			routine.step_idx = -1;
		}
	}

	if (iterations > 1 && (pdp->pumpSteps).size() % 2 != 0 && (pdp->pumpSteps).size() > 1) {
		routine.step_idx = routine.iterations - 2;
	}

	if ((iterations > 1) && (pdp->pumpSteps).size() == 1) {
		routine.step_idx = routine.iterations - 2;
	}

	routine.steps = pdp->pumpSteps;
	return routine;
}

bool PumpDataProcess::isDone(Routine_t* r)
{
	if (r->steps.empty()) {
		printf("Steps empty!");
		return true;
	}
	if (r->iterations == -1) {
		printf("Iterations equal to -1");
		return false;
	}

	int iterations = r->iterations;
	printf("Total iterations: %d\n", iterations);
	bool iterationsDone = iterationsCompleted(r) >= iterations;
	return iterationsDone;
}

int PumpDataProcess::iterationsCompleted(Routine_t* r)
{
	printf("Before calculation: step_idx=%d, steps.size()=%zu, iterations=%d\n", r->step_idx,
		   r->steps.size(), r->iterations);

	int iterations_completed;

	if (r->steps.size() % 2 == 0) {
		iterations_completed = r->step_idx / r->steps.size();
	} else {
		iterations_completed = (r->step_idx + 1) / (r->steps.size() + 1);
	}

	printf("Iterations Completed: %d out of %d\n", iterations_completed, r->iterations);

	return iterations_completed;
}

void PumpDataProcess::setTimer(Routine_t* r, double duration)
{
	r->timer_duration = duration;
	r->start_time = static_cast<double>(std::time(nullptr));

	std::cout << "Timer set. Duration: " << duration << " seconds. Start Time: " << r->start_time
			  << std::endl;
}

double PumpDataProcess::elapsed(Routine_t* r)
{
	return static_cast<double>(std::time(nullptr)) - r->start_time;
}

double PumpDataProcess::untilNext(Routine_t* r)
{
	double time = r->timer_duration - elapsed(r);
	printf("Time until next action: %f seconds\n", (time < 0) ? 0.0 : time);
	return (time < 0) ? 0.0 : time;
}

bool PumpDataProcess::newActionDue(Routine_t* r)
{
	return untilNext(r) <= 0;
}

PumpDataProcess::PumpStep_t PumpDataProcess::schedActionOrNone(Routine_t* r)
{
	if (!newActionDue(r) || isDone(r)) {
		return {};
	}

	printf("__________________ step_idx incremented! __________________\n");
	r->step_idx += 1;
	if (r->step_idx != 0 && r->step_idx % r->steps.size() == 0) {
		if (iterationsCompleted(r) > r->iterations) {
			return {};
		}
	}

	PumpStep_t action = r->steps[r->step_idx % r->steps.size()];
	setTimer(r, action.duration_s);
	return action;
}

int main()
{
	PumpDataProcess pumpProcess;

	PumpDataProcess::PumpDataProcess_t pumpData;
	pumpData.vol_per_turn_ul = 10.0;

	pumpProcess.add_pump_step(&pumpData, 1200.0, 40.0);
	pumpProcess.add_pump_step(&pumpData, 1200.0, 30.0);
	pumpProcess.add_pump_step(&pumpData, 1200.0, 30.0);

	std::vector<PumpDataProcess::PumpStep_t> pumpSteps = pumpProcess.get_pump_steps(&pumpData);

	for (const auto& step : pumpSteps) {
		std::cout << "Duration: " << step.duration_s
				  << " seconds, Turn per sec: " << step.turn_per_sec << std::endl;
	}

	std::size_t pumpStepsSize = pumpProcess.get_pump_steps_size(&pumpData);
	std::cout << "Size of pumpSteps vector: " << pumpStepsSize << std::endl;

	int iterations = 3;
	PumpDataProcess::Routine_t routine = pumpProcess.load_into_routine(&pumpData, iterations);

	std::cout << "Routine Steps:" << std::endl;
	for (const auto& step : routine.steps) {
		std::cout << "Duration: " << step.duration_s
				  << " seconds, Turn per sec: " << step.turn_per_sec << std::endl;
	}

	pumpProcess.iterationsCompleted(&routine);

	while (!pumpProcess.isDone(&routine)) {
		std::cout << "Looping..." << std::endl;
		PumpDataProcess::PumpStep_t action = pumpProcess.schedActionOrNone(&routine);

		if (action.duration_s > 0) {
			std::cout << "Performing action with duration: " << action.duration_s << " seconds\n";
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
	}

	return 0;
}
