#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Utils.h>
#include "boards_structure.h"
Utils utils;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
  if (data_packets_counter == 25)
  {
    data_packets_counter = 0; // reset the counter
  }
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));

  boardsStruct[data_packets_counter] = myData;
  Serial.println("incomming data ");
  printMessageStruct(boardsStruct[data_packets_counter]);
  data_packets_counter++;
  Serial.println();
}

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  Serial.println(utils.getMACAddress());
  String mc = utils.getMACAddress();
  long long val = mc.toInt();
  Serial.println(mc);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  printBoardsDataStructure(boardsStruct);
  delay(10000);
}