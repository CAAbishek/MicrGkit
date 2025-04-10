#include <Wire.h>
#include <RTClib.h>
#define UV_LIGHT_PIN D5
#define WATER_PUMP_PIN D7
#define SOIL_MOISTURE_PIN A0

RTC_DS3231 rtc;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  pinMode(UV_LIGHT_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

  // Initialize RTC module
  if (!rtc.begin()) {
      while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(2024, 3, 22, 10, 52, 0));
}

void loop() {
  DateTime now = rtc.now();
  // Turn on UV light from 7:00 AM to 8:00 AM
  if (now.hour() == 10 && now.minute() == 53 && now.second() >= 0) {
    digitalWrite(UV_LIGHT_PIN, HIGH);
  } else if (now.hour() == 8 && now.minute() == 0 && now.second() == 0) {
    digitalWrite(UV_LIGHT_PIN, LOW);
  }

  // Check soil moisture level
  int moistureLevel = analogRead(SOIL_MOISTURE_PIN);
  Serial.println(moistureLevel);
  if (moistureLevel > 700) { // Adjust threshold as needed
    // Turn on water pump 
    
    digitalWrite(WATER_PUMP_PIN, LOW);
    delay(5000); // Run pump for 1 second (adjust as needed)
    digitalWrite(WATER_PUMP_PIN, LOW);
  }

  delay(1000); // Delay 1 second before next iteration
}
