#include <vector>

class PumpDataProcess {
public:
	typedef struct PumpStep_s {
		double duration_s;
		double turn_per_sec;
	} PumpStep_t;

	typedef struct PumpDataProcess_s {
		double vol_per_turn_ul;
		std::vector<PumpStep_t> pumpSteps;
	} PumpDataProcess_t;

	typedef struct Routine_s {
		int iterations;
		int step_idx;
		double start_time;
		double timer_duration;
		std::vector<PumpStep_t> steps;
	} Routine_t;

	Routine_t load_into_routine(PumpDataProcess_t* pdp, int iterations);
	std::vector<PumpStep_t> get_pump_steps(PumpDataProcess_t* pdp);
	void add_pump_step(PumpDataProcess_t* pdp, double flowrate_ul_min, double vol_ul);
	std::size_t get_pump_steps_size(PumpDataProcess_t* pdp);
	bool isDone(Routine_t* r);
	int iterationsCompleted(Routine_t* r);
	void setTimer(Routine_t* r, double duration);
	double elapsed(Routine_t* r);
	double untilNext(Routine_t* r);
	bool newActionDue(Routine_t* r);
	PumpDataProcess::PumpStep_t schedActionOrNone(Routine_t* r);

private:
};