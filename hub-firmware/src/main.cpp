#include "headers.h"
#include <neotimer.h>
Neotimer mqttTimer = Neotimer(12000); // 12 second timer

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void initESPNOW();
void connectWiFi();

void initESPNOW()
{
  WiFi.mode(WIFI_STA);
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
  printBoardsDataStructure(boardsStruct);
}

void connectWiFi()
{
  // Begin WiFi in station mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi");

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected!");
}

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station

  // wclient.stop();
  // mqttClient.disconnect();
  delay(1000);
  initESPNOW();

  Serial.println(utils.getMACAddress());
  mqttTimer.set(12000); // Sets the timer preset to 2 second intervals

  // setupESPNOW();
}

void loop()
{
  // printBoardsDataStructure(boardsStruct);
  // delay(10000);
  if (mqttTimer.repeat())
  {
    esp_now_deinit();
    connectWiFi();
    mqttConnect();
    mqttClient.loop();
    delay(200);
    reconnect();
    mqttClient.loop();
    // mqttPublish("test97/t97", String(data_packets_counter));
    mqttPublish("test97/t97", String(getBoardData(boardsStruct[0])));
    mqttClient.loop();
    mqttClient.loop();

    mqttClient.loop();
    delay(500);
    mqttClient.loop();
    wclient.stop();
    mqttClient.disconnect();
    WiFi.disconnect();
    initESPNOW();
  }
}