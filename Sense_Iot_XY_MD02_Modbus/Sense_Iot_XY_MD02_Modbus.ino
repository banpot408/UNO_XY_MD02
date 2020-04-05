
#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>

#define MAX485_TX_EN_CH1      22
#define MAX485_TX_EN_CH2      23

ModbusMaster node1;
ModbusMaster node2;

EthernetClient client;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define SENSES_HOST "www.sensesiot.com"
#define SENSES_PORT 4000
#define retry_wait 1000
#define LAGTIME 100

IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);

unsigned int count_temp = 0;
unsigned int count_humi = 100;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void preTransmission1()
{
  digitalWrite(MAX485_TX_EN_CH1, 1);
}

void postTransmission1()
{
  digitalWrite(MAX485_TX_EN_CH1, 0);
}

void preTransmission2()
{
  digitalWrite(MAX485_TX_EN_CH2, 1);
}

void postTransmission2()
{
  digitalWrite(MAX485_TX_EN_CH2, 0);
}

String Senses_Sent_Data(int slotnum, float data) {
  String _response = "";
  
  if (client.connect(SENSES_HOST, SENSES_PORT)) {
    String _path = "";
    _path = "GET /send/";
    _path += String(374);
    _path += "/";
    _path += String("trpgy7c4d10c");
    _path += "/";
    _path += String(slotnum);
    _path += "/";
    _path += String(data);

    _path += " HTTP/1.1\r\n";
    _path += "Host: ";
    _path += SENSES_HOST;
    _path += ":";
    _path += SENSES_PORT;
    _path += "\r\n";
    _path += "Connection: keep-alive\r\n\r\n";

    client.print(_path);
    delay(LAGTIME);
    
    while (client.available()) {
      String _response = client.readStringUntil('\r');
    }
    return _response;
  }
}

void setup() {
  pinMode(MAX485_TX_EN_CH1, OUTPUT);
  pinMode(MAX485_TX_EN_CH2, OUTPUT);
  digitalWrite(MAX485_TX_EN_CH1, 0);
  digitalWrite(MAX485_TX_EN_CH2, 0);  
  pinMode(53, OUTPUT);

  node1.begin(5, Serial1);
  node2.begin(6, Serial2);

  node1.preTransmission(preTransmission1);
  node1.postTransmission(postTransmission1);
  
  node2.preTransmission(preTransmission2);
  node2.postTransmission(postTransmission2);
  
  Ethernet.init(53);   // MKR ETH shield

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial1.begin(9600);
  while (!Serial1) {
    ;
  }
  Serial2.begin(9600);
  while (!Serial2) {
    ;
  }
  
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting ");
  Serial.println("...");

//  Senses_Sent_Data(1, count_temp);
//  Senses_Sent_Data(2, count_humi);
}
  
void loop() {
  uint8_t result1;
  uint16_t data1[2];

  uint8_t result2;
  uint16_t data2[2];

  uint16_t temp1 = 0 ;
  uint16_t humi1 = 0 ;

  uint16_t temp2 = 0 ;
  uint16_t humi2 = 0 ;
  


  result1 = node1.readInputRegisters(0x01, 2);
  delay(500);

  result2 = node2.readInputRegisters(0x01, 2);
  delay(500);
   
  if (result1 == node1.ku8MBSuccess)
  {
    temp1 = node1.getResponseBuffer(0x00);
    humi1 = node1.getResponseBuffer(0x01);
    Serial.print("Temp 1 : ");    
    Serial.println(temp1);
    Serial.print("Humi 1 : ");    
    Serial.println(humi1);
  }
  if (result2 == node2.ku8MBSuccess)
  {
    temp2 = node2.getResponseBuffer(0x00);
    humi2 = node2.getResponseBuffer(0x01);
    Serial.print("Temp 2 : ");    
    Serial.println(temp2);
    Serial.print("Humi 2 : ");    
    Serial.println(humi2);
  }

  Senses_Sent_Data(1, temp1);
  Senses_Sent_Data(2, humi1);
  Senses_Sent_Data(3, temp2);
  Senses_Sent_Data(4, humi2);

  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();
  }

  delay(1000);
}
