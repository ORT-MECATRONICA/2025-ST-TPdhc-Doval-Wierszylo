// Code2 – Temperatura en OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define DHTPIN   23
#define DHTTYPE  DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);                 // inicia monitor serie
  dht.begin();                        // arranca sensor
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);                         // frena si la pantalla no anda
  }
  display.clearDisplay();             // limpia pantalla
  display.display();                  // muestra pantalla en blanco
}
//--------------//


void loop() {
  float t = dht.readTemperature();    // lee temperatura
  if (isnan(t)) {                     // chequea si la lectura falla
    delay(2000);
    return;                           // sale y vuelve a intentar
  }


  Serial.print(F("Temperatura: "));
  Serial.print(t, 1);
  Serial.println(F(" °C"));           // manda dato al puerto serie


  display.clearDisplay();             // borra pantalla
  display.setTextSize(2);             // ajusta tamaño de texto
  display.setTextColor(WHITE);        // texto en blanco
  display.setCursor(0, 10);           // posiciona cursor
  display.print("T: ");
  display.print(t, 1);
  display.println(" C");              // imprime temperatura
  display.display();                  // actualiza OLED


  delay(2000);                        // pausa entre lecturas
}
//--------------//
