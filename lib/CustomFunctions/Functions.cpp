#include "Functions.h"

void ExecuteBluetoothCommand(String inputString){
        String customHeight = "";

        if(inputString.indexOf('U') == 0) {
                Serial.println("You sent \"UP\"command. So I'm lifting your desk");
                digitalWrite(PINUP, LOW);
                BluetoothSend = true;
        }else if (inputString.indexOf('D') == 0) {
                Serial.println("You sent \"DOWN\"command. So I'm pushing down your desk");
                digitalWrite(PINDOWN, LOW);
        }else if(inputString.indexOf('S') == 0) {
                digitalWrite(PINDOWN, HIGH);
                digitalWrite(PINUP, HIGH);
                sendOnce = true;
                currentHeight = 0;
                BluetoothSend = true;
        }else if(inputString.indexOf('C') == 0) {
                Serial.println("You want to set your desk to custom height! O'some! Let's do it biatch!");
                customHeight = inputString.substring(inputString.indexOf('C')+1, inputString.indexOf('#'));
                Serial.println("############");
                Serial.println(customHeight);
                Serial.println("############");
                MoveTheDeskToCertainHeight(customHeight.toInt());
                BluetoothSend = true;   // Send that data to Bluetooth
        }
        else{
                /* Uncomment the below line for testing */
                // ardprintf("You entered: %s", bl_input);
        }

}

void HeightCheck(int distance){

        Serial.println("Inside the HeightCheck function. Current height is:");
        Serial.println(distance);

        if (digitalRead(PINDOWN) == LOW || digitalRead(PINUP) == LOW) {
                // Set upper and lower boundaries
                if(distance > 105) {
                        digitalWrite(PINUP, HIGH);
                }
                else if(distance < 75) {
                        digitalWrite(PINDOWN, HIGH);
                }
        }
}

void MoveTheDeskToCertainHeight(int desiredHeight){
        Serial.println("I'm in MoveTheDeskToCertainHeight function");
        /* This function should take the custom height as an
         * argument and set desiredHeight as that. The rest of the code
         * will handle it. */
        // int desiredHeight = 100;
        int currentHeight = MeasureHeight();
        float diff = currentHeight - (float) desiredHeight;
        diff = abs(diff); // take absolute value, cuz diff can be negative.
        float movementDurationMillis = diff / 3.85; // divide to 3
        Serial.println("Movement Duration is:");
        Serial.println(movementDurationMillis);

        if(currentHeight > desiredHeight) {
                MoveTheDeskDown(movementDurationMillis * 1000);
        }else{
                MoveTheDeskUp(movementDurationMillis * 1000);
        }

        sendOnce = true; /* This is the control variable. Setting it true
                            makes user receive updated height on screen */
        return;
}

void MoveTheDeskDown(int duration){
        /* Lifting the table up */
        Serial.println("Moving the desk down..");
        digitalWrite(PINDOWN, LOW);
        delay(abs(duration));
        /* Make this pin HIGH to stop the desk moving */
        Serial.println("Command successfully executed");
        digitalWrite(PINDOWN, HIGH);
}

void MoveTheDeskUp(int duration){
        /* Lifting the table up */
        Serial.println("Moving the desk up..");
        digitalWrite(PINUP, LOW);
        delay(abs(duration));
        /* Make this pin HIGH to stop the desk moving */
        digitalWrite(PINUP, HIGH);
        Serial.println("Command successfully executed");
}
