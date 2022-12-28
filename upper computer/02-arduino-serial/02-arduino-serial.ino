#include <Wire.h>

char rData[4];
char* tData = NULL;

const char* DATA_1 = "Hello, Arduino world!";
const char* DATA_2 = "Nice to meet you.";
const char* DATA_3 = "Happy geeking and coding.";

void setup() {
    Serial.begin(9600);
    while(Serial.read() >= 0) {}
}

void loop() {
    if (Serial.available()) {
        Serial.readBytes(rData, 4);
        Serial.println("I received: ");
        Serial.println(rData);
        tData = serialListener(rData);
        Serial.println(tData);
    }
}

const char* serialListener(const char received[]) {
    if (received == "0001") 
        return DATA_1;
    else if (received == "0002")
        return DATA_2;
    else if (received == "0003")
        return DATA_3;
    else 
        return "Wrong command.";
}
