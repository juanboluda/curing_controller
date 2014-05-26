#include <dht11.h>


dht11 DHT11;

#define DHT11PIN 2

float tempsetpoint = 17.0;
float humiditysetpoint = 75.0;

#define TEMPRELAY 8
#define HUMRELAY 9

#define INTERVAL_IN_MS 30000

unsigned long LastFridgeRun = 0;
unsigned long LastHumidityRun = 0;

boolean FRIDGE_IS_ON = false;
boolean HUMIDIFIER_IS_ON = false;

void setup()
{
  pinMode(TEMPRELAY, OUTPUT);
  pinMode(HUMRELAY, OUTPUT);
}

void loop()
{
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);


  if (FRIDGE_IS_ON) {
    LastFridgeRun = millis();
  }
  if (HUMIDIFIER_IS_ON) {
    LastHumidityRun = millis();
  }

  if ((float)DHT11.temperature > tempsetpoint) {
    if (!FRIDGE_IS_ON) {
      if (millis() > LastFridgeRun + INTERVAL_IN_MS) {
        digitalWrite(TEMPRELAY, LOW);
        Serial.println("We turned the fridge on");
        FRIDGE_IS_ON = true;
      }
    }
  }
  else {
    FRIDGE_IS_ON = false;
    digitalWrite(TEMPRELAY, HIGH);
    Serial.println("We turned the fridge off");
  }

  if ((float)DHT11.humidity < humiditysetpoint) {
    if (!HUMIDIFIER_IS_ON) {
      if (millis() > LastHumidityRun + INTERVAL_IN_MS) {
        digitalWrite(HUMRELAY, LOW);
        Serial.println("We turned the humidifier on");
        HUMIDIFIER_IS_ON = true;
      }
    }
  }
  else {
    HUMIDIFIER_IS_ON = false;
    digitalWrite(HUMRELAY, HIGH);
    Serial.println("We turned the humidifier off");
  }

  delay(2000);
}
