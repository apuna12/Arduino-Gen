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

void Fitness(individual* set, int size)
{
  int maX = 0;
  int index = 0;
  int* temp;
  int colours[] = {255, 255, 0};
  for(int i=0; i<size; i++)
  {
    
    int* phenotype = BoolToInt(set[i]);
    set[i].fitness = double(1000)/(tabs(phenotype[0], colours[0]) + tabs(phenotype[1], colours[1]) + tabs(phenotype[2], colours[2]) + 1);

    free(phenotype);
  }
  for(int i=0;i<size;i++)
  {
    if(set[i].fitness>maX)
    {
      maX = set[i].fitness;
      index = i;
    }
    Serial.println(set[i].fitness,4);
  }
  temp = BoolToInt(set[index]);
//  setColorOnSecond(temp);
  //Serial.println(maX);
  //Serial.println(temp[1]);
  //Serial.println(temp[2]);
  free(temp);
 
}

int Selection(individual* set)
{
  int ranD = random(0,10);
  int ranD2 = random(0,10);

  if(set[ranD].fitness > set[ranD2].fitness)
  {
    return ranD;
  }
  else
  {
    return ranD2;
  }
}


individual* Crossover(individual* set, int size)
{
  individual* ret;
  int* parentGen = (int*)malloc(2*sizeof(int));
  for(int i=0;i<size;i++)
  {
    parentGen[0] = Selection(set);
    parentGen[1] = Selection(set);
    while(parentGen[0] == parentGen[1])
    {
      parentGen[1] = Selection(set);
      Serial.print("\n opakuje sa \n");
    }
    
    int ranD = random(1,23);
    for(int j=0;j<24;j++)
    {
      if(j<ranD)
      {
        ret[i].genotype[j] = set[parentGen[0]].genotype[j];
        //Serial.print("parentgen 0 je: ");
        //Serial.println(parentGen[0]);
      }
      else
      {
        ret[i].genotype[j] = set[parentGen[1]].genotype[j];
      }
    }
  }
  Serial.print("\n koniec crossoveru \n ");
  free(parentGen);
  return ret;
}


int* BoolToInt(individual set)
{
  int* ret = (int*)malloc(3*sizeof(int));
  int sum0 = 0;
  int sum1 = 0;
  int sum2 = 0;
  //bool test[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
  for(int m=0; m<24; m++)
  {
    if(m<8)
    {
      sum0 += (int)set.genotype[m] * 1<<m;
    }
    if(m>7 && m<16)
    {
      sum1 += (int)set.genotype[m]  * 1<<(m-8);
    }
    if(m>15 && m<24)
    {    
      sum2 += (int)set.genotype[m]  * 1<<(m-16);
    }
  }
  ret[0] = sum0;
  ret[1] = sum1;
  ret[2] = sum2;

  

  return ret;
}


int tabs(int x, int y)
{
  int ret = x - y;

  if(ret<0)
  {
    ret = -ret;
  }
  return ret;
}
