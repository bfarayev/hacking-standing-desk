#include <Ultrasonic.h>



float MeasureHeight(){
        /* Takes 1 second to execute*/
        float duration = 0, height = 0;

        /* Upper and Lower Bounds for Desk Height
           Using this, we filter invalid measurements */

        int UPPERBOUND = 125;
        int LOWERBOUND = 60;

        int numberOfIterations = 10;

        /* Create empty float array for measurements */
        float tmpMeasurements[numberOfIterations];
        int size = 0;

        for(int i = 0; i< numberOfIterations; i++) {
                digitalWrite(TRIGPIN, LOW);
                delayMicroseconds(2);
                digitalWrite(TRIGPIN, HIGH);
                delayMicroseconds(5);
                digitalWrite(TRIGPIN, LOW);

                duration = pulseIn(ECHOPIN, HIGH);

                /* Convert to cm */
                height = duration / 58.138;

                /* This is a simple logic
                   to eliminate the invalid measurements */


                if (height < UPPERBOUND && height > LOWERBOUND) {
                        /* For debugging purposes */
                        // Serial.println ("Valid measurement");
                        // Serial.println (height);
                        tmpMeasurements[size] = height;
                        size += 1;
                }

                /* Put small delay between iterations */
                delay(100);
        }


        /* Return the average height*/
        if(size != 0) {
                return SortArrayAndReturnMedian(tmpMeasurements, size);
        }else{
                Serial.println("Something unexpectedly went wrong. Make sure you're not blocking the sensors.");
                return 0;
        }
}


float SortArrayAndReturnMedian(float Array[], int len){
        /* Get measurements with valid elements and size. Sort them and take median. */

        /* Buble sort */
        for(int i=0; i<(len-1); i++) {
                for(int j=0; j<(len-(i+1)); j++) {
                        if(Array[j] > Array[j+1]) {
                                float t = Array[j];
                                Array[j] = Array[j+1];
                                Array[j+1] = t;
                        }
                }
        } // End of Bubble Sort

        /* For Debugging purposes*/
        for(int i = 0; i<=len-1; i++) {
                Serial.println(Array[i]);
        }

        /* Take element in the middle. Check the diff b/w prev and next element of array/
              If the diff is < 2 cm then return median. Otherwise return 0 */

        int DIFF = 2; // 2 cm

        if(len < 3) {
                return 0;
        }else{
                /* Take the diff between prev and next elems */

                if (Array[(len)/2] - Array[(len)/2 - 1] < DIFF && Array[(len)/2 + 1] - Array[(len)/2] < DIFF) {
                        Serial.println("Height is: ");
                        Serial.println(Array[(len)/2]);
                        return Array[len/2];
                }else{
                        Serial.println("Something unexpectedly went wrong. Make sure you're not blocking the sensors.");
                        return 0;
                }
        }

}
