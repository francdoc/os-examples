#include "imu.h"

 
int main(void)
{
  float t=0.0, dt=0.0, accel=0.0, vel=0.0, pos=0.0, dv=0.0, dpos=0.0;
  float ts=0.0, max_vel=0.0, max_accel=0.0;
  double hpt=0.0, hpdt=0.0;
  int i, time0, time1, step=0;

  // zero profiles
  zero_profiles();

  // at time zero
  update_profile(t, accel, vel, pos);

  hpdt=1.0/100.0;   // 10 millisec step size
  dt=(float)hpdt;   // 10 millisec step size

  printf("Departing Beijing South @ t=%f, Max Speed of %6.2f [Km/hr] or %f [M/sec], Expected Travel time of %4.2f hours\n", t, MAX_VEL_KPH, MAX_VEL_MPS, ((float)TRAVEL_TIME_SECS/SPH));
  printf("...\n");

  time0=clock();

  do
  {

    // update time
    hpt+=hpdt;
    t=(float)hpt;

    // update state with integrator
    accel=accel_f(t);
    dv=integrator(t, dt, &accel_f);
    vel+=dv;
    dpos=integrator(t, dt, &vel_f);
    pos+=dpos;

    //printf("step=%d, t=%f, a=%f, v=%f, p=%f, dt=%f\n", step, t, accel, vel, pos, dt);
  
    // track maximum velocity
    if(vel > max_vel) max_vel=vel;
    if(accel > max_accel) max_accel=accel;
 
    // update profile 
    if((t-ts) >= 1.0) // 1 second(s) has passed, so save to profile
    {
      update_profile(t, accel, vel, pos);
      ts=t; // save time of this sample
    }

    step++;
  } while((t < ((float)MAX_TRAVEL_TIME_ALLOWED)) && (pos < (float)TRAVEL_DISTANCE_M));

  time1=clock();

  printf("Simulation time = %f microseconds\n", (float)(time1-time0)/CLOCKS_PER_MICROSEC);

  if(pos < (float)TRAVEL_DISTANCE_M)
  {
    printf("\nTrain BROKE DOWN @ t=%f just %f meters short of Tianjin in %4.2f hours, Max Clocked Speed of %6.2f [Km/hr] or %f [M/sec] and Max Acceleration of %f [M/sec] measured\n", t, (pos - (float)TRAVEL_DISTANCE_M), (t/SPH), (max_vel*KPM*SPH), max_vel, max_accel);
  }
  else
  {
    printf("\nArrived Tianjin @ t=%f in %4.2f hours, Max Clocked Speed of %6.2f [Km/hr] or %f [M/sec] and Max Acceleration of %f [M/sec] measured\n", t, (t/SPH), (max_vel*KPM*SPH), max_vel, max_accel);
  }

  dump_profile();
  printf("Final vel=%f, pos=%f\n", vel, pos);
}
