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

void Fitness(individual* set, int size,int colours[])
{
  int maX = 0;
  int index = 0;
  int* temp;
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
    Serial.println(set[index].fitness,4);
  }
  temp = BoolToInt(set[index]);
  setColorOnSecond(temp);
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

void Infusion(individual* set, int size)
{
  individual* temp = initialization(5);

  for(int i=5;i<size;i++)
  {
    for(int j=0;j<24;j++)
    {
      set[i].genotype[j] = temp[i-5].genotype[j];
    }
  }
  free(temp);
}

individual* Crossover(individual* set, int size)
{
  individual* ret = malloc(size*sizeof(individual));
  int parentGen[] = {0,0};
  for(int i=0;i<size;i++)
  {
    parentGen[0] = Selection(set);
    parentGen[1] = Selection(set);
    while(parentGen[0] == parentGen[1])
    {
      parentGen[1] = Selection(set);
      //Serial.print("\n opakuje sa \n");
    }
    
    int ranD = random(1,22);
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
  return ret;
}

void Mutation(individual* set, int size)
{
  int ranD;
  for(int i=0; i<size;i++)
  {      
    for(int j=0; j<24; j++)
    {
      ranD = random(100); 
      if(ranD >90)
      {
        set[i].genotype[j] = !set[i].genotype[j]; 
      }
    }
    
  }
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

individual* Substitute(individual* setPop, individual* setChil, int size)
{
  int randPop;
  int randChild;
  int bestChild = 0;
  int bestPop = 0;
  float maxChild = 0;
  float maxPop = 0;
  int indexPop = 0;
  int indexChild = 0;
  individual* ret = malloc(size*sizeof(individual));

  
  for(int i=0;i<size;i++)
  {
    if(setPop[i].fitness>maxPop)
    {
      maxPop = setPop[i].fitness;
      indexPop = i;
    }

    if(setChil[i].fitness>maxChild)
    {
      maxChild = setChil[i].fitness;
      indexChild = i;
    }
  }
  for(int i=0;i<24;i++)
  {
    if(maxPop>maxChild)
    {
      ret[0].genotype[i] = setPop[indexPop].genotype[i];
    }
    else
    {
      ret[0].genotype[i] = setChil[indexChild].genotype[i];
    }
  }
  
  for(int i=1;i<size;i++)
  {
    randPop = random(0,size);
    randChild = random(0,size);;
    for(int j=0; j<24; j++)
    {
      if(setPop[randPop].fitness>setChil[randChild].fitness)
      {
        ret[i].genotype[j] = setPop[i].genotype[j];
      }
      else
      {
        ret[i].genotype[j] = setChil[i].genotype[j];
      }
    } 
    
  }  
  return ret;
}

bool canWeEnd(individual* set, int size)
{
  for(int i=0; i<size; i++)
  {
    if(set[i].fitness == 1000)
    {
      return 1;
    }
  }
  return 0;
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


