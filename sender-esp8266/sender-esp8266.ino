#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Murali"; //Enter your WIFI ssid
const char *password = "muMarahalide"; //Enter your WIFI password

String ip, host, command, message, e, n, cipher, temp;
boolean hostPresent = false, hostConnected = false;

ESP8266WebServer server(80);


// Set up the client objet
WiFiClient client;
HTTPClient http;


void handleRoot() {
 server.send(200, "text/plain", "Esp8266 sender on IP : "+ip);
}

void handleSetHost() {
     host = server.arg("host");
     hostPresent = true;
 server.send(200, "text/plain", "Host ip set to : "+host);
}

void handleIsConnected(){
  server.send(200, "text/plain", "Host connection status :"+String(hostConnected));
}

void handleSetE(){
  e = server.arg("e");
  Serial.println("setE");
  delay(1000);
  Serial.println(e);
  delay(1000);
//  while(Serial.available()==0){};
  delay(1000);
  e = Serial.readString();
  delay(1000);
  server.send(200, "text/plain", "E is set as "+e);
}

void handleSetN(){
  n = server.arg("n");
  Serial.println("setN");
  delay(1000);
  Serial.println(n);
  delay(1000);
//  while(Serial.available()==0){};
  delay(1000);
  n = Serial.readString();
  delay(1000);
  server.send(200, "text/plain", "N is set as "+n);
}

void handleGetKey(){//get public key
  Serial.println("getKey");
  while(Serial.available()==0){};//waiting for input
  temp = Serial.readString();
  server.send(200, "text/plain",temp);
}

void handleEncrypt(){//encrypting message
   message = server.arg("message");
   Serial.println("encrypt");
   delay(1000);
   Serial.println(message);
   delay(1000);
//   while(Serial.available()==0){};//waiting for input
   delay(1000); 
   cipher = Serial.readString();
   delay(1000);
   Serial.print("Cipher text: ");Serial.println(cipher);
   server.send(200, "text/plain", "Message : "+message+" Cipher text: "+cipher);
}

void handleSendMessage() {
      String receiverUrl = "http://"+host+"/decrypt";
    Serial.println(receiverUrl);
    delay(1000);
    http.begin(client, receiverUrl);
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.POST(cipher);
    if(httpCode > 0){
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.print("payload: ");Serial.println(payload);
               server.send(200, "text/plain", "Encrypted message sent to host");
        }
    }else{
      
         Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
         server.send(200, "text/plain", "message not sent");

    }
    http.end();
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
 Serial.println("ip");
 delay(1000);
 Serial.println(ip);
// Serial.print("sender IP address: ");Serial.println(ip);
 server.on ( "/", handleRoot );
  server.on ( "/setHost", handleSetHost);
  server.on ( "/setE", handleSetE);
  server.on ( "/setN", handleSetN);
  server.on ( "/sendMessage", handleSendMessage);
  server.on ( "/isConnected", handleIsConnected);
  server.on ( "/encrypt", handleEncrypt);
  server.on ( "/getKey", handleGetKey);
 server.begin();

}

void loop() {
   server.handleClient();
   if(hostPresent && client.connect(host, 80) && !hostConnected){
    Serial.println("Connected to host");
    hostConnected = true;
   }

}
