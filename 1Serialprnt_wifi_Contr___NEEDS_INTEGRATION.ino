#include <WiFi.h>
#include <Arduino.h>

const char* ssid = "ZhouLab";
const char* password = "ZhouRobotics917";

WiFiServer server(10000);

void setup() {
  Serial.begin(115200);
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  server.begin();
  printWifiStatus();
  Serial.println("Listening on port 10000");
}

boolean alreadyConnected = false;
static WiFiClient client;
static uint8_t buffer[sizeof(int)];

int intVariable1 = 0;
int intVariable2 = 0;
int intVariable3 = 0;
int intVariable4 = 0;
int intVariable5 = 0;
int intVariable6 = 0;
int intVariable7 = 0;

void loop() {
  if (!client) {
    client = server.available();
    if (client) {
      Serial.println("We have a new client");
      alreadyConnected = true;
    }
  } else {
    if (client.connected()) {
      char type[2];
      int bytesRead = client.readBytes(type, sizeof(type));

      if (bytesRead == sizeof(type)) {
        type[2] = '\0';
        if (strcmp(type, "I1") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable1, buffer, sizeof(intValue));
            Serial.printf("Received integer value 1: %d\n", intVariable1);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else if (strcmp(type, "I2") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable2, buffer, sizeof(intValue));
            Serial.printf("Received integer value 2: %d\n", intVariable2);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else if (strcmp(type, "I3") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable3, buffer, sizeof(intValue));
            Serial.printf("Received integer value 3: %d\n", intVariable3);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else if (strcmp(type, "I4") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable4, buffer, sizeof(intValue));
            Serial.printf("Received integer value 4: %d\n", intVariable4);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else if (strcmp(type, "I5") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable5, buffer, sizeof(intValue));
            Serial.printf("Received integer value 5: %d\n", intVariable5);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else if (strcmp(type, "I6") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable6, buffer, sizeof(intValue));
            Serial.printf("Received integer value 6: %d\n", intVariable6);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else if (strcmp(type, "I7") == 0) {
          int intValue;
          bytesRead = client.readBytes(buffer, sizeof(intValue));
          if (bytesRead == sizeof(intValue)) {
            memcpy(&intVariable7, buffer, sizeof(intValue));
            Serial.printf("Received integer value 7: %d\n", intVariable7);
          } else {
            Serial.println("Received integer data with incorrect size");
          }
        } else {
          Serial.println("Unknown data type received");
        }
      }
    } else {
      client.stop();
      alreadyConnected = false;
    }
  }
}

void printWifiStatus() {
  Serial.print("\nSSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
