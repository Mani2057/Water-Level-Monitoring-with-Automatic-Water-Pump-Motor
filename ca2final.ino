#include <LiquidCrystal.h>

#define USONIC_DIV 0.034
#define trigPin 9
#define echoPin 8
#define buzzerPin 10
#define relayPin 11

LiquidCrystal lcd(7, 6, 4, 5, 3, 2);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(500);
  
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
}

void loop() {
  long duration;
  int percentage;
  long distance;

  // Measure: put up trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * USONIC_DIV / 2;
  
  // Ensure the distance is within a valid range (2 cm to 10 cm)
  if (distance >= 2 && distance <= 10) {
    percentage = map(distance, 10, 2, 0, 100);
    percentage = constrain(percentage, 0, 100); // Ensure percentage is within 0-100 range
    
    // Display on Serial Monitor
    Serial.print("Percentage: ");
    Serial.print(percentage);
    Serial.print("% ");
    Serial.print(distance);
    Serial.println(" cm");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water Level:");
    lcd.setCursor(0, 1);
    lcd.print(percentage);
    lcd.print("%");

 if(distance<0){
    percentage=0;
  }
  else if(distance>100){
    percentage=100;
  }
   else if(distance==9){
    percentage=5;
  }
 else if(distance==8){
    percentage=10;
  }
 else if(distance==7){
    percentage=25;
  }
   else if(distance==6){
    percentage=40;
  }

 else if(distance==5){
    percentage=50;
  }
 else if(distance==4){
    percentage=65;
  }
   else if(distance==3){
    percentage=85;
  }
   else if(distance==2){
    percentage=100;
  }

    // Check water level and activate buzzer if it's below a threshold
    if (distance<3) {
      digitalWrite(relayPin, HIGH); // Turn on the relay/motor
    } else {
      digitalWrite(relayPin, LOW); // Turn off the relay/motor
    }

    // Activate buzzer if the water level is critical
    if (distance <= 2) {  // Adjust the threshold as needed
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      delay(1000);
      digitalWrite(buzzerPin, LOW); // Turn on the buzzer
      
    } else {
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    }
  } else {
    // Invalid distance, handle it here (optional)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error: Invalid");
    lcd.setCursor(0, 1);
    lcd.print("Distance");
    digitalWrite(relayPin, LOW); // Turn off the relay/motor if distance is invalid
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer if distance is invalid
  }

  delay(1000); // Delay for stability, adjust as needed
}
