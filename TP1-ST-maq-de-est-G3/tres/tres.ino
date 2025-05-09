// Code3 – Alerta con umbral fijo
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#define UMBRAL_TEMP 28.0


void setup() {
  Serial.begin(9600);                 // monitor serie
  dht.begin();                        // arranca el sensor
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);                     // se queda ahí si falla el OLED
  }
  display.clearDisplay();             // limpia pantalla
  display.setTextSize(2);             // texto grande
  display.setTextColor(SSD1306_WHITE);// color blanco
  display.setCursor(0, 0);            // coloca cursor al inicio
  display.print("Iniciando...");      // mensaje inicial
  display.display();                  // actualiza OLED
  delay(1000);                        // espera un segundo
}
//--------------//


void loop() {
  float temperatura = dht.readTemperature();  // lee temperatura


  display.clearDisplay();             // borra pantalla


  if (!isnan(temperatura)) {          // si la lectura es válida
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");            // envía al serie


    display.setTextSize(2);           // texto grande
    display.setCursor(0, 0);          // ubica cursor
    display.print("Temp:");
    display.setCursor(0, 20);
    display.print(temperatura, 1);
    display.print(" C");              // muestra valor


    display.setTextSize(1);           // texto más pequeño
    display.setCursor(0, 50);
    if (temperatura > UMBRAL_TEMP) {
      display.print("Estado: Temp ALTA!");
    } else {
      display.print("Estado: Temp OK");
    }
  }


  display.display();                  // refresca pantalla
  delay(2000);                        // pausa antes de leer otra vez
}
//--------------//
