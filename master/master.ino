1.  #include <SoftwareSerial.h>
2.  #include <time.h>
3.  //Define Pins
4.  #define RxD 11  //Receive Serial pin
5.  #define TxD 10  //Transmit Serial pin 
6.  SoftwareSerial bt(RxD, TxD) ;
7.  //Define for Data
8.  char btData;
9.  String splitString(String str, String devider, int arrayNumber);
10. String deviceAddress;
11. String deviceClass;
12. String deviceRSSI;
13. String message;
14.  
15. bool RSSIVisible = true;
16. String atQuestEnd = "?\r\n";
17. String atSetEnd = "\r\n";
18. String atStart = "AT+";
19. String Initialize = "INIT";
20. String accesCode = "IAC=9E8B33";
21. String deviceType = "CLASS=0";
22. String searchRSSI = "INQM=1,1,20";  
23. //INQM=<Par1>,<Par2>,<Par3>   Par1: 0--inquiry mode standard/1--inquiry mode rssi
24. //                            Par2: Numero max di device Bluetooth che rispondono
25. //                            Par3: Tempo (1-48 : 1.28s to 61.44s)
26. String receiveRSSI = "INQ";
27. String roleIsMaster = "ROLE=1";
28. String roleIsSlave = "ROLE=0";
29. float n;
30. #define BTkey 9
31. void ATCmdSetup() {
32.   bt.listen();
33.   bt.print(atStart + Initialize + atSetEnd);    //initialize device
34.   bt.print(atStart + accesCode + atSetEnd);    //defines the accesCode this device shares with the others
35.   bt.print(atStart + deviceType + atSetEnd);    //defines device type 
36.   bt.print(atStart + searchRSSI + atSetEnd);    //Search Bluetooth with RSSI value
37.   }
38.  
39. void filterCode() {
40.  if (message.substring(0, 5) == "+INQ:") {
41.     deviceAddress = splitString(message, ",", 0).substring(5);
42.     deviceClass = splitString(message, ",", 1);
43.     deviceRSSI = splitString(message, ",", 2);
44.    }
45.   message = "";
46. }
47.  
48. String splitString(String str, String devider, int arrayNumber) {
49.   int previousDevider = 0;
50.   int deviders = 1;
51.   for (int i = 0; i < str.length(); i++) {
52.     if (str.substring(i, i + devider.length()) == devider) {
53.       deviders++;
54.     }
55.   }
56.   int devideCounter = 0;
57.   String devidedString[deviders + 1];
58.   for (int i = 0; i < str.length(); i++) {
59.     if (str.substring(i, i + devider.length()) == devider) {
60.       if (devideCounter) {
61.         devidedString[devideCounter] = str.substring(devidedString[devideCounter   - 1].length() + 1, i);
62.       } else {
63.         devidedString[0] = str.substring(0, i);
64.       }
65.       devideCounter++;
66.       previousDevider = i + devider.length();
67.     }
68.   }
69.   devidedString[devideCounter] = str.substring(previousDevider, str.length());
70.   if (arrayNumber > deviders) {
71.     return "ERROR; array number not found. Array number is to big.";
72.   } else {
73.     return devidedString[arrayNumber];
74.   }
75. }
76.  
77. //Funzione che converte un numero esadecimale in decimale
78. unsigned int hexToDec(String hexString) {
79.   unsigned int decValue = 0;
80.   int nextInt;
81.   for (int i = 0; i < hexString.length()-2; i++) {
82.     nextInt = int(hexString.charAt(i));
83.     if (nextInt >= 48 && nextInt <= 57)
84.             nextInt = map(nextInt, 48, 57, 0, 9);
85.     if (nextInt >= 65 && nextInt <= 70)
86.             nextInt = map(nextInt, 65, 70, 10, 15);
87.     if (nextInt >= 97 && nextInt <= 102)
88.              nextInt = map(nextInt, 97, 102, 10, 15);
89.              
90.     nextInt = constrain(nextInt, 0, 15);
91.     decValue = (decValue * 16) + nextInt;
92.   }
93.   return decValue;
94. }
95.  
96. //Funzione per il calcolo della distanza
97. void distanceRSSI() {
98.   float tempo;
99.   float rssi_dbm; //RSSI scansionato
100.    float rssi_ref= -61;// RSSI ad 1 metro di distanza
101.    float distanza; //Variabile usata per memorizzare i valori della distanza di ogni singolo beacon rispetto al nodo target
102.    if(deviceAddress== "98D3:36:80EF77"){
103.      rssi_dbm=hexToDec(deviceRSSI)-65535; //complemento a due per determinare il valore RSSI in dBm
104.      Serial.print(rssi_dbm);
105.      Serial.print("  ");
106.      n=(rssi_ref - rssi_dbm)/(10*1.73);
107.        //Calcolo della distanza
108.        distanza=(100)*(pow(10,n));
109.        Serial.print(distanza);
110.        tempo=millis();
111.        Serial.print("  ");
112.        Serial.println(tempo/1000);
113.        }
114.          }
115.  }
116.   
117.  void setup() {
118.    // define pin modes for tx, rx:
119.    pinMode(RxD, INPUT);
120.    pinMode(TxD, OUTPUT);
121.    // Switch module to AT mode
122.    pinMode(BTkey, OUTPUT);
123.    digitalWrite(BTkey, HIGH);
124.    Serial.begin(9600);
125.    // Start the software serial - baud rate for AT mode is 38400
126.    bt.begin(38400); // HC-05 default speed in AT command mode
127.    ATCmdSetup();
128.    Serial.flush();
129.   }
130.   
131.  void loop() {
132.    // Keep reading from the HC-05 and send to the Arduino Serial Monitor
133.    if (bt.available()) {
134.     btData = bt.read();
135.     message.concat(btData); // la concatenazione avviene in 0,654 secondi
136.     if (btData == '\n'){
137.     bt.print(atStart + receiveRSSI + atSetEnd);      
138.      filterCode();
139.        if (RSSIVisible){        
140.               distanceRSSI();
141.                        }
142.                 }
143.                            }
144.  }
