
 
// Pin Assignments
int RED = 4;          //red LED Pin
int YLW = 5;          //yellow LED Pin
int GRN = 6;          //green LED Pin
int PBA = 7;          //pushbutton A
int PBB = 8;          //pushbutton B
    
int dimmerLED = 9;
int photo = 0;
int servoPin =2;
int angle;
int pulseWidth;
int vdata;
int prevdata=0;
int newvdata=0;
int photoLoc=0;
int token=0;

// Initialization routine runs once after Reset
void setup() 
{                
  // initialize led pins as outputs.
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(RED, OUTPUT);
  
  //initialize button pins as inputs
  pinMode(PBA, INPUT);
  pinMode(PBB, INPUT);
  
  //initialize serial printout
  Serial.begin(9600);
     Serial.println(" ");
  Serial.println("Program ready");
  
  //Servo reaches 180 Degrees initially
  for (angle=0; angle<=180;angle++)
  {
    servoPulse(servoPin, angle);
    delay(20);
  }
  
}

void servoPulse(int servoPin, int angle)
{
  pulseWidth = (angle*10) + 550;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
}


// Main Program Loop
void loop() {
  
  prevdata = 0;
  newvdata = 0;
  photoLoc = 0;
  
    //Green flashing
    do{
       digitalWrite(GRN, HIGH);
       delay(125);
       digitalWrite(GRN, LOW);
       delay(125);
      }
      
    while(digitalRead(PBA) == HIGH && token == 0);  
    
    //Yellow LED turns ON
    turnOnLED(YLW);  
    
    //Sweep Servo CW to 0 Deg
    for (angle=180; angle>=0;angle--)  
  {
    servoPulse(servoPin, angle);
    delay(20);
  }
  
  //Sweep Servo CCW to 180 Deg
  for (angle=0; angle<=180;angle++)
  { 
    servoPulse(servoPin, angle);
    delay(20);
    newvdata = analogRead(photo);
    
    if(newvdata>prevdata)
    {
      photoLoc = angle;
    prevdata = newvdata;
    }
    Serial.println(photoLoc);
  }
  
   for (angle=180; angle>=photoLoc;angle--)  
  {
    servoPulse(servoPin, angle);
    delay(20);
  }
    
    
    do{
       digitalWrite(RED, HIGH);
       delay(125);
       digitalWrite(RED, LOW);
       delay(125);
    }while(digitalRead(PBB) == HIGH);

    //To make sure the Green LED flashes only once when the program is started not when re-run
     token =1;
    
    }

//Turn on a single LED, and all other off
void turnOnLED(int COLOUR)
{
  digitalWrite(GRN, LOW);
  digitalWrite(YLW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(COLOUR, HIGH);
}

