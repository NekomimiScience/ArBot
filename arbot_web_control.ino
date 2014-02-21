
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

//start server

YunServer server;

//setup the pins for PiBot board

const int uC_Killswitch_Status = 8;
const int uC_DC_Motor_Enable =  9;
const int Motor_A_1A = 10;
const int Motor_A_2A = 11;
const int Motor_B_1A = 12;
const int Motor_B_2A = 13;


void setup() {

  


  // initialize the pins as an output:
  pinMode(uC_DC_Motor_Enable, OUTPUT);
  pinMode(Motor_A_1A, OUTPUT);
  pinMode(Motor_A_2A, OUTPUT);
  pinMode(Motor_B_1A, OUTPUT);
  pinMode(Motor_B_2A, OUTPUT);
  pinMode(led, OUTPUT);

  // initialize the pin as an input:
  pinMode(uC_Killswitch_Status, INPUT);


//setup bridge and server stuff to enable HTTP control

  Bridge.begin();     
  server.listenOnLocalhost();
  server.begin();

}

void loop()

//what we're looking for is a URL coming in like this: "arduino.local/arduino/mode/1" from a client browser
//the following deals with that string and makes the motors turn

{

  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    process(client);
    client.stop();
  }

// delay polls every 20ms
  delay(20);
 
  }

//This function reads the URL up to the slash

void process(YunClient client) {
  String command = client.readStringUntil('/');
  
  //is the word mode before the slash (keyword to move bot)
  
  if (command == "mode") {
    //if it is, run the modeCommand function passing it the rest of what came in on the URL (client) 
    modeCommand(client);
  }
}

void modeCommand(YunClient client) {
  //mode is a variable that contains the number after the word mode (should change the name really to something like direction)
int mode;
//get the number after the slash and run the motor functions further down
mode = client.parseInt();
  
   if (mode == 1) {
    forward(); 
  }
  if (mode == 2) {
    left();
  }
  if (mode == 3) {
    right();
  }
  if (mode == 4) {
    stopmode();  
}   

  if (mode == 5) {
    reverse();
  }

}

//stop function

int stopmode() {
  digitalWrite(uC_DC_Motor_Enable, LOW);
  digitalWrite(Motor_A_1A, LOW);
  digitalWrite(Motor_A_2A, LOW);
  digitalWrite(Motor_B_1A, LOW);
  digitalWrite(Motor_B_2A, LOW);

}

//fwd function
int forward()
{


  digitalWrite(uC_DC_Motor_Enable, HIGH);
  digitalWrite(Motor_A_1A, HIGH);
  digitalWrite(Motor_A_2A, LOW);
  digitalWrite(Motor_B_1A, HIGH);
  digitalWrite(Motor_B_2A, LOW);

}
//right
int right()
{
   
  digitalWrite(uC_DC_Motor_Enable, HIGH);
  digitalWrite(Motor_A_1A, HIGH);
  digitalWrite(Motor_A_2A, LOW);
  digitalWrite(Motor_B_1A, LOW);
  digitalWrite(Motor_B_2A, HIGH); 
}
//left
int left()
{
  
  digitalWrite(uC_DC_Motor_Enable, HIGH);
  digitalWrite(Motor_A_1A, LOW);
  digitalWrite(Motor_A_2A, HIGH);
  digitalWrite(Motor_B_1A, HIGH);
  digitalWrite(Motor_B_2A, LOW); 
}
/reverse
int reverse()
{
 
  digitalWrite(uC_DC_Motor_Enable, HIGH);
  digitalWrite(Motor_A_1A, LOW);
  digitalWrite(Motor_A_2A, HIGH);
  digitalWrite(Motor_B_1A, LOW);
  digitalWrite(Motor_B_2A, HIGH); 
}


