#include <Ultrasonic.h>

int MeasureDistance(){
  /* Measure it */
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance > 3000) {
    Serial.println ("error");
  }
  else{
     Serial.print(distance);
     Serial.println("cm");
  }
  delay(1000);

  return distance;
}
