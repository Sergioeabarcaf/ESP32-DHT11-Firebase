#include "WiFi.h"
// https://github.com/taranais/NTPClient
#include <NTPClient.h>
#include <WiFiUdp.h>
// https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>

// variables WiFi
const char* ssid = "VTR-4729468";
const char* pass = "gyhc5yhFdkps";

//variables DHT11
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Variables NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
const long gmtOffset_sec = -4 * 60 * 60;
const int daylightOffset_sec = 3600;


void setup() {
  Serial.begin(115200);
  // iniciar WiFi
  Serial.println("Conectando a la red:");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  Serial.println("Conectado!");
  Serial.println(WiFi.localIP());;

  // obtener hora actual
  timeClient.begin();
  timeClient.setTimeOffset(gmtOffset_sec);
  

  // iniciar DHT
  dht.begin();

}

void loop() {
  // actualizar hora
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  float tem = dht.readTemperature();
  float hum = dht.readHumidity();
  // obtener lecturas y validar que no hayan errores.
  if( isnan(tem) || isnan(hum) ){
    Serial.println("----------------  ERROR ----------------");
    Serial.println("Error en lectura del sensor DHT11");
    Serial.println("Temperatura");
    Serial.println(String(tem));
    Serial.println("Humedad");
    Serial.println(String(hum));
    Serial.println("--------------------------------");
  } else {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("no esta conectado a WiFi");
    }

    Serial.println("Temperatura");
    Serial.println(String(tem));
    Serial.println("Humedad");
    Serial.println(String(hum));
    Serial.println(timeClient.getEpochTime());
    Serial.println("--------------------------------");
    delay(1000*60*5);
    

    //Enviar datos a Firebase
    
  }

}
