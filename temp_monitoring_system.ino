// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,7,6,5,4,3);

int sensorPin = A0;
int buzzerPin = 2;

int greenLED = 9;
int yellowLED = 10;
int redLED = 11;

float lowThreshold = 20.0;
float highThreshold = 35.0;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);

  pinMode(buzzerPin, OUTPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop()
{
  int reading = analogRead(sensorPin);

  float voltage = reading * 5.0 / 1024.0;
  float temperatureC = (voltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.println(temperatureC);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temperatureC);
  lcd.print(" C");

  if (temperatureC < lowThreshold)
  {
    lcd.setCursor(0,1);
    lcd.print("LOW TEMP ALERT");

    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);

    tone(buzzerPin, 1000);
  }
  else if (temperatureC > highThreshold)
  {
    lcd.setCursor(0,1);
    lcd.print("HIGH TEMP ALERT");

    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);

    tone(buzzerPin, 2000);
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("TEMP NORMAL");

    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    noTone(buzzerPin);
  }

  delay(500);
}