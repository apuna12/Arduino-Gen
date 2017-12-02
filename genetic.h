#ifndef genetic_h
#define genetic_h
#include <Arduino.h>

typedef struct individual
{
  bool genotype[24];
  double fitness;
}individual;

individual* initialization(unsigned int size);



#endif
