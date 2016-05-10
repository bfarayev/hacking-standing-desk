#include <sdcard.h>

File myFile;

// bool CreateNewTextFile(String userID){
//
//         /* TODO: Create a file userID.txt */
//
//         String filename = userID + ".txt";
//
//         // myFile = SD.open(filename, FILE_WRITE);
//
//         // /* TESTING: If file exists, start writing to it. */
//         // if(myFile) {
//         //         myFile.println("I'm a Random Sentence Passing by..");
//         //         myFile.close();
//         // }else {
//         //         Serial.println("Error opening file.");
//         // }
//
//         while (!SD.open(filename, FILE_WRITE)) {
//                 Serial.println("Couldn't create the file. Trying again..");
//                 delay(1000);
//         }
//
//         /* Return TRUE if such file exists */
//         return SD.exists(filename);
// }

void OpenFileAndWriteData(String data, String filename){
        /* REQUIRES: Make sure filename includes .txt in it*/

        /* Open the file with filename.txt and write data to it. */
        myFile = SD.open(filename, FILE_WRITE);

        /* If myFile exist, then write data to it */
        if(myFile) {
                Serial.println("Writing to file now..");
                myFile.println(data);
                myFile.close();

        }else{
                Serial.println("File doesn't exist");
                myFile = SD.open(filename, FILE_WRITE);
                /* Create a new file if it doesn't exist */
        }
}


void ReadFileAndSendToUser(String filename){
        /* TODO: Read File line by line and send it over Bluetooth (Serial1)*/

}
