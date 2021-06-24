/**
  ******************************************************************************
    文件名程: LED_Nano.ino
    作    者: LXS
    版    本: V1.0
    编写日期: 2020-05-26
    功    能: 无人帆船实操视频1演示代码 
  ******************************************************************************
    说明：
    配合Arduino_Nano板,杜邦线，5V电源使用。

    操作及现象：
    使用杜邦线通过数字端口配置LED；
    下载程序之后，led 以500ms频率闪烁2次 ，灭2秒，依此循环
  ******************************************************************************
*/


int LedPin = 13;  // 引脚定义;  led 连接到 13引脚(此行可省略，系统默认板载led 为 pin 13)

void setup() {
  // put your setup code here, to run once:
  
  pinMode(LedPin,OUTPUT);   // 初始化数字端口为输出模式
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LedPin, HIGH);   // led引脚置高电平
  delay(500);               // 延时500ms
  digitalWrite(LedPin, LOW);    // led引脚变为低电平
  delay(500);               // 延时500ms
   digitalWrite(LedPin, HIGH);   // led引脚置高电平
  delay(500);               // 延时500ms
  digitalWrite(LedPin, LOW);    // led引脚变为低电平
  delay(2000);               // 延时2000ms
}
