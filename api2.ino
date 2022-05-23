
#include "Arduino.h"
#define BLYNK_TEMPLATE_ID "TMPLlyW88BSI"
#define BLYNK_DEVICE_NAME "UTS2"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define LED_HIJAU 19
#define LED_MERAH 22

#define AnalogMQ6 33
#define DigitalMQ6 32

#define Buzzer 18

#define Fire_analog 4
#define Fire_digital 5


//int Buzzer = 18;        
//int Fire_analog = 4;    
//int Fire_digital = 5;  

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7

#include "BlynkEdgent.h"

BlynkTimer timer;

void setup()
  {
    pinMode(Buzzer, OUTPUT);     
    pinMode(LED_HIJAU, OUTPUT);  
    pinMode(LED_MERAH, OUTPUT);
    
    pinMode(Fire_digital, INPUT);

    
    pinMode(AnalogMQ6, INPUT);
    pinMode(DigitalMQ6, INPUT);
    
    timer.setInterval(1000L, sendSensor);
    Serial.begin(115200);
    delay(100);
  
    BlynkEdgent.begin();
  }

void sendSensor()
  {
    
  }

void sensorGas()
  {
//    AnalogOut(AnalogMQ6, HIGH);
//    delay(50);

    int MQ6sensorValue  = analogRead(AnalogMQ6);

       
    
    
    Serial.print("Gas Value Analog : ");
    Blynk.virtualWrite(V0, MQ6sensorValue);
    Serial.print(MQ6sensorValue);
    Serial.print("\t");

   
    if (MQ6sensorValue < 1000)
    {
      Serial.println ("Terjadi kebocoran gas!");
     
      digitalWrite  (LED_MERAH, HIGH);
      digitalWrite  (Buzzer, HIGH) ; //send tone
      delay(1000);
      digitalWrite  (Buzzer, LOW);
      delay(100);
      digitalWrite  (Buzzer, LOW) ;  //no tone
      digitalWrite  (LED_MERAH, LOW);
     }

    else 
    
    {
      Serial.println  ("Ruangan Aman!");
      digitalWrite    (LED_HIJAU, HIGH);
      delay(100);
      digitalWrite    (LED_HIJAU, LOW);
    }
      delay(1000);
   }

void sensorApi()
  {
    int firesensorAnalog = analogRead(Fire_analog);
    int firesensorDigital = digitalRead(Fire_digital);
    Serial.print("Fire Class: ");
    Serial.print(firesensorDigital);
    Serial.print("\t");
    
  
  if (firesensorDigital == 1) 
  {
    
    
    Serial.println("Fire");
    Blynk.logEvent("fire","Terdeteksi api");
    
    digitalWrite  (LED_MERAH, HIGH);
    digitalWrite  (Buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite  (Buzzer, LOW);
    delay(100);
    digitalWrite  (Buzzer, LOW) ;  //no tone
    digitalWrite  (LED_MERAH, LOW);
    
  }
  else 
  
  {
    Serial.println("No Fire");
    digitalWrite(LED_HIJAU, HIGH);
    delay(100);
    digitalWrite(LED_HIJAU, LOW);
  }
    delay(1000);
  }

void loop() 
  {
    sensorGas();
    sensorApi();
    
    
    BlynkEdgent.run();
  }
