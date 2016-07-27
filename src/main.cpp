#include <Arduino.h>
#include <PIR.h>
#include <Ultrasonic.h>
#include <Functions.h>
#include <sdcard.h>

String bluetoothData = "";
bool sendOnce = true;
#define IsBluetoothConnected_Pin 31
float currentHeight = 0;
int PIRcounter = 0;
bool userIsHere = true;
bool BluetoothSend = false;

void setup()
{
        /* initialize LED digital pin as an output. */
        pinMode(LED_BUILTIN, OUTPUT);

        /* Serial to USB */
        Serial.begin(9600);
        while(!Serial) {; } /* Wait for Serial to begin */
        Serial.println("Serial port is Initialized");

        /* Bluetooth Serial */
        Serial1.begin(9600);
        while(!Serial1) {; } /* Wait for Bluetooth Serial to begin */
        Serial.println("Bluetooth Serial is Initialized");

        /* This Pin is to check if user is connected to BT    */
        pinMode(31, OUTPUT);
        /* Calibrates PIR sensor */
        // calibratePIR(); // Takes 5 seconds to calibrate.

        /* Initialize Pins for PIR */
        pinMode(PIRPIN, INPUT);
        digitalWrite(PIRPIN, LOW);

        pinMode(ECHOPIN, INPUT);
        pinMode(TRIGPIN, OUTPUT);

        pinMode(PINUP, OUTPUT);
        pinMode(PINDOWN, OUTPUT);

        digitalWrite(PINUP, HIGH);
        digitalWrite(PINDOWN, HIGH);

        /* Initialize the SD Card here. while loop makes sure it's initialized */
        while(!SD.begin(CS_Pin)) {
                Serial.println("SD card initialization failed! Trying again");
                delay(1000);
        };

        Serial.println("SD Card is Initialized.");

        /* TODO: Do all test with SD here */
        OpenFileAndWriteData("My Message Here", "Hello.txt");
}


void loop()
{
        /* TODO: Check if Bluetooth is connected. LED Pin in BT should be
           checked if it's HIGH. Only then, below code should be run. For simplicity,
           code runs even if there's not BT connection.
         */
        /* Note: Check how much time it takes to run isHumanThere function. */

        if(digitalRead(IsBluetoothConnected_Pin) == HIGH && userIsHere) {
                /* When the user connects, send the current height just once
                   Force this function to send height over Bluetooth */

                while(sendOnce == true) {
                        currentHeight = 0;
                        /* In case human is present, measure the distance and send it. */
                        while(currentHeight == 0) {
                                Serial.println("Trying to measure the height again..");
                                currentHeight = MeasureHeight();
                        }

                        /* Send the distance over Bluetooth */
                        Serial.println((int) currentHeight);
                        if(BluetoothSend == true) {
                                Serial1.println((int) currentHeight);
                        }
                        sendOnce = false;

                        /*  Here you should write to file using the user's ID.
                         * So up to this point, you have to make sure that user
                         * and MCU shared the userID.
                         * Writing to file should be done in every height change!
                         */

                }

                while(Serial1.available()) {

                        /* Receive the whole string then execute commands
                         * eg. moving Up, Down, whatsoever.. */

                        char recieved = Serial1.read();
                        bluetoothData += recieved;

                        /* Process message when new line character (#) is recieved
                         * # comes from Bluetooth configuration. It may bechanged to '\n'
                         * in the future */

                        if (recieved == '#') // # - End of String
                        {
                                Serial.println("Now performing action according to received data");
                                Serial.println(bluetoothData);
                                ExecuteBluetoothCommand(bluetoothData);
                                bluetoothData = ""; // Clear recieved buffer
                        }else if( bluetoothData.length() >= 40 ) {
                                bluetoothData += '#';
                                Serial.println("Appended newline character");
                                Serial.println(bluetoothData);
                                bluetoothData = "";
                        }else{}

                }

                /* FIXME: When user leaves the desk.
                 */
                if(isHumanThere()) {
                        Serial.println("I'm here");
                        delay(1000);
                        PIRcounter = 0;
                        userIsHere = true;
                }else{
                        PIRcounter++;
                        Serial.println(PIRcounter);
                        if(PIRcounter > 100) {
                                Serial.println("You've left your desk");
                                Serial.println(PIRcounter);
                                userIsHere = false;
                        }
                }



        } /* end of if Bluetooth connected*/
}/* end of loop */
