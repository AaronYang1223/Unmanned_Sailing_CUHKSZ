/**
  ******************************************************************************
    文件名程: B21_PID_Manual_Control_with_Mocap.ino
    作    者: Vicky, Aaron
    版    本: V1.0
    编写日期: 2021-07-1
    功    能: 无人帆船 Arduino PID 控制舵机（配合上位机）
  ******************************************************************************
    说明：
    需配套自行设计的Arduino帆船控制板,蓝牙模块，USB转TTL模块，舵机，Motion Capture使用。

    操作及现象：
    分别使用杜邦线通过串口连接帆船控制板与蓝牙模块；
    通过PWM端口连接舵机，连接USB转TTL模块与蓝牙模块；  舵机1(9)_控制舵，舵机2(10)_控制帆，
    将USB转TTL模块与蓝牙模块接在电脑上；打开串口调试助手工具，选择对应端口，设置参数为57600（根据蓝牙确定）
    下载程序之后，在串口调试助手窗口可接收到相关信息"Get Start!"；

    指令格式：aaabbb(Input + Setpoint, 单位：角度，type: int)
  ******************************************************************************
*/

#include <Servo.h>
#include <PID_v1.h>

Servo myservo1;
Servo myservo2;

//angle
int pos_myservo1 = 90;
int pos_myservo2 = 90;

//control servo1, IMPROVE
const int max_myservo1 = 150;
const int min_myservo1 = 30;
const int mid_myservo1 = 85;
const int range_myservol = 80; 

//control servo2, IMPROVE
const int down_myservo2 = 80; //顺风；
const int up_myservo2 = 90;  //逆风；

double Setpoint, Input, Output; //设置pid的参数
char buffer[6];
char angle[] = "000";
char angle_[] = "000";

//Define the aggressive and conservative Tuning Parameters
double consKp=1, consKi=0, consKd=0; //设置缓慢转弯pid三个参数double consKp=1, consKi=0.05, consKd=0.25;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT); //Specify the links and initial tuning parameters

//protect servo1
void move_myservo1() 
{
  if (pos_myservo1 <= min_myservo1)
  {
    pos_myservo1 = min_myservo1;
  }
  else if (pos_myservo1 >= max_myservo1)
  {
    pos_myservo1 = max_myservo1;
  }
  myservo1.write(pos_myservo1);
}

//optimize the path(360 - 0)
void change_input(double &Input, double &Setpoint)
{
  if(Input - Setpoint > 225){
    Input -= 360;
  }else if(Setpoint - Input > 180){
    Input += 360;
  }
}

//get angle
void get_angle(char* buffer, double &Input, double &Setpoint){
  for(int i = 0 ; i < 3 ; i++)
  {
    angle[i] = buffer[i];  
  }
  Input = atoi(angle);     

  for(int i = 3 ; i < 6 ; i++)
  {
    angle[i-3] = buffer[i];  
  }
  Setpoint = atoi(angle);
}

//set sail
void set_sail(double Setpoint, int &pos_myservo2){
  if (30 <= Setpoint && Setpoint <= 150) 
  {
    pos_myservo2 = up_myservo2;
  }
  else if (240 <= Setpoint && Setpoint <= 300) 
  {
    pos_myservo2 = down_myservo2;
  }
  myservo2.write(pos_myservo2);
}

//initialize
void setup()
{
  Serial.begin(9600);
  Serial.println("Get Start!");
  myservo1.attach(9); //the servo control used PWM
  myservo2.attach(10); //the servo control used PWM
  while(Serial.read()>= 0){} //清除可能存在的缓存clear serial buffer  
  Setpoint = 90; 
  myPID.SetMode(AUTOMATIC); //打开PID
  myPID.SetOutputLimits(-255, 255); //限制舵机转动角度
}

void loop()
{
  if (Serial.available()) {      //蓝牙收到消息  
    delay(20);

    Serial.readBytes(buffer,6);
    Serial.println("Instr:"); 
    Serial.println(buffer);

    get_angle(buffer, Input, Setpoint);
    
    set_sail(Setpoint, pos_myservo2);

    myPID.Compute();//the output value will be rewrite here

    Serial.print("Setpoint:");
    Serial.println(Setpoint); 
    Serial.print("Boat Angle:");
    Serial.println(Input);    
    Serial.print("Output:"); 
    Serial.println(Output); 
    pos_myservo1 = mid_myservo1 + range_myservol * Output/255;
    Serial.print("Sail:"); 
    Serial.println(pos_myservo1); 
    move_myservo1();
    Serial.println("Done"); 
    delay(20);
  }
}

