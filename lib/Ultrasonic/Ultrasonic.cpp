#include <Ultrasonic.h>

int MeasureHeight(){
        /* Measure it */
        float duration = 0, distance = 0;
        float sum = 0;
        int validElements = 0;

        /* Do 6 measurements and take their average */
        int numberOfIterations = 6;

        for(int i = 0; i< numberOfIterations; i++) {
                digitalWrite(trigPin, LOW); // Added this line
                delayMicroseconds(2); // Added this line
                digitalWrite(trigPin, HIGH);
                delayMicroseconds(10); // Added this line
                digitalWrite(trigPin, LOW);
                duration = pulseIn(echoPin, HIGH);
                distance = (duration/2) / 29.1;

                /* This is a simple but not the best logic
                * to eliminate the invalid measurements */

                if (distance < 120 && distance > 40) {
                        //Serial.println ("invalid measurement");
                        sum += distance;
                        validElements += 1;
                }
                /* For debugging purposes */
                Serial.println (distance);
                // Serial.println(validElements);
        }

        /* Alternative solution for eliminating wrong measurements
         * But it still needs to be fixed. */
        // for(int k = 0; k <= 5; k+=2){
        //   if(abs(tmpHeight[k] - tmpHeight[k+1]) <= 2){
        //     // One of them is invalid
        //     sum+= tmpHeight[k];
        //     sum+= tmpHeight[k+1];
        //     validElements+=2;
        //   }
        // }

        /* Return the average height */
        // Serial.println(sum);
        // Serial.println(sum/validElements);
        return sum/validElements;
}
