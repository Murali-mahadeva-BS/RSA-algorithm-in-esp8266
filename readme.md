RSA Algorithm

Step1: Generating the keys
    1. Select two large prime numbers p and q
    2. Calculate n = p * q
    3. Calculate the totient function
ϕ(n)=(p−1) *(q−1)
    4. Select an integer e, such that 
    a) 1 < e < ϕ(n) 
    b) e is co-prime to ϕ(n) 
    5. The pair of numbers (n,e) makes up the public key.
    6. Calculate d such that
e.d = 1 modϕ(n).
    7. The pair (n,d) makes up the private key.

Step2: Encryption
Given a plaintext M, represented as a number, the encrypted text C is calculated as:
C = M^{e}mod n

Step3: Decryption
Using the private key (n,d) the plaintext can be found using:
M = C^{d} mod n.

# Explanation:

Arduino and esp8266 makes up a pair. Once is sender and other is receiver having unidirectional communication patter. Arduino and esp8266 communicate with each other serially. All the encryption is handled by arduino and esp8266 is used only for wireless datatransfer. Once both sender adn receiver esp8266 are connected to wifi, they printout their local IP's. Rsa public and private key generation is done on the receiver arduino. 2 prime numbers p and q are passed to arduino to generate the key pair. Values are passed from web browser using the API provided by receiver esp8266 which then passes the values to arduino serially. Once the key pair are generated, public key of the receiver is saved in the sender arduino for encryption. Receiver IP is saved in sender esp8266 for wireless data transfer over http. Sender esp8266 behaves as both  server and client. It exposes few API's for user input and acts as client when sending data to receiver esp8266. Public key(e, n) is used for encrypting user data. Once the message is encrypted, esp8266 sends it to receiver esp8266 which later decrypts using its private key and displays the actual input.

# Output implementation:

1. Find the ip of the receiver 
2. set p(receiver) ⇒ /setP?p=3  
3. set q(receiver) ⇒/setQ?q=7
4. Generate key on receiver ⇒ /genkeys
5. set receiver ip in sender ⇒ /setHost?host=ip
6. set public key on receiver ⇒ /setE?e=12
7. set public key on receiver ⇒/setN?n=200
8. encrypt message on sender ⇒ /encrypt?message=12
9. send the cipher text from sender to receiver = /sendMessage
10. decrypt the cipher received on receiver ⇒ /message
