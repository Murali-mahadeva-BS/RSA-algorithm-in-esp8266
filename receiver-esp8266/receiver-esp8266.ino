#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Murali"; //Enter your WIFI ssid
const char *password = "muMarahalide"; //Enter your WIFI password

String temp, message, ip, cipher, pq, p, q, n, phi, e, d, test;

ESP8266WebServer server(80);

void handleRoot() {
 server.send(200, "text/plain", "Esp8266 receiver on IP : "+ip);
}

void handleDecrypt() {
//  cipher= server.arg("message");
 if (server.hasArg("plain")== false){ //Check if body received
        server.send(200, "text/plain", "Cipher text not received");
        return;
      }
      cipher = server.arg("plain");
  delay(1000);
  server.send(200, "text/plain", "cipher text "+cipher+" received");
}


void handleMessage(){
   Serial.println("decrypt");
  delay(1000);
  Serial.println(cipher);
  delay(1000);
//  while (Serial.available() == 0){}; //waiting for arduino to respond
  message = Serial.readString();
  delay(1000);
   server.send(200, "text/plain", "Cipher text:"+cipher+" Decrypted  message: "+message);
}

void handleSetP(){
   p = server.arg("p");
   Serial.println("setP");
   delay(1000);
   Serial.println(p);
   while(Serial.available()==0){};
   p = Serial.readString();
   server.send(200,"text/plain", "P is set to "+p);
}

void handleSetQ(){
   q= server.arg("q");
   Serial.println("setQ");
   delay(1000);
   Serial.println(q);
   while(Serial.available()==0){};
   q= Serial.readString();
   server.send(200,"text/plain", "Q is set to "+q);
}

void handleGenkeys() {
  Serial.println("genkeys");
  while (Serial.available() == 0){}; //waiting for arduino to respond
 temp = Serial.readString();
server.send(200,"text/plain",temp);
}

void setup() {
 delay(3000);
 Serial.begin(115200);
 Serial.println();
 Serial.print("Configuring wifi access point...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 ip = WiFi.localIP().toString();
 Serial.print("IP address: ");Serial.println(ip);

 
 server.on ( "/", handleRoot );
 server.on ( "/decrypt", handleDecrypt);
 server.on ( "/genkeys", handleGenkeys);
 server.on ( "/message", handleMessage);
 server.on ( "/setP", handleSetP);
 server.on ( "/setQ", handleSetQ);


 server.begin();
 Serial.println ( "HTTP server started" );
}
void loop() {
 server.handleClient();
}
