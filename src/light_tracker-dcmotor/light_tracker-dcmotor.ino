/*
 * Search for light with a DC Gear Motor
 * Developed by Hemant Kuruva (20077636)
 * 25 May 2018
 */

// Pin Assignments
int RED = 4;          //red LED Pin
int YLW = 5;          //yellow LED Pin
int GRN = 6;          //green LED Pin
int PBA = 7;          //pushbutton A
int PBB = 8;          //pushbutton B

int photo = 0;
int prevdata=0;
int newvdata=0;
int photoLoc=0;
int token=0;
int long i = 0;
int pot = 0;
int pwmspeed = 32;
int input1 = 3; 
int input2 = 9;

int Step = 0;
    
void setup() 
{                
  //Initializing button pins as inputs
  pinMode(PBA, INPUT);
  pinMode(PBB, INPUT);

  //Initializing LED pins
  pinMode(RED, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(GRN, OUTPUT);

  pinMode(1,INPUT); //Potentiometer
  
  pinMode(0,INPUT); //Photoresistor

  //Motor Terminals
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);

  //Serial Monitor
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("Program ready");
}

// Main Program 
void loop() {

  //Setting variables back to null
  prevdata = 0;
  newvdata = 0;
  photoLoc = 0;
  Step = 0;
  
  Serial.println("Press PBA to start");
  
  // Wait for PBA press (and flash Green while waiting)
  do{
       digitalWrite(GRN, HIGH);
       delay(125);
       digitalWrite(GRN, LOW);
       delay(125);
       
       pot = analogRead(1);
       pot = map(pot, 1024, 0, -255, 255);
       movePot(pot/2);
    }
    while(digitalRead(PBA) == HIGH && token == 0); 
   
    turnOnLED(YLW); //Yellow LED turned ON
    
    //Back to 0 degrees
    digitalWrite(input1,LOW); 
    analogWrite(input2,pwmspeed);
    delay(1350);
    
    digitalWrite(input1,LOW); 
    digitalWrite(input2,LOW); 
    delay(500);
 
    Step = 0;

    //Measuring the light intensity
    for (i=0; Step < 65; i++)
    { 
    digitalWrite(input1,HIGH);
    digitalWrite(input2,LOW);
    delay(3);
    Step++;
    digitalWrite(input1,LOW);
    digitalWrite(input2,LOW);
    delay(150);
      
    newvdata = analogRead(photo);
    
    if(newvdata>prevdata)
    {
      photoLoc = Step;
      prevdata = newvdata;
    }
    Serial.println(Step);
    Serial.println(photoLoc);
  }
  
    // Stop 
  digitalWrite(input1,LOW); 
  digitalWrite(input2,LOW);

  //Tracking
  for (i = 0; i<(Step-photoLoc); i++)
  {
    digitalWrite(input2,HIGH);
    digitalWrite(input1,LOW);
    delay(3);
    digitalWrite(input1,LOW);
    digitalWrite(input2,LOW);
    delay(150);
  }
  
  digitalWrite(input1,LOW); 
  digitalWrite(input2,LOW);

  //Yellow light blinking
  digitalWrite(YLW,LOW);

  //Red light flashing
  do
  {
    digitalWrite(RED, HIGH);
    delay(125);
    digitalWrite(RED, LOW);
    delay(125);
       
    pot = analogRead(1);
    pot = map(pot, 1024, 0, -255, 255);
    movePot(pot);
  } while(digitalRead(PBB) == HIGH);
  
  token =1;
  }

//Potentiometer subroutine//
void movePot(int pot)
{
  if (pot>0)
  {
     //Back 
  digitalWrite(input1,LOW); 
  analogWrite(input2,pot);
  }
  
  else if (pot<0)
  {
    //Forward 
  analogWrite(input1,-pot);
  digitalWrite(input2,LOW);
  }

else 
  {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  }
  return;
}

  //LED Turning ON subroutine
  void turnOnLED(int COLOUR)
{
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(COLOUR, HIGH);
}
