// Code1 – “Hola mundo” en OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);                 // abre el canal serie para debug

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();             // limpia pantalla
  printText();                        // muestra “Hola mundo”
  delay(1500);                        // espera para que se vea el texto
}

void loop() {
  // no hace nada acá
}

void printText() {
  display.clearDisplay();             // vacía buffer gráfico
  display.setTextSize(2);             // texto más grande
  display.setTextColor(WHITE);        // pone el texto en blanco
  display.setCursor(0, 10);           // fija lugar de inicio
  display.print("Hola mundo");        // escribe el mensaje
  display.display();                  // actualiza pantalla
}
