
#include <Stepper.h>
#define STEPS 100

Stepper stepper(STEPS, 10, 11, 12, 13);

//Variables declaration
int motStep = 0;    //Variable for storing the iterative step variable
int dimmerLED = 9;  //PIN number of White LED
int photo = 0;      //PIN number of photoresistor
int prevdata=0;     //Stores previous photoresistor data
int newvdata=0;     //Stores present photoresistor data
int photoLoc=0;     //Stores the step number of the photoresistor location
int token=0;        //Token to ensure that Green LED flashes only for the first run


// Pin Assignments
int RED = 4;          //Red LED Pin
int YLW = 5;          //Yellow LED Pin
int GRN = 6;          //Green LED Pin
int PBA = 7;          //Pushbutton A
int PBB = 8;          //Pushbutton B
    
// Initialization routine runs once after Reset
void setup() 
{                
  //Initialize buttons and LEDs as inputs and outputs
  pinMode(PBA, INPUT);
  pinMode(PBB, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(GRN, OUTPUT);
  
  //Initialize serial printout
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("Program ready");
  stepper.setSpeed(25);
}

// Main Program 
void loop() {

  //Initializing the variables back to 0
  prevdata = 0;
  newvdata = 0;
  photoLoc = 0;
  
  Serial.println("Press PBA to start");

  // Wait for PBA press (and flash Green while waiting)
  do{
     digitalWrite(GRN, HIGH);
     delay(125);
     digitalWrite(GRN, LOW);
     delay(125);
    }
    while(digitalRead(PBA) == HIGH && token == 0);  

  //Yellow LED turns ON, all other LEDs turned OFF
  turnOnLED(YLW);
      
  //Stepper rotates to 0 Deg.
  stepper.step(50);

  //Scanning for light source
  for (motStep=0; motStep<=50;motStep++)
  { 
    stepper.step(-1);
    newvdata = analogRead(photo);
    
    if(newvdata>prevdata)
    {
      photoLoc = motStep;
    prevdata = newvdata;
    }
    Serial.println(photoLoc);
  }

  //Rotating in the direction of Light source
  stepper.step(50-photoLoc);
  digitalWrite(YLW,LOW);

  //Red LED flashes
  do
  {
    digitalWrite(RED, HIGH);
       delay(125);
       digitalWrite(RED, LOW);
       delay(125);
  } while(digitalRead(PBB) == HIGH);

  //Rotating back to 9 o'clock position
  stepper.step(-(50-photoLoc));

  //Token to ensure that Green LED flashes only for the first run
  token =1;
   
  }  
  
  void turnOnLED(int COLOUR)
{
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(COLOUR, HIGH);
}
