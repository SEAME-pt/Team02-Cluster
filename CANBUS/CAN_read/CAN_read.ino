#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMessage;
MCP2515 mcp2515(10);

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMessage) == MCP2515::ERROR_OK) {
    Serial.println("CAN_ID" + String(canMessage.can_id) + ":" + String(canMessage.data[0])); // Print CAN ID and CAN data
  }
}
