#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

// The distance from Beijing South to Tianjin is 140 Km
// Normally, this should take about 33 minutes, but this depends on
// the acceleration and velocity profile, which further depends on how
// well velocity can be estimated and an ideal acceleration and braking profile
// followed.

#define CLOCKS_PER_MICROSEC (1000)
#define TRAVEL_TIME_SECS (2000)
#define MAX_TRAVEL_TIME_ALLOWED (5000)
#define MPK (1000)
#define KPM (1.0/1000.0)
#define SPH (3600.0)
#define MAX_VEL_KPH (300.0)
#define UNSAFE_VEL_KPH (303.0)
#define MAX_VEL_KPS (MAX_VEL_KPH/SPH)
#define TIME_TO_MAX_VEL ((float)TRAVEL_TIME_SECS/10.0)
#define TIME_TO_STOP ((float)TRAVEL_TIME_SECS/50.0)
#define MAX_ACCEL_KPSPS (MAX_VEL_KPS/(TIME_TO_MAX_VEL))
#define MAX_DECEL_KPSPS (MAX_VEL_KPS/(TIME_TO_STOP))

#define MAX_VEL_MPS (MAX_VEL_KPS*MPK)
#define MAX_ACCEL_MPSPS (MAX_ACCEL_KPSPS*MPK)
#define MAX_DECEL_MPSPS (MAX_DECEL_KPSPS*MPK)

#define TRAVEL_DISTANCE_KM (140)
#define TRAVEL_DISTANCE_M (140*MPK)

#define PI 3.14159265359879323846f

// Functions you must implement in ARM ASM
extern float accel_f(float time);
extern float integrator(float t, float dt, float (*funcptr)(float));

// State update functions
extern float pos_f(float time);
extern float vel_f(float time);
extern void update_profile(float t, float a, float v, float p);
extern void zero_profiles(void);
extern void dump_profile(void);
