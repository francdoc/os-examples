#include "imu.h"
#include <time.h>

unsigned int deltat(struct timespec *t0, struct timespec *t1)
{
    double ft0, ft1;

    if(t1->tv_sec == t0->tv_sec)  // only nanosecs elapsed between t1 and t2
        return ((t1->tv_nsec - t0->tv_nsec)/1000);
    else if(t1->tv_sec > t0->tv_sec) // seconds rolled over
    {
        ft0 = ((double)((t0->tv_sec)*1000000.0)) + ((double)(t0->tv_nsec)/1000.0);
        ft1 = ((double)((t1->tv_sec)*1000000.0)) + ((double)(t1->tv_nsec)/1000.0);
        return ((unsigned int)(t1-t0));
    }
    else // this is some sort of error condition like t1 is earlier than t0
        return 0;

}

 
int main(void)
{
  float t=0.0, dt=0.0, accel=0.0, vel=0.0, pos=0.0, dv=0.0, dpos=0.0;
  float ts=0.0, max_vel=0.0, max_accel=0.0;
  double hpt=0.0, hpdt=0.0;
  int i, time0, time1, step=0;
  struct timespec t0, t1;

  // zero profiles
  zero_profiles();

  // at time zero
  update_profile(t, accel, vel, pos);

  hpdt=1.0/100.0;   // 10 millisec step size
  dt=(float)hpdt;   // 10 millisec step size

  printf("Departing Beijing South @ t=%f, Max Speed of %6.2f [Km/hr] or %f [M/sec], Expected Travel time of %4.2f hours\n", t, MAX_VEL_KPH, MAX_VEL_MPS, ((float)TRAVEL_TIME_SECS/SPH));
  printf("...\n");

  //time0=clock();
  clock_gettime(CLOCK_REALTIME, &t0);

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

  clock_gettime(CLOCK_REALTIME, &t1);
  //time1=clock();

  printf("Simulation time = %f microseconds\n", (float)deltat(&t0, &t1));
  //printf("Simulation time = %f microseconds\n", (float)((time1-time0)/CLOCKS_PER_SEC)*MICROSEC_PER_SEC);

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
