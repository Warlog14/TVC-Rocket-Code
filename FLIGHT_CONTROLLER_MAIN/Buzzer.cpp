#include "Buzzer.h"

Buzzer::Buzzer() {
  pinMode(BUZZER_PIN, OUTPUT);  // Konfiguriere den Buzzer-Pin als Ausgang
}

void Buzzer::playWelcomeTone() {
  // Einfache aufsteigende Tonsequenz
  tone(BUZZER_PIN, 262, 100);
  delay(150);
  tone(BUZZER_PIN, 294, 100);
  delay(150);
  tone(BUZZER_PIN, 330, 100);
  delay(150);
  tone(BUZZER_PIN, 349, 100);
  delay(150);
  tone(BUZZER_PIN, 392, 200);
  delay(350);  // Zusätzliche Pause, um das Ende der Sequenz zu signalisieren
}

void Buzzer::playPingBeacon() {
  // Zwei kurze Impulse mit einer Pause dazwischen
  tone(BUZZER_PIN, 440, 100);
  delay(200);
  tone(BUZZER_PIN, 440, 100);
  delay(500);  // Zusätzliche Pause, um das Ende der Sequenz zu signalisieren
}

void Buzzer::playSDKardAlert() {
  int frequency = 400;                 // Startfrequenz
  while (frequency > 250) {            // Solange die Frequenz über 20 Hz ist
    tone(BUZZER_PIN, frequency, 100);  // Spiele den Ton für 100ms
    delay(120);                        // Kurze Pause zwischen den Tönen, um die Änderung wahrnehmbar zu machen
    frequency -= 10;                   // Verringere die Frequenz schrittweise
  }

  // Optional: Sofortiger Rücksetzen auf 400 Hz und Abspielen, wenn unter 20 Hz erreicht sind
  tone(BUZZER_PIN, 400, 100);  // Zurücksetzen auf 400 Hz und Abspielen für 100ms
}

void Buzzer::playTelemetryAlert() {
  int highFreq = 1000;  // Hohe Frequenz
  int lowFreq = 250;    // Tiefe Frequenz
  int midFreq = 500;    // Mittlere Frequenz

  // Spiele den hohen Ton
  tone(BUZZER_PIN, highFreq, 200);  // 200ms Dauer
  delay(250);                       // Kurze Pause zwischen den Tönen

  // Spiele den tiefen Ton
  tone(BUZZER_PIN, lowFreq, 200);  // 200ms Dauer
  delay(250);                      // Kurze Pause zwischen den Tönen

  // Spiele den mittleren Ton
  tone(BUZZER_PIN, midFreq, 200);  // 200ms Dauer
}
