/*
   Created by Pi BOTS MakerHub

   Email: pibotsmakerhub@gmail.com

   Github: https://github.com/pibotsmakerhub

   Copyright (c) 2020 Pi BOTS MakerHub
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "espfire-fd8af.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "dAPRgic0jbEIiyHx4ecdB7TWwF92eZftMipSE7f0"
#define WIFI_SSID "Engineer29"
#define WIFI_PASSWORD "76919716"

/*
 #define FIREBASE_HOST "YOUR_FIREBASE_PROJECT.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET"
#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
 */
/*
#define DHTPIN 2    // Connect Data pin of DHT to D2
int led = D5;     // Connect LED to D5

#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);
*/
//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;


void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT); 

  

  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void sensorUpdate(){
 int Moisture = A0;
 int soil_moisture = analogRead(Moisture);   // read moisture sensor
// Moisture = soil_moisture;        //convert string to int
 Serial.println("Moisture Value : ");
  Serial.println(soil_moisture);
 delay(2000);
 
if (Firebase.setFloat(firebaseData, "/ESPfire/moisture",soil_moisture))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

}
void loop() {
  sensorUpdate();
  /*
  if (Firebase.getString(ledData, "/FirebaseIOT/led")){
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
    digitalWrite(led, HIGH);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    }
  } */
  delay(500); 
}
