#include <WiFi.h>
#include <WiFiClient.h>
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

char ssid[] = "NoWifi"; // your network SSID (name)
char pass[] = "MALLALI1975"; // your network password
int status = WL_IDLE_STATUS;

WiFiClient espClient;

#define DHTPIN 23     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define I2C_ADDR 0x3F
#define BACKLIGHT_PIN 3
#define pot 36
#define led 18

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(115200); // start the serial monitor
  WiFi.begin(ssid, pass); // start the wifi
  dht.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setBacklight(HIGH);
  
  Serial.print("searching...");
  
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("connected IP adres = ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
}

void loop() 
{
  float temp = dht.readTemperature();

  lcd.setCursor(0,0);
  Serial.print(temp);
  Serial.println("*C");
  lcd.print(temp);
  lcd.print("*C");
  
  int potentio = analogRead(pot);
  potentio = map(potentio, 0, 4095, 0 , 30);
  Serial.println(potentio);

  lcd.setCursor(0,1);
  Serial.print(potentio);
  Serial.println("*C");
  lcd.print(potentio);
  lcd.print("*C");

  if(potentio > temp)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }

}
