#include <SPI.h>       // Include SPI library
#include <nRF24L01.h>  // Include nRF24L01 library
#include <RF24.h>      // Include RF24 library

RF24 radio(9, 10);                // Define RF24 object with CE, CSN pins
const byte address[6] = "00001";  // Address for the communication channel

#define FSwitch 6  // directions switches
#define BSwitch 7
#define RSwitch 5
#define LSwitch 4

#define Lservosw 0  //  servo switches
#define Rservosw 1

#define pumpsw 8  //  for pump switch

#define LED A2   //  for LED
#define LED2 A3  //  for another LED

void setup() {
  radio.begin();                      // Initialize radio
  radio.openWritingPipe(address);     // Open writing pipe
  radio.openReadingPipe(1, address);  // Open reading pipe
  radio.setPALevel(RF24_PA_LOW);      // Set power level

  // Set pin modes
  pinMode(FSwitch, INPUT_PULLUP);
  pinMode(BSwitch, INPUT_PULLUP);
  pinMode(LSwitch, INPUT_PULLUP);
  pinMode(RSwitch, INPUT_PULLUP);
  pinMode(Lservosw, INPUT_PULLUP);
  pinMode(Rservosw, INPUT_PULLUP);
  pinMode(pumpsw, INPUT_PULLUP);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read state of switches
  int Forward = !digitalRead(FSwitch);
  int Backward = !digitalRead(BSwitch);
  int Left = !digitalRead(LSwitch);
  int Right = !digitalRead(RSwitch);
  int LServo = !digitalRead(Lservosw);
  int Rservo = !digitalRead(Rservosw);
  int pump = !digitalRead(pumpsw);

  // Count how many switches are pressed
  int buttonCount = Forward + Backward + Left + Right + LServo + Rservo + pump;

  // Check if both servo switches are pressed
  if (LServo == HIGH && Rservo == HIGH) {
    char dataToSend = 'Y';
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
    return;  //
  }
  // Check if more than one switch is pressed
  else if (buttonCount >= 2) {
    char dataToSend = 'S';
    analogWrite(LED, 0);
    radio.write(&dataToSend, sizeof(dataToSend));
    delay(100);  // Delay for stability
    return;
  }

  // Check which direction switch is pressed and send corresponding signal
  if (Forward == HIGH) {
    char dataToSend = 'F';  // move forward
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (Backward == HIGH) {
    char dataToSend = 'B';  // move backward
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (Left == HIGH) {
    char dataToSend = 'L';  // turn left
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (Right == HIGH) {
    char dataToSend = 'R';  // turn right
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (LServo == HIGH) {
    char dataToSend = 'A';  // move left servo
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (Rservo == HIGH) {
    char dataToSend = 'D';  // move right servo
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (pump == HIGH) {
    char dataToSend = 'W';  // operate pump
    delay(500);             // Delay for stability
    analogWrite(LED, 255);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else if (Right == LOW && Right == LOW && Right == LOW && Right == LOW) {
    char dataToSend = 'S';
    analogWrite(LED, 0);
    radio.write(&dataToSend, sizeof(dataToSend));
  } else {
    char dataToSend = 'S';
    analogWrite(LED, 0);
    radio.write(&dataToSend, sizeof(dataToSend));
  }
}
