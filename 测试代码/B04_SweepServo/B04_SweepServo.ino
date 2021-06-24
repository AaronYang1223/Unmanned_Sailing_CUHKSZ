/*
  ******************************************************************************
    文件名程: B04_SweepServo.ino
    作    者: Vicky
    版    本: V1.0
    编写日期: 2021-05-28
    功    能: 2个舵机转动测试
  ******************************************************************************
    说明：
    需配套自行设计的Arduino帆船控制板及舵机使用。

    操作及现象：
    将两个舵机分别按对应端口接到帆船控制板上；
    下载程序之后，控制板LED点亮，显示程序运行；
    舵机在0°和180°间不断转动。
    
  ******************************************************************************
*/

#include <Servo.h>

Servo myservo1;    // 舵机1
Servo myservo2;    // 舵机2

int pos_sail = 0;      //
int dir = 1;           //舵机方向

void move_myservo() {
  if (0 <= pos_sail && pos_sail <= 180) {
    myservo1.write(pos_sail);
    delay(10);
  }
}
void move_myservo2() {
  if (0 <= pos_sail && pos_sail <= 180) {
    myservo2.write(pos_sail);
    delay(10);
  }
}

void setup() {
  myservo1.attach(9);  // 定义舵机1驱动信号引脚位 9
  myservo2.attach(10);  // 定义舵机2驱动信号引脚位 10
}
void loop() {
  if (dir >= 0) {
    pos_sail += 10;
    if (  pos_sail >= 180) {
      pos_sail = 180;
      dir = -1;
    }
  }
  else {
    pos_sail -= 10;
    if (  pos_sail <= 0) {
      pos_sail = 0;
      dir = 1;
    }
  }
  move_myservo2();
  move_myservo();
    
  }      
