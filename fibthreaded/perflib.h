#ifndef _PERFLIB_H_

#define _PERFLIB_H_

typedef unsigned int UINT32;
typedef unsigned long long int UINT64;

double readTOD(void);
double elapsedTOD(double stopTOD, double startTOD);
void printTOD(double stopTOD, double startTOD);

#endif
