#include "SDCard.h"

SDCard::SDCard() {
  // Konstruktor-Inhalt bleibt möglicherweise leer, falls keine spezielle Initialisierung erforderlich ist
}

void SDCard::begin() {
  if (!SD.begin(CS)) {
    Serial.println("Error: SD card initialization failed, or the card is not present!");
    buzzer.playSDKardAlert();  // Angenommen, diese Methode existiert im Buzzer
    led.blue();
    while (1)
      ;
  }
  Serial.println("SD card is ready for use.");
}

void SDCard::logData(float AngleX, float AngleY, float AccX, float AccY, float AccZ, float Altitude) {
  File dataFile = SD.open("/flightData.csv", FILE_APPEND);
  if (!dataFile) {
    Serial.println("Error: Could not open flightData.csv for writing.");
    return;
  }
  // Set decimal point accuracy
  unsigned int accuracy = 2;
  String text = String(AngleX, accuracy) + "," + String(AngleY, accuracy) + "," + String(AccX, accuracy) + "," + String(AccY, accuracy) + "," + String(AccZ, accuracy) + "," + String(Altitude, accuracy);

  uint8_t teaxtdata[text.length() + 1];  // Add 1 for null terminator
  text.getBytes(teaxtdata, sizeof(teaxtdata));
  //dataFile.write(teaxtdata, sizeof(teaxtdata));
  dataFile.println(text);

  // Schließe die Datei nach dem Schreiben
  dataFile.close();

  Serial.println("Data logged.");
  Serial.print("Angle X: " + String(AngleX) + " ");
  Serial.print("Angle Y: " + String(AngleY) + " ");
  Serial.print("Acc X: " + String(AccX) + " ");
  Serial.print("Acc Y: " + String(AccY) + " ");
  Serial.print("Acc Z: " + String(AccZ) + " ");
  Serial.println("Altitude: " + String(Altitude));
}
