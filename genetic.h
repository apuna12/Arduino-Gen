#ifndef genetic_h
#define genetic_h
#include <Arduino.h>

typedef struct individual
{
  bool genotype[24];
  double fitness;
}individual;

individual* initialization(unsigned int size);
int Selection(individual* set);
void Fitness(individual* set, int size);
int tabs(int x, int y);
int* BoolToInt(individual set);
individual* Crossover(individual* set, int size);

#endif
