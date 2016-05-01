#include <PIR.h>

int counter = 0;
/* Calibration time for PIR */
static int calibrationTime = 5;

void calibratePIR(){
        /* Calibrating Sensor for 10 seconds */
        Serial.print("calibrating sensor ");
        for(int i = 0; i < calibrationTime; i++) {
                Serial.print(".");
                delay(1000);
        }

        Serial.println("done");
        Serial.println("PIR Sensor: Active");
        delay(500);
}


bool isHumanThere(){
        int i = 0;
        bool motion = false;

        while(i < 5000) {

                if(digitalRead(pirPin) == HIGH) {
                        motion = true;
                        counter = 0;
                        break;
                }else{
                        i++;
                }
                motion = false;
        }

        (motion == true) ? : counter++;

        return motion;
}

/*
   void loop(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         delay(50);
         }
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){
           //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
   }
 */
