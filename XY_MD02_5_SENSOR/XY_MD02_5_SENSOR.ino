#include <SoftwareSerial.h>
#include <ModbusMaster.h>

SoftwareSerial mySerial(2, 3); // RX, TX

#define MAX485_DE      4
#define MAX485_RE_NEG  5

// instantiate ModbusMaster object
ModbusMaster node1;
ModbusMaster node2;
ModbusMaster node3;
ModbusMaster node4;
ModbusMaster node5;
//ModbusMaster node6;

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
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
  node1.begin(1, mySerial);
  node2.begin(2, mySerial);
  node3.begin(3, mySerial);
  node4.begin(4, mySerial);
  node5.begin(5, mySerial);
//  node6.begin(6, mySerial);
  
//   Callbacks allow us to configure the RS485 transceiver correctly
  node1.preTransmission(preTransmission);
  node1.postTransmission(postTransmission);
  node2.preTransmission(preTransmission);
  node2.postTransmission(postTransmission);
  node3.preTransmission(preTransmission);
  node3.postTransmission(postTransmission);
  node4.preTransmission(preTransmission);
  node4.postTransmission(postTransmission);
  node5.preTransmission(preTransmission);
  node5.postTransmission(postTransmission);
//  node6.preTransmission(preTransmission);
//  node6.postTransmission(postTransmission);
}

void loop()
{
  uint8_t result1;
  uint16_t data1[2]; // prepare variable of storage data from sensor
  
  uint8_t result2;
  uint16_t data2[2]; // prepare variable of storage data from sensor
  
  uint8_t result3;
  uint16_t data3[2]; // prepare variable of storage data from sensor
  
  uint8_t result4;
  uint16_t data4[2]; // prepare variable of storage data from sensor
  
  uint8_t result5;
  uint16_t data5[2]; // prepare variable of storage data from sensor
  
//  uint8_t result6;
//  uint16_t data6[2]; // prepare variable of storage data from sensor

   
 // Serial.print("get data Sensor 1 : ");
  result1 = node1.readInputRegisters(1, 2); // Read 2 registers starting at 1)
  delay(200);
 // Serial.print("get data Sensor 2 : ");
  result2 = node2.readInputRegisters(1, 2); // Read 2 registers starting at 1)
  delay(200);
 // Serial.print("get data Sensor 3 : ");
  result3 = node3.readInputRegisters(1, 2); // Read 2 registers starting at 1)
  delay(200);
//  Serial.print("get data Sensor 4 : ");
  result4 = node4.readInputRegisters(1, 2); // Read 2 registers starting at 1)
  delay(200);
//  Serial.print("get data Sensor 5 : ");
  result5 = node5.readInputRegisters(1, 2); // Read 2 registers starting at 1)
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

  if (result3 == node3.ku8MBSuccess)
  {
    Serial.print("get data Sensor 3 : ");
    Serial.print("Temp : ");
    Serial.print(node3.getResponseBuffer(0)/10.0f);
    Serial.print(" Humi : ");
    Serial.println(node3.getResponseBuffer(1)/10.0f);
  }

  if (result4 == node4.ku8MBSuccess)
  {
    Serial.print("get data Sensor 4 : ");
    Serial.print("Temp : ");
    Serial.print(node4.getResponseBuffer(0)/10.0f);
    Serial.print(" Humi : ");
    Serial.println(node4.getResponseBuffer(1)/10.0f);
  }

  if (result5 == node5.ku8MBSuccess)
  {
    Serial.print("get data Sensor 5 : ");
    Serial.print("Temp : ");
    Serial.print(node5.getResponseBuffer(0)/10.0f);
    Serial.print(" Humi : ");
    Serial.println(node5.getResponseBuffer(1)/10.0f);
  }
  Serial.println();
  Serial.println();
  delay(3000);
  

  
  
}
