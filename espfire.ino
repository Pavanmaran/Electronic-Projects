/*
   Created by Pawan Meena
   Email: pavanmaran19199@gmail.com
   Website : iotinns.in
   Copyright (c) 2021 IoTinns Bot
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "fir-all-9d29a-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "OhQ0hID5jGItUlN8ea5jCtNlcs4Q2XvZNGZzuAAu"
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
    // Connect LED to D5
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);
*/
//Define FirebaseESP8266 data object
int led = D0; 
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;


void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT); 
  pinMode(BUILTIN_LED, OUTPUT); 

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
 
if (Firebase.setFloat(firebaseData, "/def_strings/sensors/sensor2",soil_moisture))
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
void ledf()
{
  Serial.println("led value :"+ledData.stringData());
  if (Firebase.getInt(ledData, "/def_strings/Sensor4")){
    Serial.println(ledData.intData());
    if (ledData.intData() == 1) {
    digitalWrite(BUILTIN_LED, HIGH);
    }
  else if (ledData.intData() == 0){
    digitalWrite(BUILTIN_LED, LOW);
    }
  } 
  delay(500); 
  }
  void loop() {
  sensorUpdate();
  ledf();
  
}
