// Software Stack

class Utils
{
public:
#define DebugPrint(x) Serial.println(x)

  String stringSeparator(String data, char separator, int index);
  char *strToCharArray(String data);
  String getMACAddress();
  String getTopicWithMAC(String topic_name);
  String randomString(int len);
  Utils();

private:
  //  String configs="";
  char buf[100];
};
Utils::Utils()
{
}
char *Utils::strToCharArray(String data)
{
  data.toCharArray(this->buf, data.length() + 1);
  return this->buf;
}

String Utils::stringSeparator(String data, char separator, int index)
{

  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
String Utils::getMACAddress()
{
  String TrackerID = String(WiFi.macAddress());
  TrackerID = stringSeparator(TrackerID, ':', 0) + stringSeparator(TrackerID, ':', 1) + stringSeparator(TrackerID, ':', 2) + stringSeparator(TrackerID, ':', 3) +
              stringSeparator(TrackerID, ':', 4) + stringSeparator(TrackerID, ':', 5);
  return TrackerID;
}
String Utils::getTopicWithMAC(String topic_name)
{
  String t = getMACAddress();
  t = t + String("/") + topic_name;

  return t;
}

String Utils::randomString(int len)
{

  char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";

  String v = "";
  for (uint8_t i = 0; i < len; i++)
  {
    uint8_t randomValue = random(0, len);
    v = v + String(letters[randomValue]);
  }
  return v;
}