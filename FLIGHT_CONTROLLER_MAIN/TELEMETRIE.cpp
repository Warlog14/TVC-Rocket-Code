#include "Telemetrie.h"

Telemetrie::Telemetrie()
  : radio(33, 32), imu(), bmp260() {
  // Konstruktor-Logik...
}

void Telemetrie::begin() {
  radio.begin();
  // Die Adresse muss als Byte-Array angegeben werden
  const uint8_t address[6] = "00001";
  radio.openWritingPipe(address);
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();  // Setzen Sie das Modul in den Sendemodus
  GPSinit(GPS_RX, GPS_TX, GPS_baud);
}

void Telemetrie::sendTelemetry(float AngleX, float AngleY, float AccX, float AccY, float AccZ, float Altitude) {

  // Set decimal point accuracy
  unsigned int accuracy = 2;
  char textdata[64];

  // format = key number key number (Ex: AngX0.125AngY0.55)
  String text = "A" + String(AngleX, accuracy) + "B" + String(AngleY, accuracy) + "C" + String(AccX, accuracy) + "R" + String(AccY, accuracy) + "W" + String(AccZ, accuracy) + "F" + String(Altitude, accuracy);
  text.toCharArray(textdata, sizeof(textdata));
  radio.write(&textdata, sizeof(textdata));
}

void Telemetrie::GPSinit(uint8_t RX, uint8_t TX, int GPSBaud) {
  SerialGPS.begin(GPSBaud, SERIAL_8N1, RX, TX);
  Serial.println(F("NEO-6M GPS-Modul Test mit TinyGPS++ Bibliothek"));
}

void Telemetrie::sendGPS() {
  if ((SerialGPS.available() > 0) && (gps.encode(SerialGPS.read()))) {
    if (gps.location.isValid()) {
      double lat = gps.location.lat();
      double lng = gps.location.lng();
      unsigned int accuracy = 6;
      char textdata[64];
      Serial.println("Breitengrad: " + String(lat, accuracy) + "\tLängengrad: " + String(lng, accuracy));
      String text = ("G" + String(lat, accuracy) + "N" + String(lng, accuracy));
      text.toCharArray(textdata, sizeof(textdata));
      radio.write(&textdata, sizeof(textdata));
    } else {
      Serial.println(F("Suche nach GPS-Signal..."));
    }
  }
}