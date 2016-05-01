#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <string.h>

#define CS_Pin 4

bool CreateNewTextFile(String userID);
