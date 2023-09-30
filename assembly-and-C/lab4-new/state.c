#include "imu.h"

// State profiles
float a_profile[MAX_TRAVEL_TIME_ALLOWED];
float v_profile[MAX_TRAVEL_TIME_ALLOWED];
float p_profile[MAX_TRAVEL_TIME_ALLOWED];
float t_profile[MAX_TRAVEL_TIME_ALLOWED];
int sample=0;

float pos_f(float time)
{
  int idx=(int)(time-0.1);

  if(idx < 0) idx=0;

  //printf("p=%f idx=%d\n", p_profile[idx], idx);  
  return p_profile[idx];
}

float vel_f(float time)
{
  int idx=(int)(time-0.1);

  if(idx < 0) idx=0;

  //printf("v=%f idx=%d\n", v_profile[idx], idx);  
  return v_profile[idx];
}

void update_profile(float t, float a, float v, float p)
{
  t_profile[sample]=t;
  a_profile[sample]=a;
  v_profile[sample]=v;
  p_profile[sample]=p;
  sample++;

  //printf("+++ sample=%d, t=%f, a=%f, v=%f, p=%f, dt=%f\n", sample, t, a, v, p);
}

void zero_profiles(void)
{
  bzero(t_profile, sizeof(float)*(MAX_TRAVEL_TIME_ALLOWED));
  bzero(a_profile, sizeof(float)*(MAX_TRAVEL_TIME_ALLOWED));
  bzero(v_profile, sizeof(float)*(MAX_TRAVEL_TIME_ALLOWED));
  bzero(p_profile, sizeof(float)*(MAX_TRAVEL_TIME_ALLOWED));
}


void dump_profile(void)
{
  int i;

  printf("\n\n#, t, a, v, pos\n");
  for(i=0; i<sample; i++)
  {
    printf("%d, %f, %f, %f, %f\n", i, t_profile[i], a_profile[i], v_profile[i], p_profile[i]);
  }
}
