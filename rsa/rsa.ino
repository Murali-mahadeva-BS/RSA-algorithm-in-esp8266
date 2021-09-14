void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  
   int p = 13;
   int q = 11;
   char msg[]="hello123";

   int len,i;
   int message[100],m1[100];
   char decry[100];
   double c[100],m[100];
   len =strlen(msg); 
   for(i=0;i<len;i++)
   message[i]=msg[i];
   
   int n=p*q;//calculate n
   int track;
   double phi= (p-1)*(q-1);//calculate phi
   //public key
   //e stands for encrypt
   double e=7;
   //for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
   while(e<phi) {
      track = gcd(e,phi);
      if(track==1)
         break;
      else
         e++;
   }
   //private key
   //d stands for decrypt
   //choosing d such that it satisfies d*e = 1 mod phi
   
   
   double d1=1/e;
   double d=(fmod(d1,phi));
   for(i=0;i<len;i++)
      { c[i] = pow(message[i],e); //encrypt the message
        m[i] = pow(c[i],d);
        c[i]=fmod(c[i],n);
        m[i]=fmod(m[i],n);
        m1[i]=round(m[i]);
        decry[i]=m1[i];
      }
   
    
   Serial.println("Original Message = ");
   Serial.println(msg);
   Serial.println(" ");
   Serial.println(" ");
   Serial.println("Encrypted message = ");
   for(i=0;i<len;i++)
   Serial.print(c[i]);
   Serial.println(" ");
   Serial.println(" ");
   Serial.println(" ");
   
   Serial.println("Decrypted message = ");
   for(i=0;i<len;i++)
   Serial.print(decry[i]); 
   
   delay(100000);
   
}
int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}
