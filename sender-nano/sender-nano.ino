#include<math.h>
String command = "", temp ;
float e, n, message, cipher;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    //serial communication is present
    command = Serial.readString();
    command.trim();
    
    if(command == "setE"){
        while(Serial.available()==0){};//waiting for user input
        e = Serial.readString().toFloat();
        Serial.println(e);
    }
        if(command == "setN"){
        while(Serial.available()==0){};//waiting for user input
        n = Serial.readString().toFloat();
        Serial.println(n);
    }

    if(command == "getKey"){
      temp = "E :"+String(e)+" N: "+String(n);
      Serial.println(temp);
    }

    if(command == "encrypt"){
      //encypting message
      while(Serial.available()==0){};//wait for user input
      message = Serial.readString().toFloat();//reading message from user
      cipher = pow(message, e);//cipher is message to the power of e
      cipher = fmod(cipher, n);//cipher text
//      delay(1000);
     Serial.println(cipher);//printing cipher text
      
    }
  }

}
