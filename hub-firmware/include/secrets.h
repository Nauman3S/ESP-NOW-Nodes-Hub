#include<Arduino.h>
const char ssid[]="hotspot2";
const char password[] ="abc123098a#";

String mac = (WiFi.macAddress());
char __mac[sizeof(mac)];

const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_user = "device";
const char *mqtt_pass = "device";
const char *mqtt_client_name = __mac; //any random alphanumeric stirng