#include <ESP8266WiFi.h>          // Replace with WiFi.h for ESP32
#include <ESP8266WebServer.h>     // Replace with WebServer.h for ESP32
#include <AutoConnect.h>

//https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/examples/PostServer/PostServer.ino

ESP8266WebServer Server;          // Replace with WebServer for ESP32
AutoConnect      Portal(Server);

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

/**
 * Handle http get from mobile app. Fetch
 * configuration from atmega device.
 */
void svGet() {
  if (Server.method() != HTTP_GET) {
    Server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "data";
    int length = 10;
    char buffer[10];
    Serial.readBytesUntil('\n', buffer, length);
    Server.send(200, "text/plain", message);
  }
}

/**
 * Handle http post from mobile app. Update
 * atmega chip variables using serial port.
 */
void svSet() {
  if (Server.method() != HTTP_POST) {
    Server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < Server.args(); i++) {
      message += " " + Server.argName(i) + ": " + Server.arg(i) + "\n";
    }
    // sent to atmega on UART
    Serial.println("sv:value");
    Server.send(200, "text/plain", message);
  }
}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }

  //handle request to update variables
  Server.on("/sv-set", svSet);
  Server.on("/sv-get", svGet);

  //handler should send update to serial
}

void loop() {
    
  
    Portal.handleClient();
}
