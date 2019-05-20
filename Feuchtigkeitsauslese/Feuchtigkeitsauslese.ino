// BUGFIX
//Sensor funktioniert nicht
// Feuchte gibt nur 0 aus 



// Programm Definitio: tbc....



//Funktionsdeklaration:
  // Funktion_1: Temperatur auslesen
  // Funktion_2: Lichtstärke auslesen
  // Funktion_3: Stepper
  // Funktion_4: Servo
  // Funktion_5: Luftfeuchtigkeit auslesen
  // Funktion_6: Displayausgabe
  // Funktion_7: Ladestatus
  // Funktion_8: Manuelle Steuerung
  // Funktion_9: Menü

// Bibliotheken Laden
#include <LiquidCrystal.h> //LCD-Bibliothek laden
#include <Wire.h>
#include <DHT.h>

// Variablen Defintion:

int TMP36 = A0; //Der Sensor soll am analogen Pin A0 angeschlossen werden. Wir nennen den Pin ab jetzt "TMP36"
int sensorwert;
int temperatur = 0; //Unter der Variablen "temperatur" wird später der Temperaturwert abgespeichert.
int t=1000; //Der Wert für „t“ gibt im Code die zeitlichen Abstände zwischen den einzelnen Messungen vor.

// LCD 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //In dieser Zeile wird festgelegt, welche Pins des Mikrocontrollerboards für das LCD verwendet wird (Am besten erstmal nicht verändern).

#define DHTPIN 8
#define DHTTYPE DHT11
 
// DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //Im Setup beginnt die serielle Kommunikation, damit die Temperatur an den serial monitor übertragen wird. Über die serielle Kommunikation sendet das Board die Messwerte an den Computer. In der Arduino-Software kann man unter „Werkzeuge“ den „Seriellen Monitor“ starten um die Messwerte zu sehen.

// LCD 
lcd.begin(16, 2); //Im Setup wird angegeben, wie viele Zeichen und Zeilen verwendet werden. Hier: 16 Zeichen in 2 Zeilen.

// DHT 
dht.begin(); //Im Setup wird der DHT11 gestartet
delay(500);

}





void loop() {
  // put your main code here, to run repeatedly:
sensorwert=analogRead(TMP36); //Auslesen des Sensorwertes.
temperatur= map(sensorwert, 0, 410, -50, 150); //Umwandeln des Sensorwertes mit Hilfe des "map" Befehls.
delay(t); // Nach jeder Messung ist je eine kleine Pause mit der Dauer „t“ in Millisekunden.
Serial.print(temperatur); //Nun wird der Wert „temperatur“ über die serielle Kommunikation an den PC gesendet. Durch öffnen des seriellen Monitors in der Arduino-Software kann die Temperatur abgelesen werden.
Serial.println(" Grad Celsius"); // Im seriellen Monitor wird hinter der Temperatur die Einheit eingeblendet.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//DHT
int humidity_data = (int)dht.readHumidity();
int temperature_data = (int)dht.readTemperature();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LCD Anzeige
lcd.setCursor(0, 0); //Startposition der Darstellung auf dem LCD festlegen. lcd.setCursor(0,0) bedeutet: Erstes Zeichen in der ersten Zeile.
lcd.print("Feuchte:   "); //Dort soll der Text „www.funduino.de“ erscheinen. Der Befehl lcd.setCursor ist dem Mikrocontrollerboard durch das Aufrufen der Bibliothek bekannt.
lcd.print(humidity_data);
lcd.setCursor(0, 1); // lcd.setCursor(0,1) bedeutet: Erstes Zeichen in der zweiten Zeile.
lcd.print("Temp.:  ");
lcd.print(temperatur);
lcd.print("\337C"); 
delay(500);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
