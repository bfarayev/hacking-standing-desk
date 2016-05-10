#include <PIR.h>

void calibratePIR(){
        /* Calibrating Sensor for 5 seconds */
        int CALIBRATIONTIME = 5;

        Serial.print("Calibrating PIR Sensor. Please Wait.");
        for(int i = 0; i < CALIBRATIONTIME; i++) {
                Serial.print(".");
                delay(1000);
        }

        Serial.println("DONE. PIR Sensor: Active");
        delay(500);
}

bool isHumanThere(){
        int i = 0;
        bool motion = false;
        int maxIterationCycle = 10000;

        while(i < maxIterationCycle) {
                if(digitalRead(PIRPIN) == HIGH) {
                        motion = true;
                        break;
                }else{
                        i++;
                }
                motion = false;
        }

        /* (motion == true) ? : counter++; */

        return motion;
}
