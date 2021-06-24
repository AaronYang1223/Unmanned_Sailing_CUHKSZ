/**
  ******************************************************************************
    文件名程: IMU_Nano.ino
    作    者: LXS
    版    本: V1.0
    编写日期: 2020-05-26
    功    能: 无人帆船实操视频3演示代码
  ******************************************************************************
    说明：
    配合Arduino_Nano板,IMU（ JY901）模块，杜邦线，5V电源使用。

    操作及现象：
    使用杜邦线通过IIC接口连接Arduino_Nano与IMU（ JY901）模块，打开串口调试助手工具，选择对应端口，串口波特率为9600；
    下载程序之后，IMU会通过串口向上位机发送相关数据；

  ******************************************************************************
*/

#include <Wire.h>  // Arduino官方库文件，使能IIC性能；
#include <JY901.h>// JY901库文件，处理IMU相关数据；

void setup() {
  // put your setup code here, to run once:-
  Serial.begin(9600);         //设置串口波特率为9600；
  JY901.StartIIC();           //通过IIC接口连接IMU；
}

void loop() {
  // put your main code here, to run repeatedly:

  JY901.GetTime(); //读取IMU时间数据
  /**相关数据计算方法及调用函数可查看库文件及芯片数据手册**/ 
  Serial.print("Time:20");
  Serial.print(JY901.stcTime.ucYear);//年
  Serial.print("年"); 
  Serial.print("-"); 
  Serial.print(JY901.stcTime.ucMonth); //月
  Serial.print("月"); 
  Serial.print("-"); 
  Serial.print(JY901.stcTime.ucDay);//日
  Serial.print("日"); 
  Serial.print(" "); 
  Serial.print(JY901.stcTime.ucHour);//时
  Serial.print(":"); 
  Serial.print(JY901.stcTime.ucMinute); //分
  Serial.print(":"); 
  Serial.println((float)JY901.stcTime.ucSecond + (float)JY901.stcTime.usMiliSecond / 1000);//秒

  JY901.GetAngle();   //读取IMU位姿数据
 //通过串口输出IMU数据
  Serial.print("Angle:"); 
  Serial.print("X:"); 
  Serial.print((float)JY901.stcAngle.Angle[0] / 32768 * 180); //X角
  Serial.print(" ");
  Serial.print("Y:"); 
  Serial.print((float)JY901.stcAngle.Angle[1] / 32768 * 180); //Y角
  Serial.print(" "); 
  Serial.print("Z:"); 
  Serial.println((float)JY901.stcAngle.Angle[2] / 32768 * 180);//Z角

  JY901.GetAcc(); //读取IMU加速度数据
  Serial.print("Acc:"); 
  Serial.print("X:"); 
  Serial.print((float)JY901.stcAcc.a[0] / 32768 * 16); //X角
  Serial.print(" "); 
  Serial.print("Y:"); 
  Serial.print((float)JY901.stcAcc.a[1] / 32768 * 16); //Y角
  Serial.print(" "); 
  Serial.print("Z:"); 
  Serial.println((float)JY901.stcAcc.a[2] / 32768 * 16);//Z角

  Serial.println("");
  delay(500);
}
