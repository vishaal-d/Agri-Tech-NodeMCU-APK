#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "DHT.h"
                          
#define FIREBASE_HOST "https://agri-tech-67113-default-rtdb.firebaseio.com"                    
#define FIREBASE_AUTH "PVsr9Wm60ZS4NUvRKPyJ2IQ7CMuNOvwbyjWPFXqu" 
#define WIFI_SSID "vivo_T2"                                               
#define WIFI_PASSWORD "12345678"                                      
 
 



FirebaseData firebaseData;
                                         
#define DHTTYPE DHT11
#define dht_dpin 3
DHT dht(dht_dpin, DHTTYPE);                                         



void setup(void) {

  Serial.begin(115200);                                   

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   

  Firebase.reconnectWiFi(true);
  delay(1000);

  pinMode (A0, INPUT);
  pinMode (D0, INPUT);


}

void loop() { 

  int h = dht.readHumidity();
  int t = dht.readTemperature();

  int moisture = analogRead (A0);

  int rain = digitalRead (D0);

  Serial.println("Temperature: ");
  Serial.print(t);

  Serial.println("Moisture :");
  Serial.print(moisture);

  Serial.println("Rain :");
  Serial.println(rain);

  

if (Firebase.setInt(firebaseData,"APP/Temperature",t)) { 
               Firebase.setInt(firebaseData,"APP/Humidity",h);   
               Firebase.setInt(firebaseData,"APP/Moisture",moisture);
               Firebase.setInt(firebaseData,"APP/Rain",rain);

               delay(1000);

     }

else {        
    Serial.println(firebaseData.errorReason());
  }

}

