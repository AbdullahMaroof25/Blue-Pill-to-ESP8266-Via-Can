

// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>

unsigned char TxData[1] = {0x25}; 
long unsigned int rxId;
unsigned char len = 0;
unsigned char flag = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

/* PINS:  CS=D8, INT=D4, SCK=D5, SO=D6, SI=D7 */
MCP_CAN CAN0(D8);                               // Set CS to pin 15 (D8)   --- 4 (D2 on my NodeMCU)
#define CAN0_INT 2                            // Set INT to pin 2 = D4

void setup() {
  
  // Init the Serial
  while (!Serial);
  Serial.begin(115200);

  // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)   // was MCP_ANY  MCP_STDEXT
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.  MCP_NORMAL
  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input       
  
  
}

void loop() 
{
 
   if(!digitalRead(CAN0_INT) )                         // If CAN0_INT pin is low, read receive buffer
  {
    
    Serial.println("ٌReceving CAN Message");
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  
    sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

    Serial.print(msgString);
  
      for(byte i = 0; i<len; i++)
      {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
      delay(1);
    CAN0.sendMsgBuf( 0x446 , 1 , TxData);
    Serial.println();
  }
  
 
}
