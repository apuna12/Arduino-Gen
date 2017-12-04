
#include "genetic.h"

int redPin1 = 8;
int greenPin1 = 11;
int bluePin1 = 13;

int redPin2 = 6;
int greenPin2 = 5;
int bluePin2 = 3;

int _colours[] = {255, 255, 0};
int _nothing[] = {0, 0, 0};
//bool** _actual = (bool**)malloc(10*sizeof(bool*));
individual* _actual;
float* _fitness;
bool tempGen[10][3];
bool tempFit[10];
//int* parentGen = (int*)malloc(2*sizeof(int));
//bool** newGen;
individual* children;
individual* newGen;

 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
void setup()
{
  //setColorOnFirst(_colours);
  randomSeed(analogRead(0));
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);
  Serial.begin(9600);
  
  //setColorOnSecond(_nothing); 
   
 //initialization
 /* for(int i=0; i<10; i++)
  {
    _actual[i] = (bool*)malloc(24*sizeof(bool));
    for(int j=0; j<24; j++)
    {
      _actual[i][j] = random(0,2);
    }    
  }*/

  _actual = initialization(10);
  Fitness(_actual, 10);
  int a=0;
  int b=0;
 // a = Selection(_actual);
  //b = Selection(_actual);
  //Serial.print("selekcia \n");
  Serial.println(a);
  Serial.println(b);
  children = Crossover(_actual, 10);

  
  
  /*for(int i=0; i<10; i++)
  {
    //a = Selection(_actual);
    for(int j=0; j<24; j++)
    {
      //newGen[i].genotype[j] = _actual[a].genotype[j];
      Serial.print(_actual[i].genotype[j]);
      Serial.print(children[i].genotype[j]);
      Serial.print("\n ");
    }    
    Serial.print("\n ");
  }*/
  
}
  
 /* 
  // first Fitness
  _fitness = Fitness(_actual);
  //Serial.print("ide");
  int k=0;
  while(canWeEnd(_fitness) == 0) 
  {
    k++;
    newGen = Crossover();
    
    free(_fitness);
    Mutation();
    //_fitness = Fitness(newGen);
    //Serial.print("Mutation done");
    //Serial.print("Fitness done");
    bool** _old = _actual;
    _actual = Substitute();
    _fitness = Fitness(_actual);

    //Serial.print("Substitution done");

    for(int i=0; i<10; i++)
    {
      free(newGen[i]);
      free(_old[i]);
    }
    free(newGen);
    free(_old);

    
    Serial.print("\n Cyklus: ");
    Serial.print(k);
    Serial.print("\n");

  
    //delay(500);
  }

Serial.print("\n I HAVE IT :)");
  
}
 */
void loop()
{
    
}
/*
bool** Substitute()
{
  int randPop;
  int randChild;
  float* fitnessPop = Fitness(_actual);
  float* fitnessChild = Fitness(newGen);
  int bestChild = 0;
  int bestPop = 0;
  float maxChild = 0;
  float maxPop = 0;
  int indexPop = 0;
  int indexChild = 0;
  bool** ret = (bool**)malloc(10*sizeof(bool*));

  
  for(int i=0;i<10;i++)
  {
    if(fitnessPop[i]>maxPop)
    {
      maxPop = fitnessPop[i];
      indexPop = i;
    }

    if(fitnessChild[i]>maxChild)
    {
      maxChild = fitnessChild[i];
      indexChild = i;
    }
  }
  ret[0] = (bool*)malloc(24*sizeof(bool));
  for(int i=0;i<24;i++)
  {
    if(maxPop>maxChild)
    {
      ret[0][i] = _actual[indexPop][i];
    }
    else
    {
      ret[0][i] = newGen[indexChild][i];
    }
  }
  
  for(int i=1;i<10;i++)
  {
    randPop = random(0,10);
    randChild = random(0,10);
    ret[i] = (bool*)malloc(24*sizeof(bool));
    for(int j=0; j<24; j++)
    {
      if(fitnessPop[randPop]>fitnessChild[randChild])
      {
        ret[i][j] = _actual[i][j];
      }
      else
      {
        ret[i][j] = newGen[i][j];
      }
    } 
    
  }
  free(fitnessPop);
  free(fitnessChild);   
  return ret;
}

bool** Crossover()
{
  bool** ret = (bool**)malloc(10*sizeof(bool*));
  
  for(int i=0;i<10;i++)
  {
    ret[i] = (bool*)malloc(24*sizeof(bool));
    parentGen[0] = Selection();
    parentGen[1] = Selection();
    while(parentGen[0] == parentGen[1])
    {
      parentGen[1] = Selection();
      //Serial.print("\n opakuje sa");
    }
    int ranD = random(1,23);
    for(int j=0;j<24;j++)
    {
      if(j<ranD)
      {
        ret[i][j] = _actual[parentGen[0]][j];
        //Serial.print("parentgen 0 je: ");
        //Serial.println(parentGen[0]);
      }
      else
      {
        ret[i][j] = _actual[parentGen[1]][j];
      }
    }
  }
  //Serial.print("\n koniec crossoveru \n ");
  return ret;
}

void Mutation()
{
  int ranD;
  for(int i=0; i< 10;i++)
  {      
    for(int j=0; j<24; j++)
    {
      ranD = random(100); 
      if(ranD >90)
      {
        newGen[i][j] = !newGen[i][j]; 
      }
    }
    
  }
}

bool canWeEnd(float fitness[])
{
  for(int i=0; i<10; i++)
  {
    if(fitness[i] == 1000)
    {
      return 1;
    }
  }
  return 0;
}

float* Fitness(bool** set)
{
  int maX = 0;
  int index = 0;
  float* fitness = (float*)malloc(10*sizeof(float));
  int* temp;

  for(int i=0; i<10; i++)
  {
    
    int* phenotype = BoolToInt(set[i]);
    fitness[i] = double(1000)/(tabs(phenotype[0], _colours[0]) + tabs(phenotype[1], _colours[1]) + tabs(phenotype[2], _colours[2]) + 1);
    //Serial.println(phenotype[1]);
    //Serial.println(phenotype[0] - _colours[0]);
    //Serial.println(phenotype[1] - _colours[1]);
    //Serial.println(phenotype[2] - _colours[2]);
    //Serial.println(_fitness[i]);

    free(phenotype);
  }
  for(int i=0;i<10;i++)
  {
    if(fitness[i]>maX)
    {
      maX = fitness[i];
      index = i;
    }
    Serial.println(fitness[i],4);
  }
  temp = BoolToInt(set[index]);
  setColorOnSecond(temp);
  //Serial.println(maX);
  //Serial.println(temp[1]);
  //Serial.println(temp[2]);
  free(temp);

  return fitness; 
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

int* BoolToInt(bool* set)
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
      sum0 += (int)set[m] * 1<<m;
    }
    if(m>7 && m<16)
    {
      sum1 += (int)set[m] * 1<<(m-8);
    }
    if(m>15 && m<24)
    {    
      sum2 += (int)set[m] * 1<<(m-16);
    }
    //Serial.println(set[m]);
    //Serial.print("\n novy prikaz: ");
    //Serial.print(1 << m);
  }
  ret[0] = sum0;
  ret[1] = sum1;
  ret[2] = sum2;

  

  return ret;
}

int Selection ()
{
  int ranD = random(0,10);
  int ranD2 = random(0,10);

  if(_fitness[ranD] > _fitness[ranD2])
  {
    return ranD;
  }
  else
  {
    return ranD2;
  }
}

 
void setColorOnFirst(int colour[])
{
  #ifdef COMMON_ANODE
   
   int red = 255 - colour[0];
   int green = 255 - colour[1];
   int blue = 255 - colour[2];
  #endif
  analogWrite(redPin1, red);
  analogWrite(greenPin1, green);
  analogWrite(bluePin1, blue);   
}

void setColorOnSecond(int colour[])
{
  #ifdef COMMON_ANODE
   
   int red = 255 - colour[0];
   int green = 255 - colour[1];
   int blue = 255 - colour[2];
  #endif
  analogWrite(redPin2, red);
  analogWrite(greenPin2, green);
  analogWrite(bluePin2, blue);  
}*/
