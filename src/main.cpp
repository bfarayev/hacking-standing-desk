#include <Arduino.h>
#include <SoftwareSerial.h>
#include <PIR.h>
#include <Ultrasonic.h>
#include <functions.h>
#include <string.h>

/* Digital Pin that's connected to LED in Bluetooth module */
#define IsBluetoothConnected_Pin 9
/* the time when the sensor outputs a low impulse */
String bluetoothData = "";
String customHeight = "";
/* Digital pin that PIR outpus is connected */
#define pinUp   6
#define pinDown 5

int ledPin = 8; // reserved for debugging purposes

/* Initialize software serial for Bluetooth (RX,TX) */
SoftwareSerial BL_Serial(10,11);
bool sendOnce = false;
int distance;
/* The amount of time the sensor has to be low
* before we assume all motion has stopped
*/

long unsigned int pause = 20000;

 int currentHeight = 0;

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

/* Not used at current codes.
*  Will be useful when you set the desk to custom heigth. */
void MoveTheDeskUp(int duration){
  /* Lifting the table up */
  Serial.println("Moving the desk up..");
  digitalWrite(pinUp, LOW);
  delay(abs(duration));
  /* Make this pin HIGH to stop the desk moving */
  digitalWrite(pinUp, HIGH);
  Serial.println("Command successfully executed");
}

void MoveTheDeskDown(int duration){
  /* Lifting the table up */
  Serial.println("Moving the desk down..");
  digitalWrite(pinDown, LOW);
  delay(abs(duration));
  /* Make this pin HIGH to stop the desk moving */
  Serial.println("Command successfully executed");
  digitalWrite(pinDown, HIGH);
}


void MoveTheDeskToCertainHeight(int desiredHeight){
  Serial.println("I'm in MoveTheDeskToCertainHeight function biacht");
  /* This function should take the custom height as an
  * argument and set desiredHeight as that. The rest of the code
  * will handle it. */
  // int desiredHeight = 100;
  int currentHeight = MeasureHeight();
  float diff = currentHeight - (float) desiredHeight;
  diff = abs(diff); // take absolute value, cuz diff can be negative.
  float movementDurationMillis = diff / 3; // divide to 3
  Serial.println("Movement Duration is:");
  Serial.println(movementDurationMillis);

  if(currentHeight > desiredHeight){
      MoveTheDeskDown(movementDurationMillis * 1000);
  }else{
      MoveTheDeskUp(movementDurationMillis * 1000);
  }
  return;
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
  calibratePIR(); // Takes 10 seconds to calibrate.

  /* Pins to control the desk */
  pinMode(pinUp, OUTPUT);
  pinMode(pinDown, OUTPUT);

  /* Initialize the PinUP & Down to HIGH
  * so that the desk won't be moving initially
  * Pulling PinUp and Down LOW moves the desk
  */

  digitalWrite(pinUp, HIGH);
  digitalWrite(pinDown, HIGH);

  /* Measure the distance once and send it to user
  * and send the distance over Bluetooth */
  // currentHeight = MeasureHeight();
  // BL_Serial.println(currentHeight);
  delay(3000);

  /* This is initial height measured and sent to the user phone */

  currentHeight = MeasureHeight();
  BL_Serial.println(currentHeight);
  Serial.println(currentHeight);

}

void ExecuteBluetoothCommand(String inputString){

  //if(inputString.indexOf("U") >=0)

  /* If char array contains U or u, then move it up. */
  // if(bl_input == 'U' || bl_input == 'u'){
  if(inputString.indexOf('U') >= 0){
    Serial.println("You sent \"UP\"command. So I'm lifting your desk");
    digitalWrite(pinUp, LOW);

    // while(HeightCheck()){
    //   HeightCheck();
    // }
    // MoveTheDeskUp(1000);
    
  }else if (inputString.indexOf('D') >= 0){
    Serial.println("You sent \"DOWN\"command. So I'm pushing down your desk");
    digitalWrite(pinDown, LOW);
  }else if(inputString.indexOf('S') >= 0){
    digitalWrite(pinDown, HIGH);
    digitalWrite(pinUp, HIGH);
    sendOnce = true;
  }else if(inputString.indexOf('C') >= 0){
    Serial.println("You want to set your desk to custom height! O'some! Let's do it biatch!");
    customHeight = inputString.substring(inputString.indexOf('C') + 1, inputString.length() -1);
    Serial.println("############");
    Serial.println(customHeight);
    Serial.println("############");
    MoveTheDeskToCertainHeight(customHeight.toInt());
  }
  else{
    /* Uncomment the below line for testing */
    // ardprintf("You entered: %s", bl_input);
  }

}

void HeightCheck(int distance){

      Serial.println("Inside the HeightCheck function. Current height is:");
      Serial.println(distance);

      if (digitalRead(pinDown) == LOW || digitalRead(pinUp) == LOW){
             // Set upper and lower boundaries
             if(distance > 105) {
               digitalWrite(pinUp, HIGH);
             }
             else if(distance < 75){
               digitalWrite(pinDown, HIGH);
             }
      }
}




void loop()
{

  /* Check if Bluetooth is connected */
  if(digitalRead(IsBluetoothConnected_Pin) == HIGH){
   /* Do the main things here:
    *  Send the height data over Bluetooth
    */

    // if (isHumanThere() && sendOnce == true)
     if (sendOnce == true) {
      /* In case human is present, measure the distance and send it. */
      distance = MeasureHeight();
      /* Send the distance over Bluetooth */
      BL_Serial.println(distance);
      sendOnce = false;
    }


     while(BL_Serial.available()){

      /* Receive the whole string and then decide
      * Then execute commands. Like moving Up, Down, whatsoever.. */

      char recieved = BL_Serial.read();

       bluetoothData += recieved;

      /* Uncomment below line to see every character received */
      //Serial.println(bluetoothData);

      /* Process message when new line character (#) is recieved
      * # comes from Bluetooth configuration. It may bechanged to '\n'
      * in the future */
       if (recieved == '#')
       {
         Serial.print("Arduino Received: ");
         Serial.print(bluetoothData);
         Serial.println("Now performing action according to received data");
         ExecuteBluetoothCommand(bluetoothData);
         bluetoothData = ""; // Clear recieved buffer
       }else if( bluetoothData.length() >= 20 ){
         bluetoothData += '#';
         Serial.println("Appended newline character");
         Serial.println(bluetoothData);
         bluetoothData = "";
       }else{}


     }

   // HeightCheck(distance);

   }

}
