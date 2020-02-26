#include "WiFi.h"
#include <FirebaseESP32.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Variables WiFi
const char* ssid = "your SSID";
const char* pass = "your pass for SSID";

// Variables DHT11
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float tem;
float hum;

// Variables NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
const long gmtOffset_sec = -4 * 60 * 60;

// Variables Firebase
#define FIREBASE_HOST "YOUR_FIREBASE_PROJECT.firebaseio.com"
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET"
FirebaseData firebaseData;
FirebaseJson json;
String epochTime;
String path;

// Setup
void setup() {
  Serial.begin(115200);
  // WiFi Start
  Serial.println("Connect network:");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());;

  // Start NTP
  timeClient.begin();
  timeClient.setTimeOffset(gmtOffset_sec);

  // Start Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // DHT Start
  dht.begin();
}

// Loop
void loop() {
  
  // Validate WiFi connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(". - .");
  }
  
  // Update Time
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Get Temperature, Humidity and epochTime and set path
  tem = dht.readTemperature();
  hum = dht.readHumidity();
  epochTime = timeClient.getEpochTime();
  path = "/data/T-" + epochTime;

  // Validate that there are no errors in reading
  if( isnan(tem) || isnan(hum) ){
    Serial.println("----------------  ERROR ----------------");
    Serial.println("Error: sensor DHT11");
    Serial.println("--------------------------------");
    
    // send error
    sendError(epochTime, 111);
  } else {
    
    // Send data To Firebase
    json.clear();
    json.add("tem", tem);
    json.add("hum", hum);
    json.add("epochTime", epochTime);

    if (Firebase.setJSON(firebaseData, path, json)) {
      Serial.println("SEND SUCCESS");
      // pause 1 minutes
      delay(1000*60*1);
        
    } else {
        Serial.println("FAILED");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
    }
  }
  delay(30000);
}

void sendError(String epochTime, int codeError) {
  String pathError = "error/T-" + epochTime;
  FirebaseJson jsonError;
  jsonError.clear();
  jsonError.add("code", codeError);
  jsonError.add("epochTime", epochTime);

  switch (codeError) {
    case 111:
      jsonError.add("msj", "DHT11 - NaN value temperature or humidity");
      break;
    default:
      Serial.println("Error not found");
      break;
  }

  if (Firebase.setJSON(firebaseData, pathError, jsonError)) {
      Serial.println("SEND ERROR SUCCESS");
      // pause 1 minutes
      delay(1000*60*1);
        
    } else {
        Serial.println("SEND ERROR FAILED");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
        delay(1000);
    }
}
