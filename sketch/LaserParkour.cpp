#include <Arduino.h>
#include "LaserParkour.h"
void LaserParkour::test(/* args */)
{
    Serial.println("test");
}
void LaserParkour::setup(unsigned int diodesPinTmp, unsigned int startPinTmp, unsigned int stopPinTmp, unsigned int topListLengthTmp)
{
    diodesPin = diodesPinTmp;
    startPin = startPinTmp;
    stopPin = stopPinTmp;
    topListLength = topListLengthTmp;
    pinMode(startPin, INPUT_PULLUP); //define start pin as button-pin
    pinMode(stopPin, INPUT_PULLUP);//define stop pin as button-pin
}
void LaserParkour::setupInfo()
{
    Serial.println("\n////////////////////////////////\n//Laser-Parkour sketch        //\n//                            //\n//by Linus Prange             //\n//and Manuel König            //\n////////////////////////////////\n\n"); //print programm authors
    Serial.println("using photo-diode on pin " + String(diodesPin) + "\n"); //print used photo-diode pins
    Serial.println(String(startPin) + " is now the start-pin\n"); //print start pin
    Serial.println(String(stopPin) + " is now the stop-pin\n"); //print stop pin
    Serial.print("\n\n\n\n\n"); //print blank lines
}
void LaserParkour::shutdown()
{
    Serial.println("shuting down...");
    delay(100);
    exit(0);
}
void LaserParkour::sort(userdataFormat sortArr[])
{
    //this is a bubble-sort-algorithm
    //visit https://de.wikipedia.org/wiki/Bubblesort for more info
    for (unsigned int sortN = topListLength + 1; sortN > 1; --sortN) {
        for (unsigned int sortI = 0; sortI < sortN - 1; ++sortI) {
            if (sortArr[sortI].userdataTime > sortArr[sortI + 1].userdataTime) {
                userdataFormat sortTmp = sortArr[sortI];
                sortArr[sortI] = sortArr[sortI + 1];
                sortArr[sortI + 1] = sortTmp;
            }
        }
    }
    //return sortArr;
}
void LaserParkour::game(String name)
{
    //userdataFormat topList[] = {{4294967295, "A"},{4294967295, "B"},{4294967295, "C"},{213475, "Player"}};
    userdataFormat topList[topListLength+1];
    for (unsigned int i = 0; i < topListLength; i++)
    {
        topList[i] = {4294967295, "placeholder" + String(i)};
    }
    topList[topListLength].userdataName = name;
    topList[topListLength].userdataTime = 10;
    sort(topList);
    for(unsigned int i = 0; i < topListLength; i++)
    {
        if (topList[i].userdataTime != 4294967295)
        {
            Serial.println("Place " + String(i+1) + ": " + String(topList[i].userdataName) + " : " + String(topList[i].userdataTime));
        }
        //Serial.println("Place " + String(i+1) + ": " + String(topList[i].userdataName) + " : " + String(topList[i].userdataTime));
    }
}