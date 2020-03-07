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
* [ESP32 Board in IDE Arduino](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* [Library Adafruit/DHT-Sensor](https://github.com/adafruit/DHT-sensor-library)
* [Library Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)
* [Library taranais/NTPClient](https://github.com/taranais/NTPClient)
* [Firebase-ESP32 Library](https://github.com/mobizt/Firebase-ESP32)

## Notes
### DHT11
* Define u pin data connected.
* Define u type sensor (DHT11 for DHT11, DHT22 for DHT22-AM2302-AM2321, DHT21 for DHT21-AM2301)
```
#define DHTPIN 15
#define DHTTYPE DHT11
```

### NTP
* Config u timezone [(get timezone)](https://www.timeanddate.com), this is config for UTC -4 (Summer time in Santiago, Chile).
```
// -3 = UTC - 3
const long gmtOffset_sec = -3 * 60 * 60;
...
timeClient.setTimeOffset(gmtOffset_sec);
``` 

### Firebase
* Get your credentials Firebase ![credentials Firebase](https://raw.githubusercontent.com/sergioeabarcaf/ESP32-DHT11-Firebase/master/firebaseCredential.png)

## Releases
### V0.1
This release: 
* get temperature and humidity from DHT11 Sensor.
* Sync timezone with NTP server.
* Get epochTime.

### V0.2
This release:
* Use [Firebase-ESP32 Library](https://github.com/mobizt/Firebase-ESP32).
* Send data JSON type.
* Create function _sendError_. 

### V0.2.1
This release:
* send date formatted.
* use UTC - 3.
