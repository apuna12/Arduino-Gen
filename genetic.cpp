#include "genetic.h"




individual* initialization(unsigned int size)
{

	if(size<2)
  {
    return NULL;
  }
  individual* p_population = malloc(size*sizeof(individual));
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<24; j++)
    {
      p_population[i].genotype[j] = random(0,2);
    }    
  }
	
	return p_population;
}
