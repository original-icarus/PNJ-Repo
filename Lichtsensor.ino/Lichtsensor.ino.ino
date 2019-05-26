// Funktionsdeklaration:
  // Funktion_1: Temperatur auslesen
  // Funktion_2: Lichtstärke auslesen
  // Funktion_3: Stepper
  // Funktion_4: Servo
  // Funktion_5: Luftfeuchtigkeit auslesen
  // Funktion_6: Displayausgabe
  // Funktion_7: Ladestatus
  // Funktion_8: Manuelle Steuerung
  // Funktion_9: Menü

 #include <Servo.h> //Die Servobibliothek wird aufgerufen. Sie wird benötigt, damit die Ansteuerung des Servos vereinfacht wird.

  int photosensorAuslesen();
  int motorSteuerung();
  int photosensorAnzeige();
  Servo servoblau; //Erstellt für das Programm ein Servo mit dem Namen „servoblau“

  
void setup() {
  // put your setup code here, to run once:

pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
pinMode(7, OUTPUT);
pinMode(4, OUTPUT);


//Servo-Setup
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


servoblau.attach(10); //Das Setup enthält die Information, dass das Servo an der Steuerleitung (gelb) mit Pin 10 verbunden wird. Hier ist natürlich auch ein anderer Pin möglich.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void loop() {
  // put your main code here, to run repeatedly:



Serial.begin(9600); //Im Setup beginnt die serielle Kommunikation, damit die Temperatur an den serial monitor übertragen wird. Über die serielle Kommunikation sendet das Board die Messwerte an den Computer. In der Arduino-Software kann man unter „Werkzeuge“ den „Seriellen Monitor“ starten um die Messwerte zu sehen.

photosensorAnzeige();
photosensorAuslesen();
motorSteuerung();

delay(5000);

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int photocellPin1 = 1;     // the cell and 10K pulldown are connected to a1
int photocellPin2 = 2;     // the cell and 10K pulldown are connected to a2
int photocellPin3 = 3;     // the cell and 10K pulldown are connected to a3
int photocellPin4 = 4;     // the cell and 10K pulldown are connected to a4


float photosensor_oben_links;   // the analog reading from the sensor divider for sensor 1 //links oben
float photosensor_oben_rechts;  // the analog reading from the sensor divider for sensor 2 //rechts oben
float photosensor_unten_links;  // the analog reading from the sensor divider for sensor 3 // links unten
float photosensor_unten_rechts; // the analog reading from the sensor divider for sensor 4 //Rechts unten


//Angleichungsfaktoren: Gleicht Fotosensoren auf ein Niveau bei gleicher Lichtstärke an, damit sinnvoller Vergleich möglich wird.
//Ohne den Angleichungsfaktor haben die Lichtsensoren andere Basiswerte, wodurch der Vergleich mittels Differenz einen durchgehenden Ausschlag in eine Richtung ermittleln würde.
  float n = 200/189;
  float m = 200/220;
  float j = 200/220;
  float k = 200/174;

int photosensorAuslesen(){

  photosensor_oben_links = n*analogRead(photocellPin1); 
  photosensor_oben_rechts = m*analogRead(photocellPin2); 
  photosensor_unten_links = j*analogRead(photocellPin3); 
  photosensor_unten_rechts = k*analogRead(photocellPin4);

return 0;
}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







//Motorsteuerung 


int a = 90;


int motorSteuerung()
{
int photosensor_oben = photosensor_oben_links + photosensor_oben_rechts;
int photosensor_unten = photosensor_unten_links + photosensor_unten_rechts;


if (photosensor_oben - photosensor_unten <-10 )
  {
    a= a+10;
servoblau.write(a); //Position 1 ansteuern mit dem Winkel 0°
  }
else if (photosensor_unten - photosensor_oben <-10)
  {
    a= a-10;
servoblau.write(a); //Position 2 ansteuern mit dem Winkel 90°
  }
/*
if (photosensor3 - photosensor4 <-10)
  {
//Stepper
  }
else if (photosensor4 - photosensor3 <-10)
  {
//Stepper
  }
 */
return 0;

}







/* Falls Die Differenz = Photosensor1 - Photosensor2 < 0 -->  LED rechts

   sonst --> LED links

   Falls Die Differenz = Photosensor3 - Photosensor4 < 0-->  LED unten

   sonst --> LED oben

   
 */


//Photosensor-Anzeige
int photosensorAnzeige()
{
  
  Serial.print("Analog reading oben links = ");
  Serial.println(photosensor_oben_links);     // the raw analog reading
  Serial.print("Analog reading oben rechts = ");
  Serial.println(photosensor_oben_rechts);     // the raw analog reading
  Serial.print("Analog reading unten links = ");
  Serial.println(photosensor_unten_links);     // the raw analog reading
  Serial.print("Analog reading unten rechts = ");
  Serial.println(photosensor_unten_rechts);     // the raw analog reading
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
 
  
} 
  
  
 
















/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see http://learn.adafruit.com/photocells */


/*


int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        //


int photoSensor(int k);


void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
}
 
void loop(void) {

for(int i = 0; i < 3; i++)
    {

    photoSensor(i);

    }


 
  delay(100);
}



int photoSensor(int k){

  photocellReading = analogRead(20 + k);  // es werden die Pins 20 bis 23 für die Photosensoren ausgewertet
 

 return photocellReading;
 /* 
 
 Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDbrightness);

  */
   /* 
}

*/
