#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//#include <SoftwareSerial.h>


ESP8266WebServer server;

uint8_t pin_led = 16;
char* ssid = "Ilyes";
char* password = "123456789";
char poubelle[100];
char parking[100];
//SoftwareSerial espSerial(0, 1);

// Serve the data as plain text, for example

void handleIndex(){

// Prepare the data for serving it over HTTP
String output = "<!DOCTYPE HTML><html><head>"<meta http-equiv=\"refresh\"content=\"6\">"</head><body><table border=1> <tr><td>poubelle</td> <td>"+String(poubelle)+"</td></tr><tr><td color=red>Parking</td> <td>"+String(parking)+"</td></table></body></html>";


server.send(200,"text/html",output);
delay(3000);

}

void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}

WiFi.begin(ssid,password);
Serial.begin(115200);
while(WiFi.status()!=WL_CONNECTED)
{
Serial.print(".");
delay(500);
}
Serial.println("");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
server.on("/", handleIndex);



server.begin();
}

void loop()
{
if (Serial.available())
{
     String data=Serial.readString();
     switch(data[0]) 
     {
          case '0':data.copy(poubelle,(data.size()-1),1);break;        
          case '1':data.copy(parking,(data.size()-1),1);break;          
  
     }



}
server.handleClient();

}