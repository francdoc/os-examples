float integrator(float t, float dt, float (*funcptr)(float))
{
  // simple forward integrator
  return ( ((*funcptr)(t)) * dt);
}
