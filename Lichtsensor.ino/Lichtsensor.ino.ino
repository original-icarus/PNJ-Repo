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

  int photosensorAuslesen();
  int motorSteuerung(int photosensor1, int photosensor2, int photosensor3, int photosensor4);
  int photosensorAnzeige();



int LEDrechts = 6;
int LEDlinks = 5;
int LEDoben = 7;
int LEDunten = 4;
  

  
void setup() {
  // put your setup code here, to run once:

pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
pinMode(7, OUTPUT);
pinMode(4, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:



Serial.begin(9600); //Im Setup beginnt die serielle Kommunikation, damit die Temperatur an den serial monitor übertragen wird. Über die serielle Kommunikation sendet das Board die Messwerte an den Computer. In der Arduino-Software kann man unter „Werkzeuge“ den „Seriellen Monitor“ starten um die Messwerte zu sehen.

photosensorAnzeige();
photosensorAuslesen();

delay(2000);

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int photocellPin1 = 1;     // the cell and 10K pulldown are connected to a1
int photocellPin2 = 2;     // the cell and 10K pulldown are connected to a2
int photocellPin3 = 3;     // the cell and 10K pulldown are connected to a3
int photocellPin4 = 4;     // the cell and 10K pulldown are connected to a4

int photocellReading1;     // the analog reading from the sensor divider for sensor 1 //links oben
int photocellReading2;     // the analog reading from the sensor divider for sensor 2 //rechts oben
int photocellReading3;     // the analog reading from the sensor divider for sensor 3 // links unten
int photocellReading4;     // the analog reading from the sensor divider for sensor 4 //Rechts unten



int photosensorAuslesen(){

  photocellReading1 = analogRead(photocellPin1); 
  photocellReading2 = analogRead(photocellPin2); 
  photocellReading3 = analogRead(photocellPin3); 
  photocellReading4 = analogRead(photocellPin4);

motorSteuerung(photocellReading1, photocellReading2, photocellReading3, photocellReading4);

}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int motorSteuerung(int photosensor1, int photosensor2, int photosensor3, int photosensor4)
{

if (photosensor1 - photosensor2 <-10)
  {
    digitalWrite (LEDrechts, HIGH);
    digitalWrite(LEDlinks, LOW);  
  }
else if (photosensor2 - photosensor1 <-10)
  {
    digitalWrite(LEDlinks, HIGH);  
    digitalWrite (LEDrechts, LOW); 
  }

if (photosensor3 - photosensor4 <-10)
  {
    digitalWrite (LEDunten, HIGH);
     digitalWrite(LEDoben, LOW);  
  }
else if (photosensor4 - photosensor3 <-10)
  {
    digitalWrite(LEDoben, HIGH);  
    digitalWrite (LEDunten, LOW); 
  }
  
return 0;

}







/* Falls Die Differenz = Photosensor1 - Photosensor2 < 0 -->  LED rechts

   sonst --> LED links

   Falls Die Differenz = Photosensor3 - Photosensor4 < 0-->  LED unten

   sonst --> LED oben

   
 */
int photosensorAnzeige()
{
  
  Serial.print("Analog reading oben links = ");
  Serial.println(photocellReading1);     // the raw analog reading
  Serial.print("Analog reading oben rechts = ");
  Serial.println(photocellReading2);     // the raw analog reading
  Serial.print("Analog reading unten links = ");
  Serial.println(photocellReading3);     // the raw analog reading
  Serial.print("Analog reading unten rechts = ");
  Serial.println(photocellReading4);     // the raw analog reading
 
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
