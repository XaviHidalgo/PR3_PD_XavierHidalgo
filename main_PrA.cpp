#include <Arduino.h>


#include <WiFi.h>
#include <WebServer.h>


// SSID & Password
const char* ssid = "Xiaomi_11T_Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here


WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)


// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Primera guai Pagina con ESP32 - Station Mode &#128522;</h1>\
<a href=\"https://www.freepik.es\"><img src=\"https://img.freepik.com/foto-gratis/ojo-belleza-pintado-purpura-vibrante-elegante-generado-ia_188544-9707.jpg?size=626&ext=jpg\" alt=\"Descripción de la imagen\"></a>\
</body>\
</html>";


// Handle root url (/)
void handle_root() {
server.send(200, "text/html", HTML);
}




void setup() {
Serial.begin(115200);
Serial.println("Try Connecting to ");
Serial.println(ssid);


// Connect to your wi-fi modem
WiFi.begin(ssid, password);


// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP());  //Show ESP32 IP on serial


server.on("/", handle_root);


server.begin();
Serial.println("HTTP server started");
delay(100);
}


void loop() {
server.handleClient();
}