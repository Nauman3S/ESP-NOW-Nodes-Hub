#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Utils.h>
Utils utils;
#include "boards_structure.h"

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClient wclient;
PubSubClient mqttClient(wclient);
String internetStatus="disconnected";

#include "mqtt_functions.h" //MQTT related functions