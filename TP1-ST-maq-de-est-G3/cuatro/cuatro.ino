// Code4 – Máquina de estado y ajuste de umbral
// (Doval, Wierszylo)


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"


// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Sensor DHT11
#define DHTPIN   23
#define DHTTYPE  DHT11
DHT dht(DHTPIN, DHTTYPE);


// Pines
const int SW1_PIN = 35;
const int SW2_PIN = 34;
const int LED_PIN = 25;


// Estado
int pantalla = 1;
float umbral = 26.0;
bool esperando_soltado = false;


void setup() {
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();


  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}


void loop() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    delay(2000);
    return;
  }


  bool sw1 = digitalRead(SW1_PIN) == LOW;
  bool sw2 = digitalRead(SW2_PIN) == LOW;


  // Cambio de pantalla solo si antes se presionaron los dos
  if (sw1 && sw2) {
    esperando_soltado = true;  // Se activó el modo de espera
  } else if (esperando_soltado && !sw1 && !sw2) {
    pantalla = (pantalla == 1) ? 2 : 1;  // cambia pantalla
    esperando_soltado = false;
    delay(300);  // antirrebote
  }


  // Ajuste de umbral solo en pantalla 2
  if (pantalla == 2) {
    if (sw1 && !sw2) { umbral -= 1; delay(200); }
    if (sw2 && !sw1) { umbral += 1; delay(200); }
  }


  // Mostrar en pantalla
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);


  if (pantalla == 1) {
    display.print("T:");
    display.print(temp, 1);
    display.print("C");
    display.setCursor(0, 30);
    display.print("U:");
    display.print(umbral, 1);
    display.print("C");
  } else {
    display.print("Ajuste");
    display.setCursor(0, 30);
    display.print(umbral, 1);
    display.print("C");
  }
  display.display();


  // Encender LED si temperatura supera umbral
  digitalWrite(LED_PIN, temp > umbral ? HIGH : LOW);


  delay(200);
}
