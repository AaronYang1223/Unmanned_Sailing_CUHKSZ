/**
  ******************************************************************************
    文件名程: B05_Demo_for_PID_function.ino
    作    者: Vicky
    版    本: V1.0
    编写日期: 2021-06-03
    功    能: 无人帆船 Arduino PID 公式验证
  ******************************************************************************
    说明：
    需配套自行设计的Arduino帆船控制板,蓝牙模块，USB转TTL模块，IMU（ JY901）模块，舵机使用。

    操作及现象：
    分别使用杜邦线通过串口连接帆船控制板与蓝牙模块，通过IIC接口连接帆船控制板与IMU（ JY901）模块；
    通过PWM端口连接舵机，连接USB转TTL模块与蓝牙模块；  舵机1(9)，舵机2(10)，
    将USB转TTL模块与蓝牙模块接在电脑上；打开串口调试助手工具，选择对应端口，设置参数为57600（根据蓝牙确定）
    下载程序之后，在串口调试助手窗口可接收到相关信息"OK1_Setup"；

  
    输入信息"S"并发送，对舵机1的角度进行手动控制；输入相应的角度数值，按非数值键结束；
    输入信息"R"并发送，对舵机2的角度进行手动控制，输入相应的角度数值，按非数值键结束；
    输入信息"D"并发送，输入相应的目标值，按非数值键结束，设定目标角度；
    输入信息"M"并发送，进行模式切换，可输入0，1，2，3，9，四种模式；
    模式9为断开舵机与控制板连接，模式0为恢复舵机连接；
    选择模式2，对舵机1进行自动控制；
    选择模式1，对舵机1进行自动控制；
  ******************************************************************************
*/
int comInt;  //用处？
#include <Servo.h>
#include <PID_v1.h>
#include <JY901.h>//IMU

long time,lasttime;      //Define Variables we'll be connecting to
double Setpoint, Input, Output,ini_Input;//设置pid的参数，ihni_Iput  20+360
double error_lasttime,error1,error2,error3;
int Ms=2000;              //间隔100响应一次

//设置两种PID参数，Define the aggressive and conservative Tuning Parameters
double consKp=1, consKi=0, consKd=0.25;//设置缓慢转弯pid三个参数double consKp=1, consKi=0.05, consKd=0.25;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);//Specify the links and initial tuning parameters


//初始化
void setup()
{
   Serial.begin(9600);
   Serial.println("Welcome to Arduino!");
  JY901.StartIIC();  //IMU数据读取
  while(Serial.read()>= 0){}//清除可能存在的缓存clear serialbuffer  
  lasttime=millis();//读取当下时间
  Setpoint = 60; 
  myPID.SetMode(AUTOMATIC);         //打开PID
  myPID.SetOutputLimits(-255, 255);//限制舵机转动角度
}

void loop()
{
  time=millis();//现在时间(ms)
  if(time-lasttime>=Ms){//ms执行一次
    char command=Serial.read();        //从串口读取数据

    JY901.GetAngle();//读取IMU的数据
    Input = (float)JY901.stcAngle.Angle[2]/32768*180;     // 当前角度To garentee the boat to turn correctly in the following two situation
    
    error1 = Setpoint - Input;
    error2 += error1;
    error3 = error1 - error_lasttime;
    
    myPID.Compute();//the output value will be rewrite here
    lasttime=time;
    error_lasttime = error1; 
    Serial.println(Input); Serial.println(error1); Serial.println(error2);
    Serial.println(error3); 
    Serial.println(Output);
     Serial.println(" ");
  
  }
}

