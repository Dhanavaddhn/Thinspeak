#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

float temperature;
float humidity;
DHT sensor(D4,DHT11);

const char*  writeKey = "CRRWC2XKJ7CRKLWG";
unsigned long channelID = 2340828;
unsigned long timeDelay = 15000;

WiFiClient client;

void init_wifi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial. print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void getSensor(){
  humidity = (sensor.readHumidity());
  temperature = (sensor.readTemperature());
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);
}

void setup(){
  Serial.begin(9600);
  init_wifi("PADHAN","123456789");
  sensor.begin();
  temperature = 0;
  humidity = 0;
  ThingSpeak.begin(client);
}

void loop(){
  getSensor();
  int x = ThingSpeak.writeFields(channelID, writeKey);
  if(x == 200) {
    Serial.println("sent humidity and temperature to ThingSpeak");
  } else {
    Serial.println("Problem sending to ThingSpeak");
  }
  delay(timeDelay);
}