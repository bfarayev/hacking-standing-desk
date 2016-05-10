#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <string.h>

#define CS_Pin 53 /* SS pin is 53 for Mega */

// bool CreateNewTextFile(String);
void OpenFileAndWriteData(String, String);
void ReadFileAndSendToUser(String);
