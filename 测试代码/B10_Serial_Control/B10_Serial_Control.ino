/**
  ******************************************************************************
   
    打开串口监视器，选择对应端口，设置参数为57600（根据程序确定）
    运行程序之后，在串口监视器可接收到相关信息"OK_Setup" ， "OK_Loop"；
    
    通过串口输入信息并发送，LED亮，
    发送r，舵机1向右旋转10度，并在接收窗口接收到回传的角度信息，达到0度后停止；
    发送l，舵机1向左旋转10度，并在接收窗口接收到回传的角度信息，达到180度后停止；
    发送m，舵机1回中，并在接收窗口接收到回传的角度信息，达到90度后停止；
    发送j，舵机2向右旋转10度，并在接收窗口接收到回传的角度信息，达到0度后停止；
    发送s，舵机2向左旋转10度，并在接收窗口接收到回传的角度信息，达到180度后停止；
    发送p，舵机2回中，并在接收窗口接收到回传的角度信息，达到90度后停止；
    串口每次收到数据处理完成，灯灭

  ******************************************************************************
*/

  #include <Servo.h>
      Servo myservo1;     //    舵机1
      Servo myservo2;     //    舵机2
      
      int pos1  = 90;    //舵机1
      int pos2  = 90;    //舵机2角度
      
      int ledPin = 13;

  void setup() {
      Serial.begin(9600);
      Serial.println("OK_Setup");
    
      myservo1.attach(9);
      myservo2.attach(10);
    
      myservo1.write(pos1);
      myservo2.write(pos2);
    }

  void loop() {
  
    if (Serial.available()) {
      analogWrite(ledPin, 0);              // 模拟值 0 灯亮，255 灯灭 这个引脚也可以用来做  呼吸灯实验
      char servodir = Serial.read();
      Serial.println("OK_Loop");
     /********************舵机1****************************/
      if (servodir == 'r')                  //右打舵
      {
        pos1 = pos1 - 10;
        if (pos1 < 0) pos1 = 0;
        myservo1.write(pos1);              // 舵机1到达位置 pos1 
        Serial.println("OK_R_rudder");
        Serial.println(pos1);
        Serial.println();
        delay(10);
      }
      
      else if (servodir == 'l')            //左打舵
      {
        pos1 = pos1 + 10;
        if (pos1  > 180) pos1 = 180;
        myservo1.write(pos1);               
        Serial.println("OK_L_rudder");
        Serial.println(pos1);
        Serial.println();
        delay(10);
      }
      else if (servodir == 'm')           //舵打平
      {
        pos1 = 90;
        myservo1.write(pos1);
        Serial.println("OK_M_rudder");
        Serial.println(pos1);
        Serial.println();
  
        delay(10);
      }
      /********************舵机2****************************/
      else if (servodir == 'j')           //紧帆
      {
        pos2 = pos2 + 10;
        if (pos2 > 180) pos2 = 180;  //180
        myservo2.write(pos2);           
        Serial.println("OK_J_sail");
        Serial.println(pos2);
        Serial.println();
         delay(10);
      }
  
      else if (servodir == 's')           //松帆
      {
        pos2 = pos2 - 10;
        if (pos2 < 0) pos2 = 0;
        myservo2.write(pos2);           
  
        Serial.println("OK_S_sail");
        Serial.println(pos2);
        Serial.println();
         delay(10);
      }
  
      else if (servodir == 'p')           //帆打平
      {
        pos2 = 90;
        myservo2.write(pos2);
        Serial.println("OK_P_sail");
        Serial.println(pos2);
        Serial.println();
  
        delay(10);
      }
    }
    analogWrite(ledPin, 255);             //  接收灯 255  每次收到数据处理完成，灯灭。
  }



