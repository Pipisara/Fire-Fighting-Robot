#define DHT_PIN_1 3 // DHT11 1
#define FLAME_PIN_1 4 // Flame 1
#define DHT_PIN_2 2 // DHT11 2
#define FLAME_PIN_2 5 // Flame 2
#define BUZZER_PIN 6 // Buzzer pin
#define BUTTON_PIN 7 // Button pin

#include <DHT.h>

#define DHT_TYPE DHT11
DHT dht1(DHT_PIN_1, DHT_TYPE);
DHT dht2(DHT_PIN_2, DHT_TYPE);

void setup() {
  Serial.begin(9600); 
  
siren();

  // DHT sensors
  dht1.begin();
  dht2.begin();
  
  // flame sensor pins
  pinMode(FLAME_PIN_1, INPUT);
  pinMode(FLAME_PIN_2, INPUT);
  
  // Set buzzer and button pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  
  float temperature1 = dht1.readTemperature();
  float temperature2 = dht2.readTemperature();

  int flameValue1 = digitalRead(FLAME_PIN_1);
  int flameValue2 = digitalRead(FLAME_PIN_2);
  
  bool buttonState = digitalRead(BUTTON_PIN);
  bool buttonState1= LOW;
  // Print temperature readings to serial monitor
  Serial.print("Temperature 1: ");
  Serial.print(temperature1);
  Serial.println(" °C");
  Serial.print("Temperature 2: ");
  Serial.print(temperature2);
  Serial.println(" °C");

  delay(500);
  
  if ((temperature1 > 30 && flameValue1 == HIGH) || (temperature2 > 30 && flameValue2 == HIGH)) {
    
    while(buttonState == HIGH) {
      siren();
      buttonState = digitalRead(BUTTON_PIN);
    }
  }
  

if(buttonState == LOW) {
buttonState1=!buttonState1;
   
}

while(buttonState1 == HIGH) {
buttonState1=!buttonState1;
   siren();
}
  noTone(BUZZER_PIN);
  
  delay(2000);
}

void siren() { // siren
  
  for (int i = 200; i < 2000; i += 100) {
    tone(BUZZER_PIN, i);
    delay(50);
  }
  for (int i = 2000; i > 200; i -= 100) {
    tone(BUZZER_PIN, i);
    delay(50);
  }
}
