# ESP32-DHT11-Firebase
_This project use ESP32 board geting temperature and humidity from sensor DHT11, this data send to Firebase_ 

## Requirements

### Components
Is necessary have the following components:
* ESP32
* Sensor DHT11
* Micro USB Cable

### Libraries
To use this project it is necessary to have the following components installed.
* [ESP32 Board in IDE Arduino](https://randomnerdtutorials.com/* installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* [Library Adafruit/DHT-Sensor](https://github.com/adafruit/DHT-sensor-library)
* [Library Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)
* [Library taranais/NTPClient](https://github.com/taranais/NTPClient)

## Notes
### DHT11
* Define u pin data connected.
* Define u type sensor (DHT11 for DHT11, DHT22 for DHT22-AM2302-AM2321, DHT21 for DHT21-AM2301)
```
#define DHTPIN 15
#define DHTTYPE DHT11
```

### NTP
* Config u timezone [(get timezone)](https://www.timeanddate.com), this is config for UTC -4 (Winter time in Santiago, Chile).
```
// -4 = UTC - 4
const long gmtOffset_sec = -4 * 60 * 60;
...
timeClient.setTimeOffset(gmtOffset_sec);
``` 

## Versions
### V0.1
This version: 
* get temperature and humidity from DHT11 Sensor.
* Sync timezone with NTP server.
* Get epochTime.