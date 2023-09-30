#include "imu.h"

float accel_f(float time)
{

  float t = time/((float)TRAVEL_TIME_SECS/(PI));
  float accel;

  // inside acceleration window
  if((time < ((float)TRAVEL_TIME_SECS - TIME_TO_STOP)) && (vel_f(time) < MAX_VEL_MPS))
  {
    // Approximate with Taylor series
    accel=(MAX_ACCEL_MPSPS * (t - ((t*t*t)/6.0) + ((t*t*t*t*t)/120.0) - (t*t*t*t*t*t*t)/940.0));

  }

  // inside braking window
  else if((time > ((float)TRAVEL_TIME_SECS - TIME_TO_STOP)) && (vel_f(time) > 4.0)) // inside braking window and moving
  {
    // Call braking function
    accel=-MAX_DECEL_MPSPS * (1.0 - (((float)TRAVEL_DISTANCE_M - pos_f(time))/(float)TRAVEL_DISTANCE_M));
  }

  // inside braking window, but stopped too soon, re-accelerate to 1/4 speed
  else if((time < ((float)MAX_TRAVEL_TIME_ALLOWED )) && (pos_f(time) < TRAVEL_DISTANCE_M) && (vel_f(time) < MAX_VEL_MPS/4.0))
  {
    // Call function to get to station
    accel=MAX_ACCEL_MPSPS;
  }

  // otherwise just cruise or stand still
  else
  {
    accel=0.0;
  }

  return accel;
}
