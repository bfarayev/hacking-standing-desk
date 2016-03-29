/**
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "SoftwareSerial.h"

/* Initialize software serial for Bluetooth (RX,TX)
*  and PIR sensor (RX)
*/

SoftwareSerial BL_Serial(10,11);
SoftwareSerial PIR_Serial(5,6);

uint8_t bl_input = 0, pc_input = 0;

void togglePin(uint8_t LED,uint8_t delayDuration){
  /* Toggle LED every delayDuration second */
  digitalWrite(LED, HIGH);
  delay(delayDuration);
  digitalWrite(LED, LOW);
  delay(delayDuration);
  return;
}

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  BL_Serial.begin(9600);
  PIR_Serial.begin(9600);
}

/* Adding this function but not using it yet */
bool isHumanThere(){
  if(PIR_Serial.available()){
    return true;
  }else{
    return false;
  }
}


void loop()
{
  /* While something coming from USER over Bluetooth
  *  Control the motor
  */

  while(BL_Serial.available()){
    /* Test Line */
    Serial.println("Inside BL Serial");

    bl_input = BL_Serial.read();
    /* if user sends UP command */
    if(bl_input == 'U' || bl_input == 'u'){
      Serial.println("You sent \"UP\"command. So I'm lifting your desk");
      /* Serial.write(bl_input); */
    }else if (bl_input == 'D' || bl_input == 'd'){
      Serial.println("You sent \"DOWN\"command. So I'm pushing down your desk");
    }else{
      Serial.println("Please insert a correct character: \"U\" for UP, \"D\" for DOWN");
    }
      /*
      * if(bl_input == String(117) || bl_input == String(85)){
      *   This is the UP command
      *   Blink the LED for 5 times
      *   for(int i = 0; i <=4; i++){
      *     togglePin(LED_BUILTIN, 100);
      *   }
        }
      */
  }

  /* When PC_USER sends something, transmit it over
  * Serial Port to the MCU and then to Bluetooth
  */
  while(Serial.available()){
    Serial.println("Inside Serial.available");
    pc_input = Serial.read();
    BL_Serial.write(pc_input);
  }


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
