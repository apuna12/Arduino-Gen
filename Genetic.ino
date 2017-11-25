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
int newGen[10][3];
 
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
  Serial.begin(9600);
  setColorOnFirst(_colours);
  setColorOnSecond(_nothing);  
  //setColorOnSecond(_colours); 
 //initialization
  for(int i=0; i<10; i++)
  {

    for(int j=0; j<3; j++)
    {
      _actual[i][j] = random(0,256);
    }
    
  }
  // first Fitness
  Fitness(_actual);
  int k=0;
  while(canWeEnd(_fitness) == 0)//k<2
  {
    Selection(_actual);
    Crossover(parentGen);
    Mutation();
    Fitness(newGen);
    Substitute();

    /*setColorOnSecond(newGen[0]);
    delay(1000);
    setColorOnSecond(newGen[1]);
    delay(1000);
    setColorOnSecond(newGen[2]);
    delay(1000);
    setColorOnSecond(newGen[3]);
    delay(1000);
    setColorOnSecond(newGen[4]);
    delay(1000);
    setColorOnSecond(newGen[5]);
    delay(1000);
    setColorOnSecond(newGen[6]);
    delay(1000);
    setColorOnSecond(newGen[7]);
    delay(1000);
    setColorOnSecond(newGen[8]);
    delay(1000);
    setColorOnSecond(newGen[9]);
    delay(1000);
    setColorOnSecond(_nothing);
    delay(1000);*/

    /*setColorOnSecond(newGen[0]);

    setColorOnSecond(newGen[1]);
  
    setColorOnSecond(newGen[2]);
  
    setColorOnSecond(newGen[3]);
  
    setColorOnSecond(newGen[4]);
   
    setColorOnSecond(newGen[5]);
   
    setColorOnSecond(newGen[6]);
    
    setColorOnSecond(newGen[7]);
  
    setColorOnSecond(newGen[8]);
  
    setColorOnSecond(newGen[9]);
   
    setColorOnSecond(_nothing);*/
 
  }

  int besT = 0;
  for(int i=0;i<10;i++)
  {
    if(_fitness>besT)
    {
      besT = i;
    }
  }
  
  setColorOnSecond(newGen[besT]);
  Serial.println(newGen[besT][0]);
  Serial.println(newGen[besT][1]);
  Serial.println(newGen[besT][2]);
  
  
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
  int temp[10][3];
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<3;j++)
    {
      temp[i][j] = newGen[i][j];
    }
  }
  for(int i=0;i<5;i++)
  {
    ranD = random(10);
    for(int j=0;j<3;j++)
    {
      newGen[i][j] = temp[ranD][j];
    }
  }
  for(int i=5;i<10;i++)
  {
    ranD = random(10);
    for(int j=0;j<3;j++)
    {
      newGen[i][j] = _actual[ranD][j];
    }
  }
}

void Crossover(int parents[2][3])
{
  int ranDpart;
  int ranDparent;
  for(int i=0; i<10; i++)
  {
    for(int j=0; j<3; j++)
    {
      ranDpart = random(0,3);
      //Serial.print("ranDpart is: ");
      //Serial.println(ranDpart);
      ranDparent = random(0,2);
      //Serial.print("ranDparent is: ");
      //Serial.println(ranDparent);
      newGen[i][j] = parents[ranDparent][ranDpart];
    }
  }
}

void Mutation()
{
  int ranD;
  for(int i=0; i< 10;i++)
  {
    ranD = random(100);
    if(ranD >50)
    {
      for(int j=0; j<3; j++)
      {
        ranD = random(100);
        if(ranD > 35)
        {
          newGen[i][j] += 20;
        }
      }
    }
  }
}

int canWeEnd(int fitness[])
{
  for(int i=0; i<10; i++)
  {
    if(fitness[i] >= 150)
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
    if(set[i][0] > _colours[0]-20 && set[i][0] < _colours[0]+20)
    {
      _fitness[i] = _fitness[i] + 1;
    }
    if(set[i][1] > _colours[1]-20 && set[i][1] < _colours[1]+20)
    {
      _fitness[i] = _fitness[i] + 1;
    }
    if(set[i][2] > _colours[2]-20 && set[i][2] < _colours[2]+20)
    {
      _fitness[i] = _fitness[i] + 1;
    }
    if(set[i][0] == _colours[0])
    {
      _fitness[i] = _fitness[i] + 50;
    }
    if(set[i][1] == _colours[1])
    {
      _fitness[i] = _fitness[i] + 50;
    }
    if(set[i][2] == _colours[2])
    {
      _fitness[i] = _fitness[i] + 50;
    }
    Serial.println(_fitness[i]);
  }
}

void Selection (int prevGen[10][3])
{
  int ranD = random(0,10);
  int ranD2 = random(0,10);
  for(int i=0; i<3; i++)
  {
    parentGen[0][i] = prevGen[ranD][i];
  }
  for(int i=0; i<3; i++)
  {
    parentGen[1][i] = prevGen[ranD2][i];
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
