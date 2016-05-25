#include "Arduino.h"
#include <Ultrasonic.h>

#define PINUP   43
#define PINDOWN 42
extern bool sendOnce;
extern float currentHeight;
extern bool BluetoothSend;

void ExecuteBluetoothCommand(String);
void HeightCheck(int);
void MoveTheDeskToCertainHeight(int);
void MoveTheDeskDown(int);
void MoveTheDeskUp(int);
