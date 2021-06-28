// This is a test file which implements 
// the function that a servo rotates follows 
// the rotation of the imu

#include <PID_v1.h>
#include <JY901.h>
#include <Wire.h>
#include <Servo.h>

double Setpoint, Input, Output;
double Kp = 2, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

Servo myServo1, myServo2;
int pos = 0;

void setup() {
    Serial.begin(9600);
    myServo1.attach(9);
    myServo2.attach(10);
    JY901.StartIIC();
    JY901.GetAngle();
    Input = (float) JY901.stcAngle.Angle[0] / 32768 * 180;
    Setpoint = 0;
    myPID.SetMode(AUTOMATIC);
}

void loop() {
    JY901.GetAngle();
    Input = (float) JY901.stcAngle.Angle[0] / 32768 * 180;
    myPID.Compute();
    Serial.print("Input: ");
    Serial.print(Input);
    Serial.print("Output: ");
    Serial.print(Output);
    myServo1.write(Output);
    myServo2.write(Output);
}
