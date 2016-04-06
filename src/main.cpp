#include <PIR.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

/* Digital Pin that's connected to LED in Bluetooth module */
#define IsBluetoothConnected_Pin 9

/* Digital pin that PIR outpus is connected */
#define pirPin  7
#define pinUp   5
#define pinDown 6

int ledPin = 8;
/* Initialize software serial for Bluetooth (RX,TX)
*  and PIR sensor (RX)
*/

SoftwareSerial BL_Serial(10,11);

/* the time when the sensor outputs a low impulse */
long unsigned int lowIn;

/* The amount of time the sensor has to be low
* before we assume all motion has stopped
*/
long unsigned int pause = 20000;

boolean lockLow = true;
boolean takeLowTime;

uint8_t bl_input = 0, pc_input = 0;

void togglePin(uint8_t LED,uint8_t delayDuration){
  /* Toggle LED every delayDuration second */
  digitalWrite(LED, HIGH);
  delay(delayDuration);
  digitalWrite(LED, LOW);
  delay(delayDuration);
  return;
}

void MoveTheDeskUp(int duration){
  /* Lifting the table up */
  Serial.println("Moving the desk up..");
  digitalWrite(pinDown, LOW);
  delay(duration);
  /* Make this pin HIGH to stop the desk moving */
  digitalWrite(pinDown, HIGH);
  Serial.println("Command successfully executed");
}

void MoveTheDeskDown(int duration){
  /* Lifting the table up */
  Serial.println("Moving the desk down..");
  digitalWrite(pinUp, LOW);
  delay(duration);
  /* Make this pin HIGH to stop the desk moving */
  Serial.println("Command successfully executed");
  digitalWrite(pinUp, HIGH);
}

void setup()
{
  /* initialize LED digital pin as an output. */
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  BL_Serial.begin(9600); /* Pins (Rx, Tx) -> (10,11) */

  Serial.println("Serial port is initialized..");
  delay(1000);
  Serial.println("Bluetooth Serial is active..");

  /* Initialize Pins for PIR and testign LED */
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  /* Calibrates PIR sensor */
  calibratePIR();

  /* Pins to control the dest */
  pinMode(pinUp, OUTPUT);
  pinMode(pinDown, OUTPUT);
  /* Initialize the PinUP & Down to HIGH
  * so that the desk won't be moving initially
  * Pulling PinUp and Down LOW moves the desk
  */
  digitalWrite(pinUp, HIGH);
  digitalWrite(pinDown, HIGH);
}



/* Adding this function but NOT using it yet */
bool isHumanThere(){
  if(digitalRead(pirPin) == HIGH){
    return true;
  }else{
    return false;
  }
}


void loop()
{
  /* Check if Bluetooth is connected */
  if(digitalRead(IsBluetoothConnected_Pin) == HIGH){
    /* Do the main things here:
    *  Send the height data over Bluetooth every 10 seconds
    */
      while(BL_Serial.available()){
      /* Test Line */
      // Serial.println("Inside Bluetooth control..");
      // Serial.println(BL_Serial.read());
      bl_input = BL_Serial.read();

      /* if user sends UP command
      *  move the desk
      */

      if(bl_input == 'U' || bl_input == 'u'){
        Serial.println("You sent \"UP\"command. So I'm lifting your desk");
        MoveTheDeskUp(1000);
      }else if (bl_input == 'D' || bl_input == 'd'){
        Serial.println("You sent \"DOWN\"command. So I'm pushing down your desk");
        MoveTheDeskDown(1000);
      }else{
        /* Uncomment the below line for testing*/
        //Serial.println("You entered:");
        //Serial.println(bl_input);

      }
    }
  }else{
    /* Wait for the user to connect..
    * You may notify the user that he/she's not connected to the desk */

  }


  // while(isHumanThere() == true){
  //   Serial.println("Human is there");
  //   digitalWrite(ledPin, HIGH);
  //   delay(1000);
  // }


  /*
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(1000);
  */
}
