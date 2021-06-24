/**
  ******************************************************************************
    文件名程: Sailboat_serial_Test.ino
    作    者: LXS
    版    本: V1.0
    编写日期: 2020-02-05
    功    能: 无人帆船 Arduino 硬件串口通讯测试实验
  ******************************************************************************
    说明：
    需配套自行设计的Arduino帆船控制板，USB转TTL模块使用。

    操作及现象：
    使用杜邦线通过硬件串口连接帆船控制板与USB转TTL模块；
    将USB转TTL模块接在电脑上，在电脑端打开串口调试助手工具，选择对应端口，设置参数为57600（根据蓝牙确定）
    下载程序之后，控制板LED点亮，在串口调试助手窗口可接收到相关信息；
    当输入信息"H"并发送，可在接收窗口接收到回传的信息"Copy That."。

  ******************************************************************************
*/

const byte LED = 17; //定义LED对应引脚
int incomedate = 0; // 定义串口接收变量

void setup() {
  pinMode(LED, OUTPUT);//点亮LED，表示程序运行正常

  Serial.begin(9600); //设置串口波特率9600bps
  // 波特率传输速率按照蓝牙模组设定，默认为9600
  Serial.println("Welcome to Arduino!");

  Serial.println(78, BIN);// "1001110"
  Serial.println(78, OCT);// "116"
  Serial.println(78, DEC);// "78"
  Serial.println(78, HEX);// "4E"
  Serial.println(1.23456, 0);// "1"
  Serial.println(1.23456, 2);// "1.23"
  Serial.println(1.23456, 4);// "1.2346"
  Serial.println('N');// "N"
  Serial.println("Hello world.");// "Hello world."

  delay(1000);
  while (Serial.read() >= 0) {} //清除可能存在的缓存clear serialbuffer
  Serial.println("Serial_OK.");// "OK."

}

void loop() {
  
  while (Serial.available() > 0)//Serial.available() 的意思是：返回串口缓冲区中当前剩余的字符个数。
//一般用这个函数来判断串口的缓冲区有无数据，当Serial.available()>0时，说明串口接收到了数据，可以读取；
  {
        char comdata = Serial.read();//获取串口接收到的数据
         if (comdata == 'H')
    {
      Serial.println("Copy That.");
    }
  }
         delay(1000);
}


/*** 接收和处理字符串（Serial.read()只能读取单个字符）
void loop(){
 
      while(Serial.available()){
 
           inputString=inputString+char(Serial.read());
 
           delay(2);
 
      }
 
      if(inputString.length()>0){
 
          Serial.println(inputString);
 
          inputString="";
 
     }
 
  ******************************************************************************
*/
