#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

 // setting the pin numbers are integers so that I don't have to remember them later
const int trigPin = 8;
const int echoPin = 9;
const int lightPin = 7;
const int buzzerPin = 12;

void setup() {
  myservo.attach(10);
  
  pinMode(lightPin, OUTPUT); //setting the light modulation pin as output
  pinMode(buzzerPin, OUTPUT); //setting the buzzer pin as output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  int dist;
  
  dist = find_Distance();

  if (dist > 100) { //says if there is no one at the door, just print the distance in the serial monitor
    Serial.println(dist);
    delay(500);  
   
  }
  
  else if (dist <= 100) { //says if someone is at the door, start shaking the head, blinking the lights, and sound the alarm                 
    for (pos = 0; pos <= 30; pos += 1) { 
      digitalWrite(lightPin, HIGH);
      digitalWrite(buzzerPin, HIGH);   
      myservo.write(pos);              
      delay(5);
    }
    for (pos = 30; pos >= 0; pos -= 1) { 
      digitalWrite(lightPin, LOW);
      digitalWrite(buzzerPin, LOW);
      myservo.write(pos);              
      delay(5);                      
    }
  }
}

//function to measure the distance (found it online)
int find_Distance(){

  int distance;
  long duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  return distance;
}
