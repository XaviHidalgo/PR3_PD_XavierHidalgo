# PR3_PD_XavierHidalgo

## PRACTICA 3: WIFI y BLUETOOTH

### Practica A generación de una pagina web


**PROGRAMA WIFI:**
``` cpp
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
```

**INFORME:**

El programa anterior es el programa dado por la práctica pero con una modificación. A continuación explicaré como funciona el programa y que se muestra por el puerte série tras la ejeccución del mismo.

Con el objetivo de conseguir que nuestro MP se connecte vía WIFI con el servidor web de la práctica (un móbil), utilizaremos las librerías Wifi.h. Para que el MP envie la página web (en HTML), que más adelante describiremos, al servidor web utilizaremos la librería WebServer.h. Después de incluir ambas librerías, con el siguiente punto importante que nos encontramos es con la decraración de un string llamado HTML el cúal contiene, efectivamente, un código en HTML (una página web).
La página contiene un mensaje que dice "My Primera guai Pagina con ESP32" y tras este una imagen extraída de una web. El mensaje tiene esta forma no lógica ya que, tras conseguir connectarnos a la página web, estuvimos cambiando el mensaje para ver si se iba actualizando tras nuestros cambios en el programa, lo conseguimos. A continuación guardamos el string en la función server.send de WebServer.h.

Más adelante, ya en el void_setup(), inicializamos el puerto série y utilizando las funciones de Wifi.h recorremos un while que va mandando puntos cada segundo por el puerto série hasta conseguir connectarse con el WIFI. Tras conseguirlo, envía una serie de mensajes por el puerto série como la IP, siendo capaz de ello utilizando la función localIP() de la última libreria nombrada.

Finalmente en el void_loop() se envía la página web anteriormente descrita.


### Practica B comunicación bluetooth con el movil


**PROGRAMA BLUETOOTH:**
``` cpp
//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial


#include "BluetoothSerial.h"
BluetoothSerial SerialBT;


void setup() {
 Serial.begin(115200);
 SerialBT.begin("BlutuDelDiablo"); //Bluetooth device name
 Serial.println("The device started, now you can pair it with bluetooth!");
}


void loop() {
 if (Serial.available()) {
   SerialBT.write(Serial.read());
 }
 if (SerialBT.available()) {
   Serial.write(SerialBT.read());
 }
 delay(20);
}
```

**INFORME:**

Para esta segunda parte de la práctica utilizaremos la librería BluetoothSerial.h, que nos dará la oportunidad de crear variables tipo BluetoothSerial las cuales incluien funciones para poder establecer facilmente una conexión Bluetooth. Gracias a estas funciones, también podremos enviar infomación (mensajes) tanto del MP al dispositivo conectado como al inrevés, como más adelante veremos, creamos una especie de chat. 

Bien, tras incluir la librería anteriormente nombrada, declaramos nuestra variable tipo BluetoothSerial llamada SerialBT. Ya en el void_setup(), como siempre hacemos inicializamos el puerto série. A continuación, utilizando la función - .begin - de nuestra librería, nuestro MP creará una red Bluetooth la cual nosotros llamamos "BlutuDelDiablo". 

Tras inicializarlo todo, yéndonos al void_loop, nos encontramos con 2 if's que se ejecutan independientemente uno del otro. Ambos hacen lo mismo, con la única diferencia de que uno se ejecuta si el puerto série del MP esta operativo y el otro si el puerto série del dispositivo connectado lo está. Si estos if's se cumplen verdaderamente (como debería ser siempre), el puerto série del MP escribirá lo que lea del puerto série del dispositivo connectado y viceversa para el otro if. De esta forma si yo con mi dispositivo envío un mensaje, saldra escrito en la impresión série del MP, y si lo envió desde el MP, saldra escrito en la impresión série del dispositivo, creando así un chat o, una versión primigenia de WhatsApp.

El práctica pudimos establecer una conexión vía Bluetooth con el MP con nuestros móviles y, utilizando la aplicación Serial Bluetooth Terminal, enviar mensajes tanto desde nuestro móvil hasta el MP como del MP hasta nuestro móvil. 
