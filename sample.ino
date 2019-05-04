
//int led = 13; // define the LED pin
int analogPin1 = A0;// KY-026 analog interface
int analogPin2 = A1;
int analogPin3 = A2;
int analogPin4 = A3;
int analogPin5 = A4;
int analogPin6 = A5;

const int trigPin = 51;
const int echoPin = 53;

// defining variables
long duration;
int distance;


//let's say you want to read up to 10 values
const int numReadings = 10;
int analogVals1[numReadings];
int analogVals2[numReadings];
int analogVals3[numReadings];
int analogVals4[numReadings];
int analogVals5[numReadings];
int analogVals6[numReadings];

int avg1 = 0;
int avg2 = 0;
int avg3 = 0;
int avg4 = 0;
int avg5 = 0;
int avg6 = 0;




// Motor A
 
int enA = 13;
int in1 = 12;
int in2 = 11;
 
// Motor B
 
int enB = 9;
int in3 = 7;
int in4 = 8;
 
void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //pinMode(led, OUTPUT);

  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  pinMode(analogPin3, INPUT);
  pinMode(analogPin4, INPUT);
  pinMode(analogPin5, INPUT);
  pinMode(analogPin6, INPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(4800);
 
}


void loop()
{
  //Serial.print("\n");
  Serial.print("\ntaking values ");
  for (int i=0; i<numReadings; i++)
  {
    analogVals1[i] = analogRead(A0);
    delay(10); //wait 0.1 sec
  }
  for (int i=0; i<numReadings; i++)
  {
    avg1 = avg1 + analogVals1[i];
  }
  avg1 = avg1 / 10 ;


  for (int i=0; i<numReadings; i++)
  {
    analogVals2[i] = analogRead(A1);
    delay(10); //wait 0.1 sec
  }
  for (int i=0; i<numReadings; i++)
  {
    avg2 = avg2 + analogVals2[i];
  }
  avg2 = avg2 / 10 ;


  for (int i=0; i<numReadings; i++)
  {
    analogVals3[i] = analogRead(A2);
    delay(10); //wait 0.1 sec
  }
  for (int i=0; i<numReadings; i++)
  {
    avg3 = avg3 + analogVals3[i];
  }
  avg3 = avg3 / 10 ;


  for (int i=0; i<numReadings; i++)
  {
    analogVals4[i] = analogRead(A3);
    delay(10); //wait 0.1 sec
  }
  for (int i=0; i<numReadings; i++)
  {
    avg4 = avg4 + analogVals4[i];
  }
  avg4 = avg4 / 10 ;


  for (int i=0; i<numReadings; i++)
  {
    analogVals5[i] = analogRead(A4);
    delay(10); //wait 0.1 sec
  }
  for (int i=0; i<numReadings; i++)
  {
    avg5 = avg5 + analogVals5[i];
  }
  avg5 = avg5 / 10 ;


  for (int i=0; i<numReadings; i++)
  {
    analogVals6[i] = analogRead(A5);
    delay(10); //wait 0.1 sec
  }
  for (int i=0; i<numReadings; i++)
  {
    avg6 = avg6 + analogVals6[i];
  }
  avg6 = avg6 / 10 ;

  int flame[6] = {avg1 , avg2 , avg3 , avg4 , avg5 , avg6};
  int min_value1 = 0;
  int min_value3 = 0;
  int min_value2 = 0;
  int min_ind1 = 10;
  int min_ind2 = 10;
  int min_ind3 = 10;

  Serial.print("\n printing averages");
  for(int i = 0 ; i < 6 ; i++)
  {
    Serial.print(flame[i]);
    Serial.print("_");
  }

  int counter = 0 ;
  for(int i = 0 ; i < 6 ; i++)
  {
    if(flame[i] > min_value1 )
    { 
      min_value1 = flame[i] ;
      min_ind3 = min_ind2 ;
      min_ind2 = min_ind1 ;
      min_ind1 = i ;  
    }
    else if(flame[i] > min_value2 )
    { 
      min_value2 = flame[i] ;
      min_ind3 = min_ind2 ;
      min_ind2 = i ;  
    }
    else if(flame[i] > min_value3 )
    { 
      min_value3 = flame[i] ;
      min_ind3 = i ;  
    }
  } 
  Serial.print(min_ind1);
  Serial.print("_");
  Serial.print(min_ind2);
  Serial.print("_");
  Serial.print(min_ind3);


  
 
  int min_ind = min_ind1;
  int Flag = 1 ;
  int Ref = 1 ;
  int count = 0;
  
  while(Ref)
  {
    int Flag = 1 ;
    Serial.print(min_ind);
    if(min_ind == 0 && Flag == 1 && count < 3)
    {
      if(foo())
      {
        Serial.print("obstacle detected\n");
        if(min_ind == min_ind1)
        {
          Serial.print("one to two");
          min_ind = min_ind2;
        }
        if(min_ind == min_ind2)
        {
          Serial.print("two to three");
          min_ind = min_ind3;
        }
        else if(min_ind == min_ind3)
        {
          Ref = 0;
        }
        Flag = 0;
      }
      else
  	  {
        Serial.print("Moving Forward\n");
        Forward1();
        Forward2();
        delay(1500);
        Stop();
        Ref = 0;
  	  }
      count++;
      
    }

    if(min_ind == 1 && Flag == 1 && count < 3)
    {
    	Serial.print("Turning left");
      //Forward1();
      Forward2();
      delay(1500);
      Stop();
      if(foo())
      {
        Serial.print("obstacle detected\n");
        if(min_ind == min_ind1)
        {
          min_ind = min_ind2;
        }
        else if(min_ind == min_ind2)
        {
          min_ind = min_ind3;
        }
        else if(min_ind == min_ind3)
        {
          Ref = 0;
        }
        Flag = 0;
      }
      else
      {
        Serial.print("Moving Forward");
        Forward1();
        Forward2();
        delay(1500);
        Stop();
        Ref = 0;
      }
      count++;
    }

    if(min_ind == 2 && Flag == 1 && count < 3)
    {
      Serial.print("Turning left");
      //Forward1();
      Forward2();
      delay(2750);
     Stop();
     if(foo())
     {
        Serial.print("obstacle detected\n");
        if(min_ind == min_ind1)
        {
          min_ind = min_ind2;
        }
        else if(min_ind == min_ind2)
        {
          min_ind = min_ind3;
        }
        else if(min_ind == min_ind3)
        {
          Ref = 0;
        }
        Flag = 0;
     }
      else
      {
        Serial.print("Moving Forward");
        Forward1();
        Forward2();
        delay(1500);
        Stop();
        Ref = 0;
      }
      count++;
    }

  if(min_ind == 3 && Flag == 1 && count < 3)
  {
    Serial.print("Turning left");
    //Forward1();
    Forward2();
    delay(3000);
    Stop();
    if(foo())
    {
      Serial.print("obstacle detected\n");
      if(min_ind == min_ind1)
      {
        min_ind = min_ind2;
      }
      else if(min_ind == min_ind2)
      {
        min_ind = min_ind3;
      }
      else if(min_ind == min_ind3)
        {
          Ref = 0;
        }
      Flag = 0;
    }
    else
    {
      Serial.print("Moving Forward");
      Forward1();
      Forward2();
      delay(1500);
      Stop();
      Ref = 0;
    }
    count++;
  }
  

  if(min_ind == 4 && Flag == 1 && count < 3)
  {
    Serial.print("Turning right");
    Forward1();
    //Forward2();
    delay(2500);
    Stop();
    if(foo())
    {
      Serial.print("obstacle detected\n");
      if(min_ind == min_ind1)
      {
        min_ind = min_ind2;
      }
      else if(min_ind == min_ind2)
      {
        min_ind = min_ind3;
      }
      else if(min_ind == min_ind3)
        {
          Ref = 0;
        }
      Flag = 0;
    }
    else
    {
      Serial.print("Moving Forward");
      Forward1();
      Forward2();
      delay(1500);
      Stop();
      Ref = 0;
    }
    count++;
  }

  if(min_ind == 5 && Flag == 1 && count < 3)
  {
    Serial.print("Turning right");
    Forward1();
    //Forward2();
    delay(1500);
    Stop();
    
    if(foo())
    {
      Serial.print("obstacle detected\n");
      if(min_ind == min_ind1)
      {
        min_ind = min_ind2;
      }
      else if(min_ind = min_ind2)
      {
        min_ind = min_ind3;
      }
      else if(min_ind == min_ind3)
        {
          Ref = 0;
        }
      Flag = 0;
    }
    else
    {
      Serial.print("Moving Forward");
      Forward1();
      Forward2();
      delay(1500);
      Stop();
      Ref = 0;
    }
    count++;
  }
  
  else
  {}
  }
  

  delay(1000);
}


void Forward1()
{
  // Turn on motor A
 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enA, 150);
}

void Forward2()
{
  // Turn on motor B
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enB, 150);
}

void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


int foo()
{

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

//delay(250);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
//delay(250);
distance= duration*0.034/2;
Serial.print(distance);

if(distance < 35)
{
  return 1;
}
return 0;
}
