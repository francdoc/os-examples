#include <vector>

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

    typedef struct Routine_s
    {
        int iterations;
        int step_idx;
        double start_time;
        double timer_duration;
        std::vector<PumpDataProcess_t> steps;
    } Routine_t;

    void add_pump_step(double flowrate_ul_min, double vol_ul);
    void add_pump_data_process(double vol_per_turn_ul);
    void print_pump_data_processes();

    void loadStepsIntoRoutine(Routine_t *r,int iterations);
    int iterationsCompleted(Routine_t *r);
    int currentIndex(Routine_t *r);
    int totalSteps(Routine_t *r);
    bool isDone(Routine_t *r);
    void setTimer(Routine_t *r, double duration);
    double elapsed(Routine_t *r);
    double untilNext(Routine_t *r);
    bool newActionDue(Routine_t *r);
    std::vector<PumpDataProcess::PumpDataProcess_t> currentAction(Routine_t *r);
    std::vector<PumpDataProcess::PumpDataProcess_t> getNextActionOrNone(Routine_t *r);

    std::vector<PumpDataProcess_t> pumpDataProcessList;

private:
};