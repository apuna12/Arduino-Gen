int redPin1 = 8;
int greenPin1 = 11;
int bluePin1 = 13;

int redPin2 = 6;
int greenPin2 = 5;
int bluePin2 = 3;
int _colours[] = {255, 0, 255};
int _nothing[] = {0, 0, 0};
bool** _actual = (bool**)malloc(10*sizeof(bool*));
float _fitness[10];
bool tempGen[10][3];
bool tempFit[10];
int* parentGen = (int*)malloc(2*sizeof(int));;
bool** newGen = (bool**)malloc(10*sizeof(bool*));
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
void setup()
{
  setColorOnFirst(_colours);
  randomSeed(analogRead(0));
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);
  Serial.begin(9600);
  
  setColorOnSecond(_nothing);  
  
 //initialization
  for(int i=0; i<10; i++)
  {
    _actual[i] = (bool*)malloc(24*sizeof(bool));
    for(int j=0; j<24; j++)
    {
      _actual[i][j] = random(0,2);
    }    
  }
  
  // first Fitness
  Fitness(_actual);
  //Serial.print("ide");
  int k=0;
  while(canWeEnd(_fitness) == 0)
  {
    k++;
    newGen = Crossover();
    /*for(int i=0;i<10;i++)
    {
      Serial.println(_fitness[i]);
    }*/
    Mutation();
    //Serial.print("Mutation done");
    Fitness(newGen);
    //Serial.print("Fitness done");
    Substitute();
    //Serial.print("Substitution done");
    
    //Serial.println(k);
    //delay(500);
  }
  /*for(int i=0;i<10;i++)
  {
    Serial.println(_fitness[i]);
  }*/
  
}
 
void loop()
{
  
 /* for(int i=0; i< 10; i++)
  {
    setColorOnFirst(_colours[i]);
    delay(1000);
  }*/
  
}

void Substitute()
{
  int ranD;
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<24;j++)
    {
      _actual[i][j] = newGen[i][j];
    }
  }
  for(int i=0; i<10; i++)
  {
    free(newGen[i]);
  }
  free(newGen);


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
    ranD = random(100); 
    for(int j=0; j<24; j++)
    {
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

void Fitness(bool** set)
{
  int maX = 0;
  int index = 0;
  int* temp;
  /*for(int i=0;i<10;i++)
  {
    for(int j=0;j<24;j++)
    {
      Serial.print(set[i][j]);
    }
    Serial.print("\n ");
  }*/
  for(int i=0; i<10; i++)
  {
    
    int* phenotype = BoolToInt(set[i]);
    //Serial.println(phenotype[0]);
    //Serial.println(phenotype[1]);
    //Serial.println(phenotype[2]);
    Serial.print("\n phenotyp je: ");
    _fitness[i] = 1000/((phenotype[0] - _colours[0])*(phenotype[0] - _colours[0]) + (phenotype[1] - _colours[1])*(phenotype[1] - _colours[1]) + (phenotype[2] - _colours[2])*(phenotype[2] - _colours[2]) + 1);
    //Serial.println(phenotype[1]);
    //Serial.println(phenotype[0] - _colours[0]);
    //Serial.println(phenotype[1] - _colours[1]);
    //Serial.println(phenotype[2] - _colours[2]);
    //Serial.println(_fitness[i]);

    free(phenotype);
  }
  for(int i=0;i<10;i++)
  {
    temp = BoolToInt(set[i]);
    if(_fitness[i]>maX)
    {
      maX = _fitness[i];
      index = i;
    }
    //Serial.println(_fitness[i]);
  }
  setColorOnSecond(temp[index]);
  //Serial.println(maX);
  //Serial.println(temp[1]);
  //Serial.println(temp[2]);
  free(temp);  
}

int* BoolToInt(bool* set)
{
  int* ret = (int)malloc(3*sizeof(int));
  int sum0 = 0;
  int sum1 = 0;
  int sum2 = 0;
  //bool test[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1};
  for(int m=0; m<24; m++)
  {
    if(m<8)
    {
      sum0 += (int)set[m] * (pow(2,m));
    }
    if(m>7 && m<16)
    {
      sum1 += (int)set[m] * (pow(2,(m-8)));
    }
    if(m>15 && m<24)
    {
      sum2 += (int)set[m] * (pow(2,(m-16)));
    }
    //Serial.println(set[m]);
  }
  ret[0] = sum0;
  ret[1] = sum1;
  ret[2] = sum2;
  //Serial.println(ret[0]);
  //Serial.println(ret[1]);
  //Serial.println(ret[2]);
  

  return ret;
}

int Selection ()
{
  int ranD = random(0,10);
  int ranD2 = random(0,10);
  /*Serial.print("\n ranD je ");
  Serial.println(ranD);
  Serial.print("\n ranD2 je ");
  Serial.println(ranD2);
  */
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
}
