int redPin1 = 8;
int greenPin1 = 11;
int bluePin1 = 13;

int redPin2 = 6;
int greenPin2 = 5;
int bluePin2 = 3;
int _colours[] = {255, 0, 255};
int _nothing[] = {0, 0, 0};
int _actual[10][3];
int _fitness[10];
int tempGen[10][3];
int tempFit[10];
int parentGen[2][3];
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT); 
  setColorOnFirst(_colours);
  setColorOnSecond(_nothing);  
 //initialization
  for(int i=0; i<10; i++)
  {

    for(int j=0; j<3; j++)
    {
      _actual[i][j] = random(0,255);
    }
    
  }
  // first Fitness
  Fitness(_actual);

  while(canWeEnd(_fitness) == 0)
  {
    Selection(_actual, _fitness);
    
    

    
    setColorOnSecond(parentGen[0]);
    delay(1000);
    setColorOnSecond(parentGen[1]);
    delay(1000);
  }

  

  
  
}
 
void loop()
{
  
 /* for(int i=0; i< 10; i++)
  {
    setColorOnFirst(_colours[i]);
    delay(1000);
  }*/
  
}

int canWeEnd(int fitness[])
{
  for(int i=0; i<10; i++)
  {
    if(fitness[i] == 3)
    {
      return 1;
      break;
    }
  }
  return 0;
}

void Fitness(int set[10][3])
{
  for(int i=0; i<10;i++)
  {
    if(set[i][0] == _colours[0])
    {
      _fitness[i] = _fitness[i] + 1;
    }
    if(set[i][1] == _colours[1])
    {
      _fitness[i] = _fitness[i] + 1;
    }
    if(set[i][2] == _colours[2])
    {
      _fitness[i] = _fitness[i] + 1;
    }
  }
}

void Selection (int prevGen[10][3], int fitness[])
{
  int best = 0;
  int customFitness[10];
  int customPrevGen[10][3];
  for(int i=0;i<10;i++)
  {
    customFitness[i] = fitness[i];
  }

  for(int k = 0; k<sizeof(prevGen); k++)
  {
    for(int l = 0; l<3; l++)
    {
      customPrevGen[k][l] = prevGen[k][l];
    }
  } 
  
  int j = 0;
  while(j<2)
  {
    best = 0;
    for(int i=0; i<10; i++)
    {
      if(customFitness[i] > best)
      {
       best = i;
      }
    }
    for(int i=0;i<3;i++)
    {
      parentGen[j][i] = prevGen[best][i];
    }
    removeFromArray(customFitness,best);
    memset(customFitness, 0, sizeof(customFitness));
    for(int k=0;k<3;k++)
    {
      customFitness[k] = tempFit[k];
    }
    removeFrom2DArray(customPrevGen,best);
    for(int k=0;k<3;k++)
    {
      memset(customPrevGen[k], 0, sizeof(customPrevGen[k]));
    } 
    for(int k = 0; k<sizeof(tempGen); k++)
    {
      for(int l = 0; l<3; l++)
      {
        customPrevGen[k][l] = tempGen[k][l];
      }
    }
    
    j++;
  }
  
}

void removeFromArray (int arraY[], int index)
{
  int returnArray[sizeof(arraY) - 1];
  int i=0;
  while(i<sizeof(arraY))
  {
    if(i == index)
    {
      i++;
      while(i<sizeof(arraY))
      {
        returnArray[i-1] = arraY[i];
        i++;
      }
      break;
    }
    else
    {
      returnArray[i] = arraY[i];
      i++;
    } 
  }
  for(int k=0;k<sizeof(returnArray);k++)
  {
    tempFit[k] = returnArray[k];
  }
}

int removeFrom2DArray (int arraY[10][3], int index)
{
  int returnArray[sizeof(arraY) - 1][3];
  for(int i=0; i<sizeof(arraY);i++)
  {
    if(i == index)
    {
      i++;
      while(i<sizeof(arraY))
      {
        for(int j=0; j<3; j++)
        {
          returnArray[i-1][j] = arraY[i][j];
        }
        i++;
      }
      break;
    }
    else
    {
        for(int j=0; j<3; j++)
        {
          returnArray[i][j] = arraY[i][j];
        }
    } 
  }
  for(int k = 0; k<sizeof(returnArray); k++)
  {
    for(int l = 0; l<3; l++)
    {
      tempGen[k][l] = returnArray[k][l];
    }
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
