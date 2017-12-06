
#include "genetic.h"

int redPin1 = 8;
int greenPin1 = 11;
int bluePin1 = 13;

int redPin2 = 6;
int greenPin2 = 5;
int bluePin2 = 3;

int _colours[] = {255, 255, 0};
int _nothing[] = {0, 0, 0};
individual* _actual;
bool tempGen[10][3];
bool tempFit[10];
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
  setColorOnFirst(_colours);
  setColorOnSecond(_nothing); 
  _actual = initialization(10);
  Fitness(_actual, 10, _colours);
  int k=0;
  
  while(canWeEnd(_actual, 10) == 0) 
  {
    k++;
    children = Crossover(_actual, 10);
    Mutation(children, 10);
    Fitness(children, 10, _colours);
    newGen = Substitute(_actual, children, 10);
    Fitness(newGen,10, _colours);
    _actual = newGen;
    free(children);
    free(newGen);
    Serial.print("\n Cyklus: ");
    Serial.print(k);
    Serial.print("\n");
  }

Serial.print("\n I HAVE IT :)");
  
}

void loop()
{
    
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
