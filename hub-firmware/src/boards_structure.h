#include <Arduino.h>
#define MAX_DATA_PACKETS 25
// Structure to receive data
// Must match the sender structure
typedef struct struct_message
{
    String macStr;
    int generatedValue;
    String uniqueID;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create an array with all the structures
struct_message boardsStruct[MAX_DATA_PACKETS];

int data_packets_counter = 0;

void printMessageStruct(struct_message sm)
{
    Serial.println("{");
    Serial.print(" MAC Address: ");
    Serial.println(sm.macStr);
    Serial.print(" Generated Value: ");
    Serial.println(sm.generatedValue);
    Serial.print(" Unique ID: ");
    Serial.println(sm.uniqueID);
    Serial.println("}");
}

void printBoardsDataStructure(struct_message *sm_array)
{
    Serial.print("Data Points: ");
    Serial.println(data_packets_counter);
    Serial.println("**********");
    for (int i = 0; i < data_packets_counter; i++)
    {
        printMessageStruct(sm_array[i]);
    }
    Serial.println("**********");
}