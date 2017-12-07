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
void Fitness(individual* set, int size, int colours[]);
int tabs(int x, int y);
int* BoolToInt(individual set);
individual* Crossover(individual* set, int size);
void Mutation(individual* set, int size);
individual* Substitute(individual* setPop, individual* setChil, int size);
bool canWeEnd(individual* set, int size);
void setColorOnSecond(int colour[]);
void Infusion(individual* set, int size);

#endif
