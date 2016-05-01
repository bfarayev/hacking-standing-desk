#include <sdcard.h>

File myFile;

bool CreateNewTextFile(String userID){
        String filename = userID + ".txt";
        myFile = SD.open(filename, FILE_WRITE);
        myFile.close();
        if (SD.exists("example.txt")) {
                return true;
        }
        else{
                return false;
        }
}
