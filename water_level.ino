#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


BlynkTimer timer; 
char auth[] = "ozlBtiO_8H8o4T0-dn3Er0jAYBQNvnhy";  // token code sent via email 


#define echoPin 2 // attach pin D4 (GPIO2) Node MCU to pin Echo of HC-SR04
#define trigPin 0 //attach pin D3 (GPIO0) Node MCU to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
// add wifi ssid and pass
  Blynk.begin(auth, "Vi", "okgoogle");

// to send function data at 1s
  timer.setInterval(1000, sendLevel);
  
  Serial.println("Water level HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino Uno");
}

void loop(){
  Blynk.run();
  timer.run();
  delay(1000);
}

void sendLevel(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
//  send data to V1 of Blynk app
  Blynk.virtualWrite(V1, distance);
  Serial.print(distance);
  Serial.println(" cm");
}
