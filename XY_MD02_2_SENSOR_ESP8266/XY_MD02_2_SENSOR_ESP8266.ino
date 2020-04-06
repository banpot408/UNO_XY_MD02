#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>

SoftwareSerial mySerial(D2, D3); // RX, TX

#define MAX485_TX_EN      D4


// instantiate ModbusMaster object
ModbusMaster node1;
ModbusMaster node2;

void preTransmission()
{
  digitalWrite(MAX485_TX_EN, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_TX_EN, 0);
}

void setup()
{
  pinMode(MAX485_TX_EN, OUTPUT);

  // Init in receive mode
  digitalWrite(MAX485_TX_EN, 0);

  Serial.println("start init serial 0");
  Serial.begin(9600);
  
  while (!Serial) {
    Serial.println("loop for init serial 0"); // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("start init software serial");
  mySerial.begin(9600);
  while (!mySerial) {
    Serial.println("loop for init software serial"); // wait for serial port to connect. Needed for Native USB only
  }
  
// Modbus slave ID 1
  node1.begin(5, mySerial);
  node2.begin(6, mySerial);

//   Callbacks allow us to configure the RS485 transceiver correctly
  node1.postTransmission(postTransmission);
  node2.preTransmission(preTransmission);

}

void loop()
{
  uint8_t result1; 
  uint8_t result2;

 // Serial.print("get data Sensor 1 : ");
  result1 = node1.readInputRegisters(1, 2); // Read 2 registers starting at 1)
  delay(200);
 // Serial.print("get data Sensor 2 : ");
  result2 = node2.readInputRegisters(1, 2); // Read 2 registers starting at 1)
  delay(200);

 
  if (result1 == node1.ku8MBSuccess)
  {
    Serial.print("get data Sensor 1 : ");
    Serial.print("Temp : ");
    Serial.print(node1.getResponseBuffer(0)/10.0f);
    Serial.print(" Humi : ");
    Serial.println(node1.getResponseBuffer(1)/10.0f);
  }

  if (result2 == node2.ku8MBSuccess)
  {
    Serial.print("get data Sensor 2 : ");
    Serial.print("Temp : ");
    Serial.print(node2.getResponseBuffer(0)/10.0f);
    Serial.print(" Humi : ");
    Serial.println(node2.getResponseBuffer(1)/10.0f);
  }

  Serial.println();
  Serial.println();
  delay(3000);
    
  
}
