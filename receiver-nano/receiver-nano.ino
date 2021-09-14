#include<math.h>

float p, q, n, phi, e = 2, count, k=2, d, cipher, message, a, b;
String command, pq, temp;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()){
    //serial communication is present
    command = Serial.readString();//reading serial data
    command.trim();

    if(command == "genkeys"){ 
      //generating keys
      n = p*q;
      phi = (p-1)*(q-1);
      //public key
      //for checking co-prime which satisfies 1<e<phi
      while(e<phi){
        count = gcd(e,phi);
        if(count==1)
            break;
        else
            e++;
        }
      d = (1 + (k*phi))/e; //choosing d such that it satisfies d*e = 1 + k * phi
      temp = "n = "+String(n)+"; phi = "+String(phi)+"; e = "+String(e)+"; d = "+String(d)+"; public key: "+"("+String(e)+","+String(n)+")"+" private key: "+"("+String(d)+","+String(n)+")";
      Serial.println(temp);
       
    }

    if(command == "setP"){//settign first prime number p
        while (Serial.available() == 0){}; //wait for the esp8266 to send p
        p = Serial.readString().toFloat();
        delay(1000);
        Serial.println(p);
    }

     if(command == "setQ"){//settign first prime number p
        while (Serial.available() == 0){}; //wait for the esp8266 to send q
        q = Serial.readString().toFloat();
        delay(1000);
        Serial.println(q);
    }
    
    if(command == "getPQ"){
       Serial.print(p);Serial.print(q);
    }

    if(command == "decrypt"){
        //decrypting the cipher text
        while (Serial.available() == 0){}; //waiting for the esp8266 to give cipher text
        cipher = Serial.readString().toFloat();//cipher text read
        message = pow(cipher, d);
        message = fmod(message, n);
        Serial.print(message);
    }

  }
  
}

//to find gcd
int gcd(int a, int h)
{
    int temp;
    while(1)
    {
        temp = a%h;
        if(temp==0)
        return h;
        a = h;
        h = temp;
    }
}
