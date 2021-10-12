#pragma once
class LaserParkour
{
private:
    /* data */
    //structs:
    struct userdataFormat { //Top 10 Format
        unsigned long userdataTime;
        String userdataName;
    };
    //vars:
    unsigned int diodesPin;
    unsigned int startPin; 
    unsigned int stopPin;
    unsigned int topListLength;
public:
    void test(/* args */);
    void setup(unsigned int diodesPinTmp, unsigned int startPinTmp, unsigned int stopPinTmp, unsigned int topListLengthTmp);
    void setupInfo();
    void shutdown();
    void sort(userdataFormat sortArr[]);
    void game(String name);
};